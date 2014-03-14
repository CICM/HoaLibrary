//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework not only for VST plugins
//
// Version 4.2
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2013, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this
//     software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "uibitmapscontroller.h"

#if VSTGUI_LIVE_EDITING

#include "uibasedatasource.h"
#include "uisearchtextfield.h"
#include "uieditcontroller.h"
#include "uidialogcontroller.h"
#include "../../lib/cbitmapfilter.h"
#include "../../lib/cfileselector.h"
#include "../../lib/idatapackage.h"
#include "../../lib/controls/ccolorchooser.h"
#include "../../lib/controls/ctextedit.h"

namespace VSTGUI {
//----------------------------------------------------------------------------------------------------
class UIBitmapView : public CView
{
public:
	UIBitmapView (CBitmap* bitmap = 0)
	: CView (CRect (0, 0, 0, 0))
	, zoom (1.)
	, fastZooming (true)
	{
		setBackground (bitmap);
	}
	
	void draw (CDrawContext* context)
	{
		CView::draw (context);
		if (getBackground ())
		{
			CNinePartTiledBitmap* bitmap = dynamic_cast<CNinePartTiledBitmap*>(getBackground ());
			if (bitmap)
			{
				static const CCoord kDefaultOnOffDashLength2[] = {2, 2};
				const CLineStyle kLineOnOffDash2 (CLineStyle::kLineCapButt, CLineStyle::kLineJoinMiter, 0, 2, kDefaultOnOffDashLength2);

				const CNinePartTiledBitmap::PartOffsets offsets = bitmap->getPartOffsets ();
				CRect r (getViewSize ());
				context->setDrawMode (kAliasing);
				context->setFrameColor (kBlueCColor);
				context->setLineWidth (1);
				context->setLineStyle (kLineSolid);
				context->moveTo (CPoint (r.left, r.top + offsets.top));
				context->lineTo (CPoint (r.right, r.top + offsets.top));
				context->moveTo (CPoint (r.left, r.bottom - offsets.bottom));
				context->lineTo (CPoint (r.right, r.bottom - offsets.bottom));
				context->moveTo (CPoint (r.left + offsets.left, r.top));
				context->lineTo (CPoint (r.left + offsets.left, r.bottom));
				context->moveTo (CPoint (r.right - offsets.right, r.top));
				context->lineTo (CPoint (r.right - offsets.right, r.bottom));
				context->setFrameColor (kRedCColor);
				context->setLineWidth (1);
				context->setLineStyle (kLineOnOffDash2);
				context->moveTo (CPoint (r.left, r.top + offsets.top));
				context->lineTo (CPoint (r.right, r.top + offsets.top));
				context->moveTo (CPoint (r.left, r.bottom - offsets.bottom));
				context->lineTo (CPoint (r.right, r.bottom - offsets.bottom));
				context->moveTo (CPoint (r.left + offsets.left, r.top));
				context->lineTo (CPoint (r.left + offsets.left, r.bottom));
				context->moveTo (CPoint (r.right - offsets.right, r.top));
				context->lineTo (CPoint (r.right - offsets.right, r.bottom));
			}
		}
	}

	void enableFastZooming (bool state)
	{
//		if (state != fastZooming)
//		{
//			fastZooming = state;
//			if (state == false)
//			{
//				CCoord z = zoom;
//				zoom -= 1;
//				setZoom (z);
//			}
//		}
	}

	void setZoom (CCoord factor)
	{
		if (factor <= 0. || factor == zoom)
			return;
		if (unzoomedBitmap)
		{
			if (factor == 1.)
			{
				setBitmapToShow (unzoomedBitmap);
			}
			else
			{
				OwningPointer<BitmapFilter::IFilter> filter = BitmapFilter::Factory::getInstance ().createFilter (fastZooming ? BitmapFilter::Standard::kScaleLinear : BitmapFilter::Standard::kScaleBilinear);
				if (filter)
				{
					filter->setProperty (BitmapFilter::Standard::Property::kInputBitmap, unzoomedBitmap.cast<CBaseObject> ());
					CRect r;
					r.setWidth (unzoomedBitmap->getWidth () * factor);
					r.setHeight (unzoomedBitmap->getHeight () * factor);
					filter->setProperty (BitmapFilter::Standard::Property::kOutputRect, r);
					if (filter->run ())
					{
						BitmapFilter::Property prop = filter->getProperty (BitmapFilter::Standard::Property::kOutputBitmap);
						CBitmap* bitmap = dynamic_cast<CBitmap*> (prop.getObject ());
						if (bitmap)
						{
							if (CNinePartTiledBitmap* nptb = unzoomedBitmap.cast<CNinePartTiledBitmap> ())
							{
								CNinePartTiledBitmap::PartOffsets offsets = nptb->getPartOffsets ();
								offsets.left *= factor;
								offsets.right *= factor;
								offsets.top *= factor;
								offsets.bottom *= factor;
								OwningPointer<CNinePartTiledBitmap> newBitmap = new CNinePartTiledBitmap (bitmap->getPlatformBitmap(), offsets);
								setBitmapToShow (newBitmap);
							}
							else
								setBitmapToShow (bitmap);
						}
					}
				}
			}
		}
		zoom = factor;
	}

