#!/bin/bash
# This file must be saved in UTF-8


################################
# Uninstallations Methodes
################################
function remove6 {
	echo "Removing HoaLibrary for Max6";
	doRemove;
}

function doRemove {
	echo -ne "- HoaLibrary Installer Receipt\n"
	#sudo rm -Rf "/Library/Receipts/HoaLibrary.pkg"
	sudo rm -Rf "/private/var/db/receipts"/com.cicm.hoalibrary.*
	echo -ne "... done.\n"
	
	if [ -e "$C74Folder" ] ; then
		echo -ne "- HoaLibrary Folder ($C74Folder/HoaLibrary/)"
		sudo rm -Rf "$C74Folder/HoaLibrary" && echo -ne "... done.\n"
		
		echo -ne "- Extension Files ($C74Folder/extensions/)"
		sudo rm -Rf "$C74Folder/extensions/"hoa.* && echo -ne "... done.\n"
		
		echo -ne "- Palettes Files ($C74Folder/object-palettes/)"
		sudo rm -Rf "$C74Folder/object-palettes/"hoa-palette.json && echo -ne "... done.\n"
		sudo rm -Rf "$C74Folder/object-palettes/"hoa.* && echo -ne "... done.\n"   
	fi
	

	if [ -e "$maxAppFolder" ] ; then
		
		echo -ne "- Clippings Files ($maxAppFolder/patches/clippings/HoaClippings)"
		sudo rm -Rf "$maxAppFolder/patches/clippings/HoaClippings" && echo -ne "... done.\n"

		echo -ne "- Extra Files ($maxAppFolder/patches/extras/HoaExtras)"
		sudo rm -Rf "$maxAppFolder/patches/extras/HoaExtras" && echo -ne "... done.\n"
		
		echo -ne "- Reference Files ($maxAppFolder/patches/HoaLibrary Reference/)"
		sudo rm -Rf "$maxAppFolder/patches/docs/refpages/hoa-ref" && echo -ne "... done.\n"
	fi
 
	echo -ne "\n";

}


################################
# UnInstallation process
################################
clear

echo "------------------------------"
echo "--- HoaLibrary Uninstaller ---"
echo "------------------------------"
echo ""
echo "Hi $USER..."
echo "You must run this script as an Admin user, and may be prompted for your password."
echo ""


################################
#  Version checking
################################
whichVersion=0;

maxAppFolder="/Applications/Max6";
C74Folder="$maxAppFolder/Cycling '74"; 
#HoaLibrary="$maxAppFolder/Cycling '74/extensions/hoa.loader.mxo";
remove6;

echo -ne "done"
echo -ne "\n\nend of HoaLibrary Uninstaller.\n"
echo -ne "(you can quit the Terminal now...)\n"

exit 0;
