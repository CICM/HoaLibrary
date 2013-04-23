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

//==============================================================================
static const char* const aiffFormatName = "AIFF file";
static const char* const aiffExtensions[] = { ".aiff", ".aif", 0 };

//==============================================================================
namespace AiffFileHelpers
{
    inline int chunkName (const char* const name)   { return (int) ByteOrder::littleEndianInt (name); }

   #if JUCE_MSVC
    #pragma pack (push, 1)
   #endif

    //==============================================================================
    struct InstChunk
    {
        struct Loop
        {
            uint16 type; // these are different in AIFF and WAV
            uint16 startIdentifier;
            uint16 endIdentifier;
        } JUCE_PACKED;

        int8 baseNote;
        int8 detune;
        int8 lowNote;
        int8 highNote;
        int8 lowVelocity;
        int8 highVelocity;
        int16 gain;
        Loop sustainLoop;
        Loop releaseLoop;

        void copyTo (StringPairArray& values) const
        {
            values.set ("MidiUnityNote",        String (baseNote));
            values.set ("Detune",               String (detune));

            values.set ("LowNote",              String (lowNote));
            values.set ("HighNote",             String (highNote));
            values.set ("LowVelocity",          String (lowVelocity));
            values.set ("HighVelocity",         String (highVelocity));

            values.set ("Gain",                 String ((int16) ByteOrder::swapIfLittleEndian ((uint16) gain)));

            values.set ("NumSampleLoops",       String (2));        // always 2 with AIFF, WAV can have more
            values.set ("Loop0Type",            String (ByteOrder::swapIfLittleEndian (sustainLoop.type)));
            values.set ("Loop0StartIdentifier", String (ByteOrder::swapIfLittleEndian (sustainLoop.startIdentifier)));
            values.set ("Loop0EndIdentifier",   String (ByteOrder::swapIfLittleEndian (sustainLoop.endIdentifier)));
            values.set ("Loop1Type",            String (ByteOrder::swapIfLittleEndian (releaseLoop.type)));
            values.set ("Loop1StartIdentifier", String (ByteOrder::swapIfLittleEndian (releaseLoop.startIdentifier)));
            values.set ("Loop1EndIdentifier",   String (ByteOrder::swapIfLittleEndian (releaseLoop.endIdentifier)));
        }

        static uint16 getValue16 (const StringPairArray& values, const char* name, const char* def)
        {
            return ByteOrder::swapIfLittleEndian ((uint16) values.getValue (name, def).getIntValue());
        }

        static int8 getValue8 (const StringPairArray& values, const char* name, const char* def)
        {
            return (int8) values.getValue (name, def).getIntValue();
        }

        static void create (MemoryBlock& block, const StringPairArray& values)
        {
            if (values.getAllKeys().contains ("MidiUnityNote", true))
            {
                block.setSize ((sizeof (InstChunk) + 3) & ~(size_t) 3, true);
                InstChunk& inst = *static_cast <InstChunk*> (block.getData());

                inst.baseNote      = getValue8 (values, "MidiUnityNote", "60");
                inst.detune        = getValue8 (values, "Detune", "0");
                inst.lowNote       = getValue8 (values, "LowNote", "0");
                inst.highNote      = getValue8 (values, "HighNote", "127");
                inst.lowVelocity   = getValue8 (values, "LowVelocity", "1");
                inst.highVelocity  = getValue8 (values, "HighVelocity", "127");
                inst.gain          = (int16) getValue16 (values, "Gain", "0");

                inst.sustainLoop.type              = getValue16 (values, "Loop0Type", "0");
                inst.sustainLoop.startIdentifier   = getValue16 (values, "Loop0StartIdentifier", "0");
                inst.sustainLoop.endIdentifier     = getValue16 (values, "Loop0EndIdentifier", "0");
                inst.releaseLoop.type              = getValue16 (values, "Loop1Type", "0");
                inst.releaseLoop.startIdentifier   = getValue16 (values, "Loop1StartIdentifier", "0");
                inst.releaseLoop.endIdentifier     = getValue16 (values, "Loop1EndIdentifier", "0");
            }
        }

    } JUCE_PACKED;

   #if JUCE_MSVC
    #pragma pack (pop)
   #endif

