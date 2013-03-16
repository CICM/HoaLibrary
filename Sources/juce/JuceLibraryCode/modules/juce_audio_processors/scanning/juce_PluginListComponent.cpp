/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

PluginListComponent::PluginListComponent (AudioPluginFormatManager& manager,
                                          KnownPluginList& listToEdit,
                                          const File& deadMansPedal,
                                          PropertiesFile* const properties)
    : formatManager (manager),
      list (listToEdit),
      deadMansPedalFile (deadMansPedal),
      optionsButton ("Options..."),
      propertiesToUse (properties),
      scanOnBackgroundThread (false)
{
    listBox.setModel (this);
    addAndMakeVisible (&listBox);

    addAndMakeVisible (&optionsButton);
    optionsButton.addListener (this);
    optionsButton.setTriggeredOnMouseDown (true);

    setSize (400, 600);
    list.addChangeListener (this);
    updateList();

    PluginDirectoryScanner::applyBlacklistingsFromDeadMansPedal (list, deadMansPedalFile);
    deadMansPedalFile.deleteFile();
}

PluginListComponent::~PluginListComponent()
{
    list.removeChangeListener (this);
}

void PluginListComponent::setOptionsButtonText (const String& newText)
{
    optionsButton.setButtonText (newText);
    resized();
}

void PluginListComponent::setScansOnMessageThread (bool useMessageThread) noexcept
{
    scanOnBackgroundThread = ! useMessageThread;
}

void PluginListComponent::resized()
{
    listBox.setBounds (0, 0, getWidth(), getHeight() - 30);
    optionsButton.changeWidthToFitText (24);
    optionsButton.setTopLeftPosition (0, getHeight() - 28);
}

void PluginListComponent::changeListenerCallback (ChangeBroadcaster*)
{
    updateList();
}

void PluginListComponent::updateList()
{
    listBox.updateContent();
    listBox.repaint();
}

int PluginListComponent::getNumRows()
{
    return list.getNumTypes() + list.getBlacklistedFiles().size();
}

void PluginListComponent::paintListBoxItem (int row, Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll (findColour (TextEditor::highlightColourId));

    String name, desc;
    bool isBlacklisted = false;

    if (row >= list.getNumTypes())
    {
        isBlacklisted = true;
        name = list.getBlacklistedFiles() [row - list.getNumTypes()];
        desc = TRANS("Deactivated after failing to initialise correctly");
    }
    else if (const PluginDescription* const pd = list.getType (row))
    {
        name = pd->name;

        desc << pd->pluginFormatName
             << (pd->isInstrument ? " instrument" : " effect")
             << " - " << pd->numInputChannels  << (pd->numInputChannels  == 1 ? " in"  : " ins")
             << " / " << pd->numOutputChannels << (pd->numOutputChannels == 1 ? " out" : " outs");

        if (pd->manufacturerName.isNotEmpty())  desc << " - " << pd->manufacturerName;
        if (pd->version.isNotEmpty())           desc << " - " << pd->version;
        if (pd->category.isNotEmpty())          desc << " - category: '" << pd->category << '\'';
    }

    if (name.isNotEmpty())
    {
        GlyphArrangement ga;
        ga.addCurtailedLineOfText (Font (height * 0.7f, Font::bold),
                                   name, 8.0f, height * 0.8f, width - 10.0f, true);

        g.setColour (isBlacklisted ? Colours::red : Colours::black);
        ga.draw (g);

        const Rectangle<float> bb (ga.getBoundingBox (0, -1, false));

        ga.clear();
        ga.addCurtailedLineOfText (Font (height * 0.6f), desc,
                                   jmax (bb.getRight() + 10.0f, width / 3.0f), height * 0.8f,
                                   width - bb.getRight() - 12.0f, true);

        g.setColour (isBlacklisted ? Colours::red : Colours::grey);
        ga.draw (g);
    }
}

static void removePluginItem (KnownPluginList& list, int index)
{
    if (index < list.getNumTypes())
        list.removeType (index);
    else
        list.removeFromBlacklist (list.getBlacklistedFiles() [index - list.getNumTypes()]);
}