	void setBitmapToShow (CBitmap* bitmap)
	{
		CView::setBackground (bitmap);
		CCoord width = bitmap ? bitmap->getWidth () : 0;
		CCoord height = bitmap ? bitmap->getHeight () : 0;
		CRect r (getViewSize ());
		r.setWidth (width+1);
		r.setHeight(height+1);
		if (getViewSize () != r)
		{
			setViewSize (r);
			setMouseableArea (r);
		}
	}

	void setBackground (CBitmap *background)
	{
		unzoomedBitmap = background;
		if (zoom != 1.)
		{
			CCoord toZoom = zoom;
			zoom = toZoom+1;
			setZoom (toZoom);
		}
		else
			setBitmapToShow (background);
	}
protected:
	CCoord zoom;
	bool fastZooming;
	SharedPointer<CBitmap> unzoomedBitmap;
};

//----------------------------------------------------------------------------------------------------
class UIBitmapsDataSource : public UIBaseDataSource
{
public:
	UIBitmapsDataSource (UIDescription* description, IActionPerformer* actionPerformer, IGenericStringListDataBrowserSourceSelectionChanged* delegate);
	
	CBitmap* getSelectedBitmap ();
	UTF8StringPtr getSelectedBitmapName ();

	virtual bool add ();
protected:
	virtual void getNames (std::list<const std::string*>& names);
	virtual bool addItem (UTF8StringPtr name);
	virtual bool removeItem (UTF8StringPtr name);
	virtual bool performNameChange (UTF8StringPtr oldName, UTF8StringPtr newName);
	virtual UTF8StringPtr getDefaultsName () { return "UIBitmapsDataSource"; }

	bool addBitmap (UTF8StringPtr path, std::string& outName);

	void dbOnDragEnterBrowser (IDataPackage* drag, CDataBrowser* browser) VSTGUI_OVERRIDE_VMETHOD;
	void dbOnDragExitBrowser (IDataPackage* drag, CDataBrowser* browser) VSTGUI_OVERRIDE_VMETHOD;
	void dbOnDragEnterCell (int32_t row, int32_t column, const CPoint& where, IDataPackage* drag, CDataBrowser* browser) VSTGUI_OVERRIDE_VMETHOD;
	void dbOnDragExitCell (int32_t row, int32_t column, IDataPackage* drag, CDataBrowser* browser) VSTGUI_OVERRIDE_VMETHOD;
	bool dbOnDropInCell (int32_t row, int32_t column, const CPoint& where, IDataPackage* drag, CDataBrowser* browser) VSTGUI_OVERRIDE_VMETHOD;