    //==============================================================================
    namespace MarkChunk
    {
        static bool metaDataContainsZeroIdentifiers (const StringPairArray& values)
        {
            // (zero cue identifiers are valid for WAV but not for AIFF)
            const String cueString ("Cue");
            const String noteString ("CueNote");
            const String identifierString ("Identifier");

            const StringArray& keys = values.getAllKeys();

            for (int i = 0; i < keys.size(); ++i)
            {
                const String key (keys[i]);

                if (key.startsWith (noteString))
                    continue; // zero identifier IS valid in a COMT chunk

                if (key.startsWith (cueString) && key.contains (identifierString))
                {
                    const int value = values.getValue (key, "-1").getIntValue();

                    if (value == 0)
                        return true;
                }
            }

            return false;
        }

        static void create (MemoryBlock& block, const StringPairArray& values)
        {
            const int numCues = values.getValue ("NumCuePoints", "0").getIntValue();

            if (numCues > 0)
            {
                MemoryOutputStream out (block, false);

                out.writeShortBigEndian ((short) numCues);

                const int numCueLabels = values.getValue ("NumCueLabels", "0").getIntValue();
                const int idOffset = metaDataContainsZeroIdentifiers (values) ? 1 : 0; // can't have zero IDs in AIFF

               #if JUCE_DEBUG
                Array<int> identifiers;
               #endif

                for (int i = 0; i < numCues; ++i)
                {
                    const String prefixCue ("Cue" + String (i));
                    const int identifier = idOffset + values.getValue (prefixCue + "Identifier", "1").getIntValue();

                   #if JUCE_DEBUG
                    jassert (! identifiers.contains (identifier));
                    identifiers.add (identifier);
                   #endif

                    const int offset = values.getValue (prefixCue + "Offset", "0").getIntValue();
                    String label ("CueLabel" + String (i));

                    for (int labelIndex = 0; labelIndex < numCueLabels; ++labelIndex)
                    {
                        const String prefixLabel ("CueLabel" + String (labelIndex));
                        const int labelIdentifier = idOffset + values.getValue (prefixLabel + "Identifier", "1").getIntValue();

                        if (labelIdentifier == identifier)
                        {
                            label = values.getValue (prefixLabel + "Text", label);
                            break;
                        }
                    }

                    out.writeShortBigEndian ((short) identifier);
                    out.writeIntBigEndian (offset);

                    const size_t labelLength = jmin ((size_t) 254, label.getNumBytesAsUTF8()); // seems to need null terminator even though it's a pstring
                    out.writeByte ((char) labelLength + 1);
                    out.write (label.toUTF8(), labelLength);
                    out.writeByte (0);
                }

                if ((out.getDataSize() & 1) != 0)
                    out.writeByte (0);
            }
        }
    }

    //==============================================================================
    namespace COMTChunk
    {
        static void create (MemoryBlock& block, const StringPairArray& values)
        {
            const int numNotes = values.getValue ("NumCueNotes", "0").getIntValue();

            if (numNotes > 0)
            {
                MemoryOutputStream out (block, false);
                out.writeShortBigEndian ((short) numNotes);

                for (int i = 0; i < numNotes; ++i)
                {
                    const String prefix ("CueNote" + String (i));

                    out.writeIntBigEndian (values.getValue (prefix + "TimeStamp", "0").getIntValue());
                    out.writeShortBigEndian ((short) values.getValue (prefix + "Identifier", "0").getIntValue());

                    const String comment (values.getValue (prefix + "Text", String::empty));

                    const size_t commentLength = jmin (comment.getNumBytesAsUTF8(), (size_t) 65534);
                    out.writeShortBigEndian ((short) commentLength + 1);
                    out.write (comment.toUTF8(), commentLength);
                    out.writeByte (0);

                    if ((out.getDataSize() & 1) != 0)
                        out.writeByte (0);
                }
            }
        }
    }
}

