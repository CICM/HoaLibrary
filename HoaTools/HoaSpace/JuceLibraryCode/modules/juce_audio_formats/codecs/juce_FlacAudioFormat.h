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

#if JUCE_USE_FLAC || defined (DOXYGEN)

//==============================================================================
/**
    Reads and writes the lossless-compression FLAC audio format.

    To compile this, you'll need to set the JUCE_USE_FLAC flag.

    @see AudioFormat
*/
class JUCE_API  FlacAudioFormat    : public AudioFormat
{
public:
    //==============================================================================
    FlacAudioFormat();
    ~FlacAudioFormat();

    //==============================================================================
    Array<int> getPossibleSampleRates();
    Array<int> getPossibleBitDepths();
    bool canDoStereo();
    bool canDoMono();
    bool isCompressed();
    StringArray getQualityOptions();

    //==============================================================================
    AudioFormatReader* createReaderFor (InputStream* sourceStream,
                                        bool deleteStreamIfOpeningFails);

    AudioFormatWriter* createWriterFor (OutputStream* streamToWriteTo,
                                        double sampleRateToUse,
                                        unsigned int numberOfChannels,
                                        int bitsPerSample,
                                        const StringPairArray& metadataValues,
                                        int qualityOptionIndex);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlacAudioFormat)
};


#endif
