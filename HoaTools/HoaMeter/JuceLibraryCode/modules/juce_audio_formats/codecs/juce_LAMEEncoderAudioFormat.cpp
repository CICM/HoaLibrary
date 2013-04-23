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

#if JUCE_USE_LAME_AUDIO_FORMAT

class LAMEEncoderAudioFormat::Writer   : public AudioFormatWriter
{
public:
    Writer (OutputStream* destStream, const String& formatName,
            const File& lameApp, int vbr, int cbr,
            double sampleRate, unsigned int numberOfChannels,
            unsigned int bitsPerSample, const StringPairArray& metadata)
        : AudioFormatWriter (destStream, formatName, sampleRate,
                             numberOfChannels, bitsPerSample),
          vbrLevel (vbr), cbrBitrate (cbr),
          tempWav (".wav")
    {
        WavAudioFormat wavFormat;

        if (FileOutputStream* out = tempWav.getFile().createOutputStream())
        {
            writer = wavFormat.createWriterFor (out, sampleRate, numChannels,
                                                bitsPerSample, metadata, 0);

            args.add (lameApp.getFullPathName());

            args.add ("--quiet");

            if (cbrBitrate == 0)
            {
                args.add ("-vbr-new");
                args.add ("-V");
                args.add (String (vbrLevel));
            }
            else
            {
                args.add ("--cbr");
                args.add ("-b");
                args.add (String (cbrBitrate));
            }

            addMetadataArg (metadata, "id3title",       "--tt");
            addMetadataArg (metadata, "id3artist",      "--ta");
            addMetadataArg (metadata, "id3album",       "--tl");
            addMetadataArg (metadata, "id3comment",     "--tc");
            addMetadataArg (metadata, "id3date",        "--ty");
            addMetadataArg (metadata, "id3genre",       "--tg");
            addMetadataArg (metadata, "id3trackNumber", "--tn");
        }
    }

    void addMetadataArg (const StringPairArray& metadata, const char* key, const char* lameFlag)
    {
        const String value (metadata.getValue (key, String::empty));

        if (value.isNotEmpty())
        {
            args.add (lameFlag);
            args.add (value);
        }
    }

    ~Writer()
    {
        if (writer != nullptr)
        {
            writer = nullptr;

            if (! convertToMP3())
                convertToMP3(); // try again
        }
    }

    bool write (const int** samplesToWrite, int numSamples)
    {
        return writer != nullptr && writer->write (samplesToWrite, numSamples);
    }

private:
    int vbrLevel, cbrBitrate;
    TemporaryFile tempWav;
    ScopedPointer<AudioFormatWriter> writer;
    StringArray args;

    bool convertToMP3() const
    {
        TemporaryFile tempMP3 (".mp3");

        StringArray args2 (args);
        args2.add (tempWav.getFile().getFullPathName());
        args2.add (tempMP3.getFile().getFullPathName());

        ChildProcess cp;

        DBG (args2.joinIntoString(" "));

        if (cp.start (args2))
        {
            String childOutput (cp.readAllProcessOutput());
            DBG (childOutput);

            if (tempMP3.getFile().getSize() > 0)
            {
                FileInputStream fis (tempMP3.getFile());

                if (fis.openedOk() && output->writeFromInputStream (fis, -1) > 0)
                {
                    output->flush();
                    return true;
                }
            }
        }

        return false;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Writer)
};

//==============================================================================
static const char* const lameFormatName = "MP3 file";
static const char* const lameExtensions[] = { ".mp3", nullptr };

LAMEEncoderAudioFormat::LAMEEncoderAudioFormat (const File& lameApplication)
   : AudioFormat (TRANS (lameFormatName), StringArray (lameExtensions)),
     lameApp (lameApplication)
{
}

LAMEEncoderAudioFormat::~LAMEEncoderAudioFormat()
{
}

bool LAMEEncoderAudioFormat::canHandleFile (const File&)
{
    return false;
}

Array<int> LAMEEncoderAudioFormat::getPossibleSampleRates()
{
    const int rates[] = { 32000, 44100, 48000, 0 };
    return Array <int> (rates);
}

Array<int> LAMEEncoderAudioFormat::getPossibleBitDepths()
{
    const int depths[] = { 16, 0 };
    return Array <int> (depths);
}

bool LAMEEncoderAudioFormat::canDoStereo()      { return true; }
bool LAMEEncoderAudioFormat::canDoMono()        { return true; }
bool LAMEEncoderAudioFormat::isCompressed()     { return true; }

StringArray LAMEEncoderAudioFormat::getQualityOptions()
{
    const char* vbrOptions[] = { "VBR quality 0 (best)", "VBR quality 1", "VBR quality 2", "VBR quality 3",
                                 "VBR quality 4 (normal)", "VBR quality 5", "VBR quality 6", "VBR quality 7", "VBR quality 8",
                                 "VBR quality 9 (smallest)",
                                 nullptr };

    StringArray opts (vbrOptions);

    const int cbrRates[] = { 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 };

    for (int i = 0; i < numElementsInArray (cbrRates); ++i)
        opts.add (String (cbrRates[i]) + " Kb/s CBR");

    return opts;
}

AudioFormatReader* LAMEEncoderAudioFormat::createReaderFor (InputStream*, const bool)
{
    return nullptr;
}

AudioFormatWriter* LAMEEncoderAudioFormat::createWriterFor (OutputStream* streamToWriteTo,
                                                            double sampleRateToUse,
                                                            unsigned int numberOfChannels,
                                                            int bitsPerSample,
                                                            const StringPairArray& metadataValues,
                                                            int qualityOptionIndex)
{
    int vbr = 4;
    int cbr = 0;

    const String qual (getQualityOptions() [qualityOptionIndex]);

    if (qual.contains ("VBR"))
        vbr = qual.retainCharacters ("0123456789").getIntValue();
    else
        cbr = qual.getIntValue();

    return new Writer (streamToWriteTo, getFormatName(), lameApp, vbr, cbr,
                       sampleRateToUse, numberOfChannels, bitsPerSample, metadataValues);
}

#endif