void PluginListComponent::deleteKeyPressed (int lastRowSelected)
{
    removePluginItem (list, lastRowSelected);
}

void PluginListComponent::removeSelected()
{
    const SparseSet <int> selected (listBox.getSelectedRows());

    for (int i = list.getNumTypes(); --i >= 0;)
        if (selected.contains (i))
            removePluginItem (list, i);
}

bool PluginListComponent::canShowSelectedFolder() const
{
    if (const PluginDescription* const desc = list.getType (listBox.getSelectedRow()))
        return File::createFileWithoutCheckingPath (desc->fileOrIdentifier).exists();

    return false;
}

void PluginListComponent::showSelectedFolder()
{
    if (canShowSelectedFolder())
        if (const PluginDescription* const desc = list.getType (listBox.getSelectedRow()))
            File (desc->fileOrIdentifier).getParentDirectory().startAsProcess();
}

void PluginListComponent::removeMissingPlugins()
{
    for (int i = list.getNumTypes(); --i >= 0;)
        if (! formatManager.doesPluginStillExist (*list.getType (i)))
            list.removeType (i);
}

void PluginListComponent::optionsMenuStaticCallback (int result, PluginListComponent* pluginList)
{
    if (pluginList != nullptr)
        pluginList->optionsMenuCallback (result);
}

void PluginListComponent::optionsMenuCallback (int result)
{
    switch (result)
    {
        case 0:   break;
        case 1:   list.clear(); break;
        case 2:   list.sort (KnownPluginList::sortAlphabetically); break;
        case 3:   list.sort (KnownPluginList::sortByCategory); break;
        case 4:   list.sort (KnownPluginList::sortByManufacturer); break;
        case 5:   removeSelected(); break;
        case 6:   showSelectedFolder(); break;
        case 7:   removeMissingPlugins(); break;

        default:  scanFor (formatManager.getFormat (result - 10)); break;
    }
}

void PluginListComponent::buttonClicked (Button* button)
{
    if (button == &optionsButton)
    {
        PopupMenu menu;
        menu.addItem (1, TRANS("Clear list"));
        menu.addItem (5, TRANS("Remove selected plug-in from list"), listBox.getNumSelectedRows() > 0);
        menu.addItem (6, TRANS("Show folder containing selected plug-in"), canShowSelectedFolder());
        menu.addItem (7, TRANS("Remove any plug-ins whose files no longer exist"));
        menu.addSeparator();
        menu.addItem (2, TRANS("Sort alphabetically"));
        menu.addItem (3, TRANS("Sort by category"));
        menu.addItem (4, TRANS("Sort by manufacturer"));
        menu.addSeparator();

        for (int i = 0; i < formatManager.getNumFormats(); ++i)
        {
            AudioPluginFormat* const format = formatManager.getFormat (i);

            if (format->canScanForPlugins())
                menu.addItem (10 + i, "Scan for new or updated " + format->getName() + " plug-ins");
        }

        menu.showMenuAsync (PopupMenu::Options().withTargetComponent (&optionsButton),
                            ModalCallbackFunction::forComponent (optionsMenuStaticCallback, this));
    }
}

bool PluginListComponent::isInterestedInFileDrag (const StringArray& /*files*/)
{
    return true;
}

void PluginListComponent::filesDropped (const StringArray& files, int, int)
{
    OwnedArray <PluginDescription> typesFound;
    list.scanAndAddDragAndDroppedFiles (formatManager, files, typesFound);
}