//==============================================================================
class AiffAudioFormatReader  : public AudioFormatReader
{
public:
    AiffAudioFormatReader (InputStream* in)
        : AudioFormatReader (in, TRANS (aiffFormatName))
    {
        using namespace AiffFileHelpers;

        if (input->readInt() == chunkName ("FORM"))
        {
            const int len = input->readIntBigEndian();
            const int64 end = input->getPosition() + len;

            const int nextType = input->readInt();
            if (nextType == chunkName ("AIFF") || nextType == chunkName ("AIFC"))
            {
                bool hasGotVer = false;
                bool hasGotData = false;
                bool hasGotType = false;

                while (input->getPosition() < end)
                {
                    const int type = input->readInt();
                    const uint32 length = (uint32) input->readIntBigEndian();
                    const int64 chunkEnd = input->getPosition() + length;

                    if (type == chunkName ("FVER"))
                    {
                        hasGotVer = true;

                        const int ver = input->readIntBigEndian();
                        if (ver != 0 && ver != (int) 0xa2805140)
                            break;
                    }
                    else if (type == chunkName ("COMM"))
                    {
                        hasGotType = true;

                        numChannels = (unsigned int) input->readShortBigEndian();
                        lengthInSamples = input->readIntBigEndian();
                        bitsPerSample = (unsigned int) input->readShortBigEndian();
                        bytesPerFrame = (int) ((numChannels * bitsPerSample) >> 3);

                        unsigned char sampleRateBytes[10];
                        input->read (sampleRateBytes, 10);
                        const int byte0 = sampleRateBytes[0];

                        if ((byte0 & 0x80) != 0
                             || byte0 <= 0x3F || byte0 > 0x40
                             || (byte0 == 0x40 && sampleRateBytes[1] > 0x1C))
                            break;

                        unsigned int sampRate = ByteOrder::bigEndianInt (sampleRateBytes + 2);
                        sampRate >>= (16414 - ByteOrder::bigEndianShort (sampleRateBytes));
                        sampleRate = (int) sampRate;

                        if (length <= 18)
                        {
                            // some types don't have a chunk large enough to include a compression
                            // type, so assume it's just big-endian pcm
                            littleEndian = false;
                        }
                        else
                        {
                            const int compType = input->readInt();

                            if (compType == chunkName ("NONE") || compType == chunkName ("twos"))
                            {
                                littleEndian = false;
                            }
                            else if (compType == chunkName ("sowt"))
                            {
                                littleEndian = true;
                            }
                            else
                            {
                                sampleRate = 0;
                                break;
                            }
                        }
                    }
                    else if (type == chunkName ("SSND"))
                    {
                        hasGotData = true;

                        const int offset = input->readIntBigEndian();
                        dataChunkStart = input->getPosition() + 4 + offset;
                        lengthInSamples = (bytesPerFrame > 0) ? jmin (lengthInSamples, ((int64) length) / (int64) bytesPerFrame) : 0;
                    }
                    else if (type == chunkName ("MARK"))
                    {
                        const uint16 numCues = (uint16) input->readShortBigEndian();

                        // these two are always the same for AIFF-read files
                        metadataValues.set ("NumCuePoints", String (numCues));
                        metadataValues.set ("NumCueLabels", String (numCues));

                        for (uint16 i = 0; i < numCues; ++i)
                        {
                            uint16 identifier = (uint16) input->readShortBigEndian();
                            uint32 offset = (uint32) input->readIntBigEndian();
                            uint8 stringLength = (uint8) input->readByte();
                            MemoryBlock textBlock;
                            input->readIntoMemoryBlock (textBlock, stringLength);

                            // if the stringLength is even then read one more byte as the
                            // string needs to be an even number of bytes INCLUDING the
                            // leading length character in the pascal string
                            if ((stringLength & 1) == 0)
                                input->readByte();

                            const String prefixCue ("Cue" + String (i));
                            metadataValues.set (prefixCue + "Identifier", String (identifier));
                            metadataValues.set (prefixCue + "Offset", String (offset));

                            const String prefixLabel ("CueLabel" + String (i));
                            metadataValues.set (prefixLabel + "Identifier", String (identifier));
                            metadataValues.set (prefixLabel + "Text", textBlock.toString());
                        }
                    }
                    else if (type == chunkName ("COMT"))
                    {
                        const uint16 numNotes = (uint16) input->readShortBigEndian();
                        metadataValues.set ("NumCueNotes", String (numNotes));

                        for (uint16 i = 0; i < numNotes; ++i)
                        {
                            uint32 timestamp = (uint32) input->readIntBigEndian();
                            uint16 identifier = (uint16) input->readShortBigEndian(); // may be zero in this case
                            uint16 stringLength = (uint16) input->readShortBigEndian();

                            MemoryBlock textBlock;
                            input->readIntoMemoryBlock (textBlock, stringLength + (stringLength & 1));

                            const String prefix ("CueNote" + String (i));
                            metadataValues.set (prefix + "TimeStamp", String (timestamp));
                            metadataValues.set (prefix + "Identifier", String (identifier));
                            metadataValues.set (prefix + "Text", textBlock.toString());
                        }
                    }
                    else if (type == chunkName ("INST"))
                    {
                        HeapBlock <InstChunk> inst;
                        inst.calloc (jmax ((size_t) length + 1, sizeof (InstChunk)), 1);
                        input->read (inst, (int) length);
                        inst->copyTo (metadataValues);
                    }
                    else if ((hasGotVer && hasGotData && hasGotType)
                              || chunkEnd < input->getPosition()
                              || input->isExhausted())
                    {
                        break;
                    }

                    input->setPosition (chunkEnd + (chunkEnd & 1)); // (chunks should be aligned to an even byte address)
                }
            }
        }

        if (metadataValues.size() > 0)
            metadataValues.set ("MetaDataSource", "AIFF");
    }

