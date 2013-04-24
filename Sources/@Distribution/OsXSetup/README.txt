------------------------------------------------------------------------------------------
HoaLibrary by Julien Colafrancesco, Pierre Guillot & Eliott Paris at CICM / Universite Paris 8 - 2012-2013
-----------------
The HoaLibrary (high order ambisonics library) is a two dimensional high order ambisonics processing set of externals and patches for Max/MSP. It allows you to synthesize, transform and modulate sound fields.
It has been elaborated to facilitate the use of the sphericals harmonics and the routing in the ambisonic domain for musicians and composers.  
Thus, they should be able to let their creativity run free.
------------------------------------------------------------------------------------------


-----------------
MANUAL INSTALLATION :
-----------------

If you have already install a previous version of the library, to avoid conflicts, please delete all the old hoa files by running the uninstaller (HoaLibrary/MaxMsp/Max/Cycling '74/HoaLibrary/uninstaller).
or just :
 - delete {your max app path}/Cycling '74/HoaLibrary/externals/jsExternals/hoa.trajectory.js
 - delete {your max app path}/Cycling '74/HoaLibrary/helps/hoa.trajectory.maxhelp
 - delete {your max app path}/Cycling '74/HoaLibrary/effects/hoa.wider~.maxpat

-----------------
OsX Install :
-----------------

Firt please delete all windows files :
 - the .mxe files in the package (\Max\Cycling '74\extensions) and (Max\Cycling '74\HoaLibrary\externals\Windows).
Now you can put all folders of the package in your max application like below :
 - "Cycling '74/HoaLibrary" folder go to max "Cycling '74/" folder
 - the content of "Cycling '74/extension" go to the max "Cycling '74/extension" folder
 - the content of "Cycling '74/init" go to the max "Cycling '74/init" folder
 - the content of "Cycling '74/object-palettes" go to the max "Cycling '74/object-palettes" folder
 - the content of "exemples/" go to the max "exemples/" folder
 - the content of "patches/clippings/" go to the max "patches/clippings/" folder
 - the content of "patches/docs/refpages" go to the max "patches/docs/refpages" folder
 - the content of "patches/extras/" go to the max "patches/extras" folder
 - the content of "patches/object-prototypes" go to the max "patches/object-prototypes" folder
 
You can also copy just part of the package but we recommend to include all the files and to respect the paths.
The "HrtfDatabase" folder must be put in "/Library/Application Support/CicmLibrary/". If the "CicmLibrary" don't exist please create it.


-----------------
Windows Install :
-----------------

Firt please delete the .mxo files in the package (\Max\Cycling '74\extensions and Max\Cycling '74\HoaLibrary\externals\Osx).
Now you can put all folders of the package in your max application like below :
 - "Cycling '74/HoaLibrary" folder go to max "Cycling '74/" folder
 - the content of "Cycling '74/extension" go to the max "Cycling '74/extension" folder
 - the content of "Cycling '74/init" go to the max "Cycling '74/init" folder
 - the content of "Cycling '74/object-palettes" go to the max "Cycling '74/object-palettes" folder
 - the content of "exemples/" go to the max "exemples/" folder
 - the content of "patches/clippings/" go to the max "patches/clippings/" folder
 - the content of "patches/docs/refpages" go to the max "patches/docs/refpages" folder
 - the content of "patches/extras/" go to the max "patches/extras" folder
 - the content of "patches/object-prototypes" go to the max "patches/object-prototypes" folder

We recommend to include all the files and to respect the paths but you can also copy just part of the package.
The "HrtfDatabase" folder must be put in "C:/ProgramData/CicmLibrary/". If the "CicmLibrary" don't exist please create it.


-----------------

Feedback are welcome.

jcolafrancesco@gmail.com
guillotpierre6@gmail.com
eliottparis@gmail.com
-----------------

http://www.mshparisnord.fr/hoalibrary/contacts/