//==============================================================================
class PluginListComponent::Scanner    : private Timer,
                                        private Thread
{
public:
    Scanner (PluginListComponent& plc,
             AudioPluginFormat& format,
             PropertiesFile* properties,
             bool useThread)
        : Thread ("plugin_scan"),
          owner (plc), formatToScan (format), propertiesToUse (properties),
          pathChooserWindow (TRANS("Select folders to scan..."), String::empty, AlertWindow::NoIcon),
          progressWindow (TRANS("Scanning for plug-ins..."),
                          TRANS("Searching for all possible plug-in files..."), AlertWindow::NoIcon),
          progress (0.0), shouldUseThread (useThread), finished (false)
    {
        FileSearchPath path (formatToScan.getDefaultLocationsToSearch());

        if (path.getNumPaths() > 0) // if the path is empty, then paths aren't used for this format.
        {
            if (propertiesToUse != nullptr)
                path = propertiesToUse->getValue ("lastPluginScanPath_" + formatToScan.getName(), path.toString());

            pathList.setSize (500, 300);
            pathList.setPath (path);

            pathChooserWindow.addCustomComponent (&pathList);
            pathChooserWindow.addButton (TRANS("Scan"),   1, KeyPress (KeyPress::returnKey));
            pathChooserWindow.addButton (TRANS("Cancel"), 0, KeyPress (KeyPress::escapeKey));

            pathChooserWindow.enterModalState (true,
                ModalCallbackFunction::forComponent (startScanCallback, &pathChooserWindow, this),
                false);
        }
        else
        {
            startScan();
        }
    }

    ~Scanner()
    {
        stopThread (10000);
    }

private:
    static void startScanCallback (int result, AlertWindow* alert, Scanner* scanner)
    {
        if (alert != nullptr && scanner != nullptr)
        {
            if (result != 0)
                scanner->startScan();
            else
                scanner->finishedScan();
        }
    }

    void startScan()
    {
        pathChooserWindow.setVisible (false);

        scanner = new PluginDirectoryScanner (owner.list, formatToScan, pathList.getPath(),
                                              true, owner.deadMansPedalFile);

        if (propertiesToUse != nullptr)
        {
            propertiesToUse->setValue ("lastPluginScanPath_" + formatToScan.getName(), pathList.getPath().toString());
            propertiesToUse->saveIfNeeded();
        }

        progressWindow.addButton (TRANS("Cancel"), 0, KeyPress (KeyPress::escapeKey));
        progressWindow.addProgressBarComponent (progress);
        progressWindow.enterModalState();

        if (shouldUseThread)
            startThread();

        startTimer (20);
    }

    void finishedScan()
    {
        owner.scanFinished (scanner != nullptr ? scanner->getFailedFiles()
                                               : StringArray());
    }

    void timerCallback()
    {
        if (! isThreadRunning())
        {
            if (doNextScan())
                startTimer (20);
        }

        if (! progressWindow.isCurrentlyModal())
            finished = true;

        if (finished)
            finishedScan();
        else
            progressWindow.setMessage (progressMessage);
    }

    void run()
    {
        while (doNextScan() && ! threadShouldExit())
        {}
    }

    bool doNextScan()
    {
        progressMessage = TRANS("Testing:\n\n") + scanner->getNextPluginFileThatWillBeScanned();

        if (scanner->scanNextFile (true))
        {
            progress = scanner->getProgress();
            return true;
        }

        finished = true;
        return false;
    }

    PluginListComponent& owner;
    AudioPluginFormat& formatToScan;
    PropertiesFile* propertiesToUse;
    ScopedPointer<PluginDirectoryScanner> scanner;
    AlertWindow pathChooserWindow, progressWindow;
    FileSearchPathListComponent pathList;
    String progressMessage;
    double progress;
    bool shouldUseThread, finished;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scanner)
};

void PluginListComponent::scanFor (AudioPluginFormat* format)
{
    if (format != nullptr)
        currentScanner = new Scanner (*this, *format, propertiesToUse, scanOnBackgroundThread);
}

void PluginListComponent::scanFinished (const StringArray& failedFiles)
{
    StringArray shortNames;

    for (int i = 0; i < failedFiles.size(); ++i)
        shortNames.add (File::createFileWithoutCheckingPath (failedFiles[i]).getFileName());

    currentScanner = nullptr; // mustn't delete this before using the failed files array

    if (shortNames.size() > 0)
        AlertWindow::showMessageBoxAsync (AlertWindow::InfoIcon,
                                          TRANS("Scan complete"),
                                          TRANS("Note that the following files appeared to be plugin files, but failed to load correctly:\n\n")
                                            + shortNames.joinIntoString (", "));
}