    //==============================================================================
    bool readSamples (int** destSamples, int numDestChannels, int startOffsetInDestBuffer,
                      int64 startSampleInFile, int numSamples)
    {
        clearSamplesBeyondAvailableLength (destSamples, numDestChannels, startOffsetInDestBuffer,
                                           startSampleInFile, numSamples, lengthInSamples);

        if (numSamples <= 0)
            return true;

        input->setPosition (dataChunkStart + startSampleInFile * bytesPerFrame);

        while (numSamples > 0)
        {
            const int tempBufSize = 480 * 3 * 4; // (keep this a multiple of 3)
            char tempBuffer [tempBufSize];

            const int numThisTime = jmin (tempBufSize / bytesPerFrame, numSamples);
            const int bytesRead = input->read (tempBuffer, numThisTime * bytesPerFrame);

            if (bytesRead < numThisTime * bytesPerFrame)
            {
                jassert (bytesRead >= 0);
                zeromem (tempBuffer + bytesRead, (size_t) (numThisTime * bytesPerFrame - bytesRead));
            }

            jassert (! usesFloatingPointData); // (would need to add support for this if it's possible)

            if (littleEndian)
                copySampleData<AudioData::LittleEndian> (bitsPerSample, destSamples, startOffsetInDestBuffer,
                                                         numDestChannels, tempBuffer, (int) numChannels, numThisTime);
            else
                copySampleData<AudioData::BigEndian> (bitsPerSample, destSamples, startOffsetInDestBuffer,
                                                      numDestChannels, tempBuffer, (int) numChannels, numThisTime);


            startOffsetInDestBuffer += numThisTime;
            numSamples -= numThisTime;
        }

        return true;
    }

    template <typename Endianness>
    static void copySampleData (unsigned int bitsPerSample, int* const* destSamples, int startOffsetInDestBuffer, int numDestChannels,
                                const void* sourceData, int numChannels, int numSamples) noexcept
    {
        switch (bitsPerSample)
        {
            case 8:     ReadHelper<AudioData::Int32, AudioData::Int8,  Endianness>::read (destSamples, startOffsetInDestBuffer, numDestChannels, sourceData, numChannels, numSamples); break;
            case 16:    ReadHelper<AudioData::Int32, AudioData::Int16, Endianness>::read (destSamples, startOffsetInDestBuffer, numDestChannels, sourceData, numChannels, numSamples); break;
            case 24:    ReadHelper<AudioData::Int32, AudioData::Int24, Endianness>::read (destSamples, startOffsetInDestBuffer, numDestChannels, sourceData, numChannels, numSamples); break;
            case 32:    ReadHelper<AudioData::Int32, AudioData::Int32, Endianness>::read (destSamples, startOffsetInDestBuffer, numDestChannels, sourceData, numChannels, numSamples); break;
            default:    jassertfalse; break;
        }
    }

    int bytesPerFrame;
    int64 dataChunkStart;
    bool littleEndian;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AiffAudioFormatReader)
};