	SharedPointer<CColorChooser> colorChooser;
	bool dragContainsBitmaps;
};

//----------------------------------------------------------------------------------------------------
UIBitmapsDataSource::UIBitmapsDataSource (UIDescription* description, IActionPerformer* actionPerformer, IGenericStringListDataBrowserSourceSelectionChanged* delegate)
: UIBaseDataSource (description, actionPerformer, UIDescription::kMessageBitmapChanged, delegate)
, dragContainsBitmaps (false)
{
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsDataSource::dbOnDragEnterBrowser (IDataPackage* drag, CDataBrowser* browser)
{
	int32_t index = 0;
	IDataPackage::Type type;
	const void* item = 0;
	while (drag->getData (index, item, type) > 0)
	{
		if (type == IDataPackage::kFilePath)
		{
			const char* ext = strrchr (static_cast<const char*> (item), '.');
			if (ext)
			{
				std::string extStr (ext);
				std::transform (extStr.begin (), extStr.end (), extStr.begin (), ::tolower);
				if (extStr == ".png" || extStr == ".bmp" || extStr == ".jpg" || extStr == ".jpeg")
				{
					dragContainsBitmaps = true;
					break;
				}
			}
		}
		index++;
	}
	if (dragContainsBitmaps)
		browser->getFrame ()->setCursor (kCursorCopy);
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsDataSource::dbOnDragExitBrowser (IDataPackage* drag, CDataBrowser* browser)
{
	if (dragContainsBitmaps)
		browser->getFrame ()->setCursor (kCursorNotAllowed);
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsDataSource::dbOnDragEnterCell (int32_t row, int32_t column, const CPoint& where, IDataPackage* drag, CDataBrowser* browser)
{
#if DEBUG
	DebugPrint ("enter cell: %d-%d\n", row, column);
#endif
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsDataSource::dbOnDragExitCell (int32_t row, int32_t column, IDataPackage* drag, CDataBrowser* browser)
{
#if DEBUG
	DebugPrint ("exit cell: %d-%d\n", row, column);
#endif
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::dbOnDropInCell (int32_t row, int32_t column, const CPoint& where, IDataPackage* drag, CDataBrowser* browser)
{
	if (dragContainsBitmaps)
	{
		int32_t index = 0;
		IDataPackage::Type type;
		const void* item = 0;
		while (drag->getData (index++, item, type) > 0)
		{
			if (type == IDataPackage::kFilePath)
			{
				const char* ext = strrchr (static_cast<const char*> (item), '.');
				if (ext)
				{
					std::string extStr (ext);
					std::transform (extStr.begin (), extStr.end (), extStr.begin (), ::tolower);
					if (extStr == ".png" || extStr == ".bmp" || extStr == ".jpg" || extStr == ".jpeg")
					{
						std::string name;
						addBitmap (static_cast<UTF8StringPtr> (item), name);
					}
				}
			}
		}
		dragContainsBitmaps = false;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsDataSource::getNames (std::list<const std::string*>& names)
{
	description->collectBitmapNames (names);
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::addItem (UTF8StringPtr name)
{
	actionPerformer->performBitmapChange (name, 0);
	return true;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::removeItem (UTF8StringPtr name)
{
	actionPerformer->performBitmapChange (name, 0, true);
	return true;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::performNameChange (UTF8StringPtr oldName, UTF8StringPtr newName)
{
	actionPerformer->performBitmapNameChange (oldName, newName);
	return true;
}

//----------------------------------------------------------------------------------------------------
CBitmap* UIBitmapsDataSource::getSelectedBitmap ()
{
	int32_t selectedRow = dataBrowser ? dataBrowser->getSelectedRow() : CDataBrowser::kNoSelection;
	if (selectedRow != CDataBrowser::kNoSelection && selectedRow < (int32_t)names.size ())
		return description->getBitmap (names.at (selectedRow).c_str ());
	return 0;
}

//----------------------------------------------------------------------------------------------------
UTF8StringPtr UIBitmapsDataSource::getSelectedBitmapName ()
{
	int32_t selectedRow = dataBrowser ? dataBrowser->getSelectedRow() : CDataBrowser::kNoSelection;
	if (selectedRow != CDataBrowser::kNoSelection && selectedRow < (int32_t)names.size ())
		return names.at (selectedRow).c_str ();
	return 0;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::addBitmap (UTF8StringPtr path, std::string& outName)
{
	bool result = false;
	outName = path;
	unixfyPath (outName);
	size_t index = outName.find_last_of (unixPathSeparator);
	outName.erase (0, index+1);
	index = outName.find_last_of ('.');
	if (index == std::string::npos)
		return false;

	outName.erase (index);
	if (createUniqueName (outName))
	{
		std::string pathStr (path);
		UTF8StringPtr descPath = description->getXmFileName ();
		if (descPath && descPath[0] != 0)
		{
			std::string descPathStr (descPath);
			unixfyPath (descPathStr);
			index = descPathStr.find_last_of (unixPathSeparator);
			if (index != std::string::npos)
			{
				descPathStr.erase (index);
				if ((index = pathStr.find (descPathStr)) == 0)
				{
					pathStr.erase (0, descPathStr.length () + 1);
				}
			}
		}
		actionPerformer->performBitmapChange (outName.c_str (), pathStr.c_str ());
		result = true;
	}
	return result;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsDataSource::add ()
{
	bool result = false;
	OwningPointer<CNewFileSelector> fs = CNewFileSelector::create (dataBrowser->getFrame ());
	if (fs)
	{
		fs->addFileExtension (CFileExtension ("PNG", "PNG"));
		fs->addFileExtension (CFileExtension ("BMP", "BMP"));
		fs->addFileExtension (CFileExtension ("JPG", "JPG"));
		fs->addFileExtension (CFileExtension ("JPEG", "JPEG"));
		fs->setAllowMultiFileSelection (true);
		if (fs->runModal ())
		{
			int32_t numFiles = fs->getNumSelectedFiles();
			for (int32_t i = 0; i < numFiles; i++)
			{
				UTF8StringPtr path = fs->getSelectedFile (i);
				if (path)
				{
					std::string newName;
					if (addBitmap (path, newName) && i == numFiles - 1)
					{
						int32_t row = selectName (newName.c_str ());
						if (row != -1)
							dbOnMouseDown (CPoint (0, 0), CButtonState (kLButton|kDoubleClick), row, 0, dataBrowser);
						result = true;
					}
				}
			}
		}
	}
	return result;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
class UIBitmapSettingsController : public CBaseObject, public IController
{
public:
	UIBitmapSettingsController (CBitmap* bitmap, const std::string& bitmapName, UIDescription* description, IActionPerformer* actionPerformer);
	~UIBitmapSettingsController ();

	CMessageResult notify (CBaseObject* sender, IdStringPtr message);
	CView* verifyView (CView* view, const UIAttributes& attributes, IUIDescription* description);
	CView* createView (const UIAttributes& attributes, IUIDescription* description);
	void valueChanged (CControl* pControl);
	void controlBeginEdit (CControl* pControl);
	void controlEndEdit (CControl* pControl);
protected:
	void updateNinePartTiledControls ();
	static bool stringToValue (UTF8StringPtr txt, float& result, void* userData);
	static bool valueToString (float value, char utf8String[256], void* userData);

	IActionPerformer* actionPerformer;
	SharedPointer<UIDescription> editDescription;
	SharedPointer<CBitmap> bitmap;
	SharedPointer<UIBitmapView> bitmapView;
	std::string bitmapName;
	CRect origOffsets;

	enum {
		kBitmapPathTag,
		kBitmapWidthTag,
		kBitmapHeightTag,
		kNinePartTiledTag,
		kNinePartTiledLeftTag,
		kNinePartTiledTopTag,
		kNinePartTiledRightTag,
		kNinePartTiledBottomTag,
		kZoomTag,
		kZoomTextTag,
		kNumTags
	};
	CControl* controls[kNumTags];
};

//----------------------------------------------------------------------------------------------------
UIBitmapSettingsController::UIBitmapSettingsController (CBitmap* bitmap, const std::string& bitmapName, UIDescription* description, IActionPerformer* actionPerformer)
: bitmap (bitmap)
, bitmapName (bitmapName)
, editDescription (description)
, actionPerformer (actionPerformer)
, origOffsets (10, 10, 10, 10)
{
	for (int32_t i = 0; i < kNumTags; i++)
		controls[i] = 0;
}

//----------------------------------------------------------------------------------------------------
UIBitmapSettingsController::~UIBitmapSettingsController ()
{
}

//----------------------------------------------------------------------------------------------------
void UIBitmapSettingsController::updateNinePartTiledControls ()
{
	CNinePartTiledBitmap* nptb = bitmap.cast<CNinePartTiledBitmap> ();
	if (nptb)
	{
		controls[kNinePartTiledTag]->setValueNormalized (1);
		const CNinePartTiledBitmap::PartOffsets offsets = nptb->getPartOffsets ();
		controls[kNinePartTiledLeftTag]->setValue ((float)offsets.left);
		controls[kNinePartTiledTopTag]->setValue ((float)offsets.top);
		controls[kNinePartTiledRightTag]->setValue ((float)offsets.right);
		controls[kNinePartTiledBottomTag]->setValue ((float)offsets.bottom);
	}
	else
	{
		controls[kNinePartTiledTag]->setValueNormalized (0.);
		for (int32_t i = kNinePartTiledLeftTag; i <= kNinePartTiledBottomTag; i++)
		{
			CTextLabel* label = dynamic_cast<CTextLabel*>(controls[i]);
			if (label)
				label->setText ("");
		}
	}
	for (int32_t i = kNinePartTiledLeftTag; i <= kNinePartTiledBottomTag; i++)
	{
		controls[i]->setMouseEnabled (nptb ? true : false);
	}
}

//----------------------------------------------------------------------------------------------------
void UIBitmapSettingsController::valueChanged (CControl* control)
{
	switch (control->getTag ())
	{
		case kBitmapPathTag:
		{
			CTextEdit* edit = dynamic_cast<CTextEdit*>(control);
			if (edit)
			{
				actionPerformer->performBitmapChange (bitmapName.c_str (), edit->getText ());
				bitmap = editDescription->getBitmap (bitmapName.c_str ());
				bitmapView->setBackground (bitmap);
				updateNinePartTiledControls ();
			}
			break;
		}
		case kNinePartTiledTag:
		{
			CNinePartTiledBitmap* nptb = bitmap.cast<CNinePartTiledBitmap> ();
			if (nptb)
			{
				origOffsets.left = nptb->getPartOffsets ().left;
				origOffsets.top = nptb->getPartOffsets ().top;
				origOffsets.right = nptb->getPartOffsets ().right;
				origOffsets.bottom = nptb->getPartOffsets ().bottom;
			}
			bool checked = control->getValue () == control->getMax ();
			actionPerformer->performBitmapNinePartTiledChange (bitmapName.c_str (), checked ? &origOffsets : 0);
			bitmap = editDescription->getBitmap (bitmapName.c_str ());
			bitmapView->setBackground (bitmap);
			updateNinePartTiledControls ();
			break;
		}
		case kNinePartTiledLeftTag:
		case kNinePartTiledTopTag:
		case kNinePartTiledRightTag:
		case kNinePartTiledBottomTag:
		{
			CRect r;
			r.left = controls[kNinePartTiledLeftTag]->getValue ();
			r.top = controls[kNinePartTiledTopTag]->getValue ();
			r.right = controls[kNinePartTiledRightTag]->getValue ();
			r.bottom = controls[kNinePartTiledBottomTag]->getValue ();
			actionPerformer->performBitmapNinePartTiledChange (bitmapName.c_str (), &r);
			bitmap = editDescription->getBitmap (bitmapName.c_str ());
			bitmapView->setBackground (bitmap);
			updateNinePartTiledControls ();
			break;
		}
		case kZoomTag:
		{
			CCoord zoom = floor (control->getValue () / 10. + 0.5);
			control->setValue ((float)zoom * 10.f);
			controls[kZoomTextTag]->setValue ((float)zoom * 10.f);
			bitmapView->setZoom (zoom / 10.);
			controls[kZoomTextTag]->invalid ();
			control->invalid ();
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------
void UIBitmapSettingsController::controlBeginEdit (CControl* control)
{
	if (control->getTag () == kZoomTag)
	{
		bitmapView->enableFastZooming (true);
	}
}

//----------------------------------------------------------------------------------------------------
void UIBitmapSettingsController::controlEndEdit (CControl* control)
{
	if (control->getTag () == kZoomTag)
	{
		bitmapView->enableFastZooming (false);
	}
}

//----------------------------------------------------------------------------------------------------
CMessageResult UIBitmapSettingsController::notify (CBaseObject* sender, IdStringPtr message)
{
	if (message == UIDialogController::kMsgDialogButton1Clicked)
	{
		return kMessageNotified;
	}
	else if (message == UIDialogController::kMsgDialogShow)
	{
		bitmapView->setBackground (bitmap);
		updateNinePartTiledControls ();
		return kMessageNotified;
	}
	return kMessageUnknown;
}

//----------------------------------------------------------------------------------------------------
CView* UIBitmapSettingsController::verifyView (CView* view, const UIAttributes& attributes, IUIDescription* description)
{
	CControl* control = dynamic_cast<CControl*>(view);
	if (control && control->getTag () >= 0 && control->getTag () < kNumTags)
	{
		controls[control->getTag ()] = control;
		switch (control->getTag ())
		{
			case kBitmapPathTag:
			{
				CTextEdit* bitmapPathEdit = dynamic_cast<CTextEdit*> (control);
				if (bitmapPathEdit)
					bitmapPathEdit->setText (bitmap->getResourceDescription ().u.name);
				break;
			}
			case kBitmapWidthTag:
			{
				CTextLabel* label = dynamic_cast<CTextLabel*>(control);
				if (label)
				{
					label->setPrecision (0);
					label->setMax ((float)bitmap->getWidth ());
					label->setValue ((float)bitmap->getWidth ());
					label->sizeToFit ();
				}
				break;
			}
			case kBitmapHeightTag:
			{
				CTextLabel* label = dynamic_cast<CTextLabel*>(control);
				if (label)
				{
					label->setPrecision (0);
					label->setMax ((float)bitmap->getHeight ());
					label->setValue ((float)bitmap->getHeight ());
					label->sizeToFit ();
					if (controls[kBitmapWidthTag])
					{
						CRect r = control->getViewSize ();
						if (controls[kBitmapWidthTag]->getWidth () > r.getWidth ())
						{
							r.setWidth (controls[kBitmapWidthTag]->getWidth ());
							control->setViewSize (r);
						}
						else
						{
							r = controls[kBitmapWidthTag]->getViewSize ();
							r.setWidth (control->getWidth ());
							controls[kBitmapWidthTag]->setViewSize (r);
						}
					}
				}
				break;
			}
			case kNinePartTiledLeftTag:
			case kNinePartTiledRightTag:
			{
				CTextEdit* textEdit = dynamic_cast<CTextEdit*>(control);
				if (textEdit)
				{
					textEdit->setPrecision (0);
					textEdit->setStringToValueProc (stringToValue);
				}
				control->setMax ((float)bitmap->getWidth ());
				break;
			}
			case kNinePartTiledTopTag:
			case kNinePartTiledBottomTag:
			{
				CTextEdit* textEdit = dynamic_cast<CTextEdit*>(control);
				if (textEdit)
				{
					textEdit->setPrecision (0);
					textEdit->setStringToValueProc (stringToValue);
				}
				control->setMax ((float)bitmap->getHeight ());
				break;
			}
			case kZoomTag:
			{
				control->setValue (100);
				break;
			}
			case kZoomTextTag:
			{
				CTextLabel* label = dynamic_cast<CTextLabel*>(control);
				if (label)
				{
					label->setValueToStringProc (valueToString);
				}
				control->setValue (100);
			}
		}
	}
	return view;
}

//----------------------------------------------------------------------------------------------------
CView* UIBitmapSettingsController::createView (const UIAttributes& attributes, IUIDescription* description)
{
	const std::string* name = attributes.getAttributeValue ("custom-view-name");
	if (name)
	{
		if (*name == "BitmapView")
		{
			bitmapView = new UIBitmapView ();
			return bitmapView;
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapSettingsController::valueToString (float value, char utf8String[256], void* userData)
{
	int32_t intValue = (int32_t)value;
	std::stringstream str;
	str << intValue;
	str << "%";
	strcpy (utf8String, str.str ().c_str ());
	return true;
}


//----------------------------------------------------------------------------------------------------
bool UIBitmapSettingsController::stringToValue (UTF8StringPtr txt, float& result, void* userData)
{
	int32_t value = txt ? (int32_t)strtol (txt, 0, 10) : 0;
	result = (float)value;
	return true;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
UIBitmapsController::UIBitmapsController (IController* baseController, UIDescription* description, IActionPerformer* actionPerformer)
: DelegationController (baseController)
, editDescription (description)
, actionPerformer (actionPerformer)
, dataSource (0)
{
	dataSource = new UIBitmapsDataSource (editDescription, actionPerformer, this);
	UIEditController::setupDataSource (dataSource);
}

//----------------------------------------------------------------------------------------------------
UIBitmapsController::~UIBitmapsController ()
{
	dataSource->forget ();
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsController::showSettingsDialog ()
{
	UIDialogController* dc = new UIDialogController (this, bitmapPathEdit->getFrame ());
	UIBitmapSettingsController* fsController = new UIBitmapSettingsController (dataSource->getSelectedBitmap (), dataSource->getSelectedBitmapName (), editDescription, actionPerformer);
	dc->run ("bitmap.settings", "Bitmap Settings", "Close", 0, fsController, &UIEditController::getEditorDescription ());
}

//----------------------------------------------------------------------------------------------------
CView* UIBitmapsController::createView (const UIAttributes& attributes, IUIDescription* description)
{
	const std::string* name = attributes.getAttributeValue ("custom-view-name");
	if (name)
	{
		if (*name == "BitmapsBrowser")
		{
			CDataBrowser* dataBrowser = new CDataBrowser (CRect (0, 0, 0, 0), dataSource, CDataBrowser::kDrawRowLines|CScrollView::kHorizontalScrollbar | CScrollView::kVerticalScrollbar);
			return dataBrowser;
		}
		else if (*name == "BitmapView")
		{
			bitmapView = new UIBitmapView ();
			return bitmapView;
		}
	}
	return DelegationController::createView (attributes, description);
}

//----------------------------------------------------------------------------------------------------
CView* UIBitmapsController::verifyView (CView* view, const UIAttributes& attributes, IUIDescription* description)
{
	UISearchTextField* searchField = dynamic_cast<UISearchTextField*>(view);
	if (searchField && searchField->getTag () == kSearchTag)
	{
		dataSource->setSearchFieldControl (searchField);
		return searchField;
	}
	CTextEdit* textEdit = dynamic_cast<CTextEdit*>(view);
	if (textEdit)
	{
		switch (textEdit->getTag ())
		{
			case kBitmapPathTag:
			{
				bitmapPathEdit = textEdit;
				textEdit->setMouseEnabled (false);
				break;
			}
		}
	}
	else
	{
		CControl* control = dynamic_cast<CControl*> (view);
		if (control)
		{
			if (control->getTag () == kSettingsTag)
			{
				settingButton = control;
				settingButton->setMouseEnabled (false);
			}
		}
	}
	return DelegationController::verifyView (view, attributes, description);
}

//----------------------------------------------------------------------------------------------------
CControlListener* UIBitmapsController::getControlListener (UTF8StringPtr name)
{
	return this;
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsController::valueChanged (CControl* pControl)
{
	switch (pControl->getTag ())
	{
		case kAddTag:
		{
			if (pControl->getValue () == pControl->getMax ())
			{
				dataSource->add ();
			}
			break;
		}
		case kRemoveTag:
		{
			if (pControl->getValue () == pControl->getMax ())
			{
				dataSource->remove ();
			}
			break;
		}
		case kBitmapPathTag:
		{
			UTF8StringPtr bitmapName = dataSource->getSelectedBitmapName ();
			if (bitmapName)
			{
				CTextEdit* edit = dynamic_cast<CTextEdit*>(pControl);
				if (edit)
					actionPerformer->performBitmapChange (bitmapName, edit->getText ());
			}
			break;
		}
		case kSettingsTag:
		{
			if (pControl->getValue () == pControl->getMax ())
			{
				showSettingsDialog ();
			}
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------
void UIBitmapsController::dbSelectionChanged (int32_t selectedRow, GenericStringListDataBrowserSource* source)
{
	if (dataSource)
	{
		CBitmap* bitmap = dataSource->getSelectedBitmap ();
		UTF8StringPtr selectedBitmapName = dataSource->getSelectedBitmapName ();
		if (bitmapView)
		{
			bitmapView->setBackground (bitmap);
			if (bitmapView->getParentView ())
				bitmapView->getParentView ()->invalid ();
		}
		if (bitmapPathEdit)
		{
			bitmapPathEdit->setText (bitmap ? bitmap->getResourceDescription ().u.name : 0);
			bitmapPathEdit->setMouseEnabled (selectedBitmapName ? true : false);
		}
		if (settingButton)
		{
			settingButton->setMouseEnabled (selectedBitmapName ? true : false);
		}
	}
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsController::valueToString (float value, char utf8String[256], void* userData)
{
	int32_t intValue = (int32_t)value;
	std::stringstream str;
	str << intValue;
	strcpy (utf8String, str.str ().c_str ());
	return true;
}

//----------------------------------------------------------------------------------------------------
bool UIBitmapsController::stringToValue (UTF8StringPtr txt, float& result, void* userData)
{
	int32_t value = txt ? (int32_t)strtol (txt, 0, 10) : 0;
	result = (float)value;
	return true;
}

} // namespace

#endif // VSTGUI_LIVE_EDITING
