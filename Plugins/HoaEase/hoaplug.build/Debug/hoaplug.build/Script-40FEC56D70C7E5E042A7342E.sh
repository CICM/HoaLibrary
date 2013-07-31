#!/bin/sh

# This script takes the build product and copies it to the AU, VST, and RTAS folders, depending on 
# which plugin types you've built

original=$CONFIGURATION_BUILD_DIR/$FULL_PRODUCT_NAME

# this looks inside the binary to detect which platforms are needed.. 
copyAU=`nm -g "$CONFIGURATION_BUILD_DIR/$EXECUTABLE_PATH" | grep -i 'AudioUnit' | wc -l`
copyVST=`nm -g "$CONFIGURATION_BUILD_DIR/$EXECUTABLE_PATH" | grep -i 'VSTPlugin' | wc -l`
copyRTAS=`nm -g "$CONFIGURATION_BUILD_DIR/$EXECUTABLE_PATH" | grep -i 'CProcess' | wc -l`
copyAAX=`nm -g "$CONFIGURATION_BUILD_DIR/$EXECUTABLE_PATH" | grep -i 'GetEffectDescriptions' | wc -l`

if [ $copyAU -gt 0 ]; then
  echo "Copying to AudioUnit folder..."
  AU=~/Library/Audio/Plug-Ins/Components/$PRODUCT_NAME.component
  if [ -d "$AU" ]; then 
    rm -r "$AU"
  fi

  cp -r "$original" "$AU"
  sed -i "" -e 's/TDMwPTul/BNDLPTul/g' "$AU/Contents/PkgInfo"
  sed -i "" -e 's/TDMw/BNDL/g' "$AU/Contents/$INFOPLIST_FILE"
fi

if [ $copyVST -gt 0 ]; then
  echo "Copying to VST folder..."
  VST=~/Library/Audio/Plug-Ins/VST/$PRODUCT_NAME.vst
  if [ -d "$VST" ]; then 
    rm -r "$VST"
  fi

  cp -r "$original" "$VST"
  sed -i "" -e 's/TDMwPTul/BNDLPTul/g' "$VST/Contents/PkgInfo"
  sed -i "" -e 's/TDMw/BNDL/g' "$VST/Contents/$INFOPLIST_FILE"
fi

if [ $copyRTAS -gt 0 ]; then
  echo "Copying to RTAS folder..."
  RTAS=/Library/Application\ Support/Digidesign/Plug-Ins/$PRODUCT_NAME.dpm
  if [ -d "$RTAS" ]; then
    rm -r "$RTAS"
  fi

  cp -r "$original" "$RTAS"
fi

if [ $copyAAX -gt 0 ]; then
  echo "Copying to AAX folder..."

  if [ -d "/Applications/ProTools_3PDev/Plug-Ins" ]; then
    AAX1="/Applications/ProTools_3PDev/Plug-Ins/$PRODUCT_NAME.aaxplugin"

    if [ -d "$AAX1" ]; then
      rm -r "$AAX1"
    fi

    cp -r "$original" "$AAX1"
  fi

  if [ -d "/Library/Application Support/Avid/Audio/Plug-Ins" ]; then
    AAX2="/Library/Application Support/Avid/Audio/Plug-Ins/$PRODUCT_NAME.aaxplugin"

    if [ -d "$AAX2" ]; then
      rm -r "$AAX2"
    fi

    cp -r "$original" "$AAX2"
  fi
fi