//==============================================================================
class AiffAudioFormatWriter  : public AudioFormatWriter
{
public:
    AiffAudioFormatWriter (OutputStream* out, double sampleRate_,
                           unsigned int numChans, unsigned int bits,
                           const StringPairArray& metadataValues)
        : AudioFormatWriter (out, TRANS (aiffFormatName), sampleRate_, numChans, bits),
          lengthInSamples (0),
          bytesWritten (0),
          writeFailed (false)
    {
        using namespace AiffFileHelpers;

        if (metadataValues.size() > 0)
        {
            // The meta data should have been santised for the AIFF format.
            // If it was originally sourced from a WAV file the MetaDataSource
            // key should be removed (or set to "AIFF") once this has been done
            jassert (metadataValues.getValue ("MetaDataSource", "None") != "WAV");

            MarkChunk::create (markChunk, metadataValues);
            COMTChunk::create (comtChunk, metadataValues);
            InstChunk::create (instChunk, metadataValues);
        }

        headerPosition = out->getPosition();
        writeHeader();
    }

    ~AiffAudioFormatWriter()
    {
        if ((bytesWritten & 1) != 0)
            output->writeByte (0);

        writeHeader();
    }

    //==============================================================================
    bool write (const int** data, int numSamples)
    {
        jassert (data != nullptr && *data != nullptr); // the input must contain at least one channel!

        if (writeFailed)
            return false;

        const size_t bytes = (size_t) numSamples * numChannels * bitsPerSample / 8;
        tempBlock.ensureSize ((size_t) bytes, false);

        switch (bitsPerSample)
        {
            case 8:     WriteHelper<AudioData::Int8,  AudioData::Int32, AudioData::BigEndian>::write (tempBlock.getData(), (int) numChannels, data, numSamples); break;
            case 16:    WriteHelper<AudioData::Int16, AudioData::Int32, AudioData::BigEndian>::write (tempBlock.getData(), (int) numChannels, data, numSamples); break;
            case 24:    WriteHelper<AudioData::Int24, AudioData::Int32, AudioData::BigEndian>::write (tempBlock.getData(), (int) numChannels, data, numSamples); break;
            case 32:    WriteHelper<AudioData::Int32, AudioData::Int32, AudioData::BigEndian>::write (tempBlock.getData(), (int) numChannels, data, numSamples); break;
            default:    jassertfalse; break;
        }

        if (bytesWritten + bytes >= (size_t) 0xfff00000
             || ! output->write (tempBlock.getData(), bytes))
        {
            // failed to write to disk, so let's try writing the header.
            // If it's just run out of disk space, then if it does manage
            // to write the header, we'll still have a useable file..
            writeHeader();
            writeFailed = true;
            return false;
        }
        else
        {
            bytesWritten += bytes;
            lengthInSamples += (uint64) numSamples;

            return true;
        }
    }

private:
    MemoryBlock tempBlock, markChunk, comtChunk, instChunk;
    uint64 lengthInSamples, bytesWritten;
    int64 headerPosition;
    bool writeFailed;

