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

MidiMessageCollector::MidiMessageCollector()
    : lastCallbackTime (0),
      sampleRate (44100.0001)
{
}

MidiMessageCollector::~MidiMessageCollector()
{
}

//==============================================================================
void MidiMessageCollector::reset (const double sampleRate_)
{
    jassert (sampleRate_ > 0);

    const ScopedLock sl (midiCallbackLock);
    sampleRate = sampleRate_;
    incomingMessages.clear();
    lastCallbackTime = Time::getMillisecondCounterHiRes();
}

void MidiMessageCollector::addMessageToQueue (const MidiMessage& message)
{
    // you need to call reset() to set the correct sample rate before using this object
    jassert (sampleRate != 44100.0001);

    // the messages that come in here need to be time-stamped correctly - see MidiInput
    // for details of what the number should be.
    jassert (message.getTimeStamp() != 0);

    const ScopedLock sl (midiCallbackLock);

    const int sampleNumber
        = (int) ((message.getTimeStamp() - 0.001 * lastCallbackTime) * sampleRate);

    incomingMessages.addEvent (message, sampleNumber);

    // if the messages don't get used for over a second, we'd better
    // get rid of any old ones to avoid the queue getting too big
    if (sampleNumber > sampleRate)
        incomingMessages.clear (0, sampleNumber - (int) sampleRate);
}

void MidiMessageCollector::removeNextBlockOfMessages (MidiBuffer& destBuffer,
                                                      const int numSamples)
{
    // you need to call reset() to set the correct sample rate before using this object
    jassert (sampleRate != 44100.0001);
    jassert (numSamples > 0);

    const double timeNow = Time::getMillisecondCounterHiRes();
    const double msElapsed = timeNow - lastCallbackTime;

    const ScopedLock sl (midiCallbackLock);
    lastCallbackTime = timeNow;

    if (! incomingMessages.isEmpty())
    {
        int numSourceSamples = jmax (1, roundToInt (msElapsed * 0.001 * sampleRate));

        int startSample = 0;
        int scale = 1 << 16;

        const uint8* midiData;
        int numBytes, samplePosition;

        MidiBuffer::Iterator iter (incomingMessages);

        if (numSourceSamples > numSamples)
        {
            // if our list of events is longer than the buffer we're being
            // asked for, scale them down to squeeze them all in..
            const int maxBlockLengthToUse = numSamples << 5;

            if (numSourceSamples > maxBlockLengthToUse)
            {
                startSample = numSourceSamples - maxBlockLengthToUse;
                numSourceSamples = maxBlockLengthToUse;
                iter.setNextSamplePosition (startSample);
            }

            scale = (numSamples << 10) / numSourceSamples;

            while (iter.getNextEvent (midiData, numBytes, samplePosition))
            {
                samplePosition = ((samplePosition - startSample) * scale) >> 10;

                destBuffer.addEvent (midiData, numBytes,
                                     jlimit (0, numSamples - 1, samplePosition));
            }
        }
        else
        {
            // if our event list is shorter than the number we need, put them
            // towards the end of the buffer
            startSample = numSamples - numSourceSamples;

            while (iter.getNextEvent (midiData, numBytes, samplePosition))
            {
                destBuffer.addEvent (midiData, numBytes,
                                     jlimit (0, numSamples - 1, samplePosition + startSample));
            }
        }

        incomingMessages.clear();
    }
}

//==============================================================================
void MidiMessageCollector::handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{
    MidiMessage m (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
    m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);

    addMessageToQueue (m);
}

void MidiMessageCollector::handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber)
{
    MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber));
    m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);

    addMessageToQueue (m);
}

void MidiMessageCollector::handleIncomingMidiMessage (MidiInput*, const MidiMessage& message)
{
    addMessageToQueue (message);
}