    void writeHeader()
    {
        using namespace AiffFileHelpers;

        const bool couldSeekOk = output->setPosition (headerPosition);
        (void) couldSeekOk;

        // if this fails, you've given it an output stream that can't seek! It needs
        // to be able to seek back to write the header
        jassert (couldSeekOk);

        const int headerLen = (int) (54 + (markChunk.getSize() > 0 ? markChunk.getSize() + 8 : 0)
                                        + (comtChunk.getSize() > 0 ? comtChunk.getSize() + 8 : 0)
                                        + (instChunk.getSize() > 0 ? instChunk.getSize() + 8 : 0));
        int audioBytes = (int) (lengthInSamples * ((bitsPerSample * numChannels) / 8));
        audioBytes += (audioBytes & 1);

        output->writeInt (chunkName ("FORM"));
        output->writeIntBigEndian (headerLen + audioBytes - 8);
        output->writeInt (chunkName ("AIFF"));
        output->writeInt (chunkName ("COMM"));
        output->writeIntBigEndian (18);
        output->writeShortBigEndian ((short) numChannels);
        output->writeIntBigEndian ((int) lengthInSamples);
        output->writeShortBigEndian ((short) bitsPerSample);

        uint8 sampleRateBytes[10] = { 0 };

        if (sampleRate <= 1)
        {
            sampleRateBytes[0] = 0x3f;
            sampleRateBytes[1] = 0xff;
            sampleRateBytes[2] = 0x80;
        }
        else
        {
            int mask = 0x40000000;
            sampleRateBytes[0] = 0x40;

            if (sampleRate >= mask)
            {
                jassertfalse;
                sampleRateBytes[1] = 0x1d;
            }
            else
            {
                int n = (int) sampleRate;

                int i;
                for (i = 0; i <= 32 ; ++i)
                {
                    if ((n & mask) != 0)
                        break;

                    mask >>= 1;
                }

                n = n << (i + 1);

                sampleRateBytes[1] = (uint8) (29 - i);
                sampleRateBytes[2] = (uint8) ((n >> 24) & 0xff);
                sampleRateBytes[3] = (uint8) ((n >> 16) & 0xff);
                sampleRateBytes[4] = (uint8) ((n >>  8) & 0xff);
                sampleRateBytes[5] = (uint8) (n & 0xff);
            }
        }

        output->write (sampleRateBytes, 10);

        if (markChunk.getSize() > 0)
        {
            output->writeInt (chunkName ("MARK"));
            output->writeIntBigEndian ((int) markChunk.getSize());
            *output << markChunk;
        }

        if (comtChunk.getSize() > 0)
        {
            output->writeInt (chunkName ("COMT"));
            output->writeIntBigEndian ((int) comtChunk.getSize());
            *output << comtChunk;
        }

        if (instChunk.getSize() > 0)
        {
            output->writeInt (chunkName ("INST"));
            output->writeIntBigEndian ((int) instChunk.getSize());
            *output << instChunk;
        }

        output->writeInt (chunkName ("SSND"));
        output->writeIntBigEndian (audioBytes + 8);
        output->writeInt (0);
        output->writeInt (0);

        jassert (output->getPosition() == headerLen);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AiffAudioFormatWriter)
};

//==============================================================================
class MemoryMappedAiffReader   : public MemoryMappedAudioFormatReader
{
public:
    MemoryMappedAiffReader (const File& file, const AiffAudioFormatReader& reader)
        : MemoryMappedAudioFormatReader (file, reader, reader.dataChunkStart,
                                         reader.bytesPerFrame * reader.lengthInSamples, reader.bytesPerFrame),
          littleEndian (reader.littleEndian)
    {
    }

    bool readSamples (int** destSamples, int numDestChannels, int startOffsetInDestBuffer,
                      int64 startSampleInFile, int numSamples)
    {
        clearSamplesBeyondAvailableLength (destSamples, numDestChannels, startOffsetInDestBuffer,
                                           startSampleInFile, numSamples, lengthInSamples);

        if (map == nullptr || ! mappedSection.contains (Range<int64> (startSampleInFile, startSampleInFile + numSamples)))
        {
            jassertfalse; // you must make sure that the window contains all the samples you're going to attempt to read.
            return false;
        }

        if (littleEndian)
            AiffAudioFormatReader::copySampleData<AudioData::LittleEndian>
                    (bitsPerSample, destSamples, startOffsetInDestBuffer,
                     numDestChannels, sampleToPointer (startSampleInFile), (int) numChannels, numSamples);
        else
            AiffAudioFormatReader::copySampleData<AudioData::BigEndian>
                    (bitsPerSample, destSamples, startOffsetInDestBuffer,
                     numDestChannels, sampleToPointer (startSampleInFile), (int) numChannels, numSamples);

        return true;
    }

    void readMaxLevels (int64 startSampleInFile, int64 numSamples,
                        float& min0, float& max0, float& min1, float& max1)
    {
        if (numSamples <= 0)
        {
            min0 = max0 = min1 = max1 = 0;
            return;
        }

        if (map == nullptr || ! mappedSection.contains (Range<int64> (startSampleInFile, startSampleInFile + numSamples)))
        {
            jassertfalse; // you must make sure that the window contains all the samples you're going to attempt to read.

            min0 = max0 = min1 = max1 = 0;
            return;
        }

        switch (bitsPerSample)
        {
            case 8:     scanMinAndMax<AudioData::UInt8> (startSampleInFile, numSamples, min0, max0, min1, max1); break;
            case 16:    scanMinAndMax<AudioData::Int16> (startSampleInFile, numSamples, min0, max0, min1, max1); break;
            case 24:    scanMinAndMax<AudioData::Int24> (startSampleInFile, numSamples, min0, max0, min1, max1); break;
            case 32:    scanMinAndMax<AudioData::Int32> (startSampleInFile, numSamples, min0, max0, min1, max1); break;
            default:    jassertfalse; break;
        }
    }

private:
    const bool littleEndian;

    template <typename SampleType>
    void scanMinAndMax (int64 startSampleInFile, int64 numSamples,
                        float& min0, float& max0, float& min1, float& max1) const noexcept
    {
        if (littleEndian)
            scanMinAndMax2<SampleType, AudioData::LittleEndian> (startSampleInFile, numSamples, min0, max0, min1, max1);
        else
            scanMinAndMax2<SampleType, AudioData::BigEndian> (startSampleInFile, numSamples, min0, max0, min1, max1);
    }

    template <typename SampleType, typename Endianness>
    void scanMinAndMax2 (int64 startSampleInFile, int64 numSamples,
                         float& min0, float& max0, float& min1, float& max1) const noexcept
    {
        typedef AudioData::Pointer <SampleType, Endianness, AudioData::Interleaved, AudioData::Const> SourceType;

        SourceType (sampleToPointer (startSampleInFile), (int) numChannels)
            .findMinAndMax ((size_t) numSamples, min0, max0);

        if (numChannels > 1)
            SourceType (addBytesToPointer (sampleToPointer (startSampleInFile), bitsPerSample / 8), (int) numChannels)
                  .findMinAndMax ((size_t) numSamples, min1, max1);
        else
            min1 = max1 = 0;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemoryMappedAiffReader)
};

//==============================================================================
AiffAudioFormat::AiffAudioFormat()
    : AudioFormat (TRANS (aiffFormatName), StringArray (aiffExtensions))
{
}

AiffAudioFormat::~AiffAudioFormat()
{
}

Array<int> AiffAudioFormat::getPossibleSampleRates()
{
    const int rates[] = { 22050, 32000, 44100, 48000, 88200, 96000, 176400, 192000, 0 };
    return Array <int> (rates);
}

Array<int> AiffAudioFormat::getPossibleBitDepths()
{
    const int depths[] = { 8, 16, 24, 0 };
    return Array <int> (depths);
}

bool AiffAudioFormat::canDoStereo() { return true; }
bool AiffAudioFormat::canDoMono()   { return true; }

#if JUCE_MAC
bool AiffAudioFormat::canHandleFile (const File& f)
{
    if (AudioFormat::canHandleFile (f))
        return true;

    const OSType type = f.getMacOSType();
    return type == 'AIFF' || type == 'AIFC'
        || type == 'aiff' || type == 'aifc';
}
#endif

AudioFormatReader* AiffAudioFormat::createReaderFor (InputStream* sourceStream, const bool deleteStreamIfOpeningFails)
{
    ScopedPointer <AiffAudioFormatReader> w (new AiffAudioFormatReader (sourceStream));

    if (w->sampleRate > 0 && w->numChannels > 0)
        return w.release();

    if (! deleteStreamIfOpeningFails)
        w->input = nullptr;

    return nullptr;
}

MemoryMappedAudioFormatReader* AiffAudioFormat::createMemoryMappedReader (const File& file)
{
    if (FileInputStream* fin = file.createInputStream())
    {
        AiffAudioFormatReader reader (fin);

        if (reader.lengthInSamples > 0)
            return new MemoryMappedAiffReader (file, reader);
    }

    return nullptr;
}

AudioFormatWriter* AiffAudioFormat::createWriterFor (OutputStream* out,
                                                     double sampleRate,
                                                     unsigned int numberOfChannels,
                                                     int bitsPerSample,
                                                     const StringPairArray& metadataValues,
                                                     int /*qualityOptionIndex*/)
{
    if (getPossibleBitDepths().contains (bitsPerSample))
        return new AiffAudioFormatWriter (out, sampleRate, numberOfChannels, (unsigned int) bitsPerSample, metadataValues);

    return nullptr;
}
