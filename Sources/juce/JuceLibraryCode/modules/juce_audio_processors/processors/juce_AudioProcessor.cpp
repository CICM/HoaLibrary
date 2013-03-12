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

static ThreadLocalValue<AudioProcessor::WrapperType> wrapperTypeBeingCreated;

void JUCE_CALLTYPE AudioProcessor::setTypeOfNextNewPlugin (AudioProcessor::WrapperType type)
{
    wrapperTypeBeingCreated = type;
}

AudioProcessor::AudioProcessor()
    : wrapperType (wrapperTypeBeingCreated.get()),
      playHead (nullptr),
      sampleRate (0),
      blockSize (0),
      numInputChannels (0),
      numOutputChannels (0),
      latencySamples (0),
      suspended (false),
      nonRealtime (false)
{
}

AudioProcessor::~AudioProcessor()
{
    // ooh, nasty - the editor should have been deleted before the filter
    // that it refers to is deleted..
    jassert (activeEditor == nullptr);

   #if JUCE_DEBUG
    // This will fail if you've called beginParameterChangeGesture() for one
    // or more parameters without having made a corresponding call to endParameterChangeGesture...
    jassert (changingParams.countNumberOfSetBits() == 0);
   #endif
}

void AudioProcessor::setPlayHead (AudioPlayHead* const newPlayHead) noexcept
{
    playHead = newPlayHead;
}

void AudioProcessor::addListener (AudioProcessorListener* const newListener)
{
    const ScopedLock sl (listenerLock);
    listeners.addIfNotAlreadyThere (newListener);
}

void AudioProcessor::removeListener (AudioProcessorListener* const listenerToRemove)
{
    const ScopedLock sl (listenerLock);
    listeners.removeFirstMatchingValue (listenerToRemove);
}

void AudioProcessor::setPlayConfigDetails (const int newNumIns,
                                           const int newNumOuts,
                                           const double newSampleRate,
                                           const int newBlockSize) noexcept
{
    sampleRate = newSampleRate;
    blockSize  = newBlockSize;

    if (numInputChannels != newNumIns || numOutputChannels != newNumOuts)
    {
        numInputChannels  = newNumIns;
        numOutputChannels = newNumOuts;

        numChannelsChanged();
    }
}

void AudioProcessor::numChannelsChanged() {}

void AudioProcessor::setSpeakerArrangement (const String& inputs, const String& outputs)
{
    inputSpeakerArrangement  = inputs;
    outputSpeakerArrangement = outputs;
}

void AudioProcessor::setNonRealtime (const bool newNonRealtime) noexcept
{
    nonRealtime = newNonRealtime;
}

void AudioProcessor::setLatencySamples (const int newLatency)
{
    if (latencySamples != newLatency)
    {
        latencySamples = newLatency;
        updateHostDisplay();
    }
}

void AudioProcessor::setParameterNotifyingHost (const int parameterIndex,
                                                const float newValue)
{
    setParameter (parameterIndex, newValue);
    sendParamChangeMessageToListeners (parameterIndex, newValue);
}

AudioProcessorListener* AudioProcessor::getListenerLocked (const int index) const noexcept
{
    const ScopedLock sl (listenerLock);
    return listeners [index];
}

void AudioProcessor::sendParamChangeMessageToListeners (const int parameterIndex, const float newValue)
{
    jassert (isPositiveAndBelow (parameterIndex, getNumParameters()));

    for (int i = listeners.size(); --i >= 0;)
        if (AudioProcessorListener* l = getListenerLocked (i))
            l->audioProcessorParameterChanged (this, parameterIndex, newValue);
}

void AudioProcessor::beginParameterChangeGesture (int parameterIndex)
{
    jassert (isPositiveAndBelow (parameterIndex, getNumParameters()));

   #if JUCE_DEBUG
    // This means you've called beginParameterChangeGesture twice in succession without a matching
    // call to endParameterChangeGesture. That might be fine in most hosts, but better to avoid doing it.
    jassert (! changingParams [parameterIndex]);
    changingParams.setBit (parameterIndex);
   #endif

    for (int i = listeners.size(); --i >= 0;)
        if (AudioProcessorListener* l = getListenerLocked (i))
            l->audioProcessorParameterChangeGestureBegin (this, parameterIndex);
}

void AudioProcessor::endParameterChangeGesture (int parameterIndex)
{
    jassert (isPositiveAndBelow (parameterIndex, getNumParameters()));

   #if JUCE_DEBUG
    // This means you've called endParameterChangeGesture without having previously called
    // endParameterChangeGesture. That might be fine in most hosts, but better to keep the
    // calls matched correctly.
    jassert (changingParams [parameterIndex]);
    changingParams.clearBit (parameterIndex);
   #endif

    for (int i = listeners.size(); --i >= 0;)
        if (AudioProcessorListener* l = getListenerLocked (i))
            l->audioProcessorParameterChangeGestureEnd (this, parameterIndex);
}

void AudioProcessor::updateHostDisplay()
{
    for (int i = listeners.size(); --i >= 0;)
        if (AudioProcessorListener* l = getListenerLocked (i))
            l->audioProcessorChanged (this);
}

String AudioProcessor::getParameterLabel (int) const        { return String::empty; }
bool AudioProcessor::isParameterAutomatable (int) const     { return true; }
bool AudioProcessor::isMetaParameter (int) const            { return false; }

void AudioProcessor::suspendProcessing (const bool shouldBeSuspended)
{
    const ScopedLock sl (callbackLock);
    suspended = shouldBeSuspended;
}

void AudioProcessor::reset() {}
void AudioProcessor::processBlockBypassed (AudioSampleBuffer&, MidiBuffer&) {}

//==============================================================================
void AudioProcessor::editorBeingDeleted (AudioProcessorEditor* const editor) noexcept
{
    const ScopedLock sl (callbackLock);

    if (activeEditor == editor)
        activeEditor = nullptr;
}

AudioProcessorEditor* AudioProcessor::createEditorIfNeeded()
{
    if (activeEditor != nullptr)
        return activeEditor;

    AudioProcessorEditor* const ed = createEditor();

    // You must make your hasEditor() method return a consistent result!
    jassert (hasEditor() == (ed != nullptr));

    if (ed != nullptr)
    {
        // you must give your editor comp a size before returning it..
        jassert (ed->getWidth() > 0 && ed->getHeight() > 0);

        const ScopedLock sl (callbackLock);
        activeEditor = ed;
    }

    return ed;
}

//==============================================================================
void AudioProcessor::getCurrentProgramStateInformation (juce::MemoryBlock& destData)
{
    getStateInformation (destData);
}

void AudioProcessor::setCurrentProgramStateInformation (const void* data, int sizeInBytes)
{
    setStateInformation (data, sizeInBytes);
}

//==============================================================================
// magic number to identify memory blocks that we've stored as XML
const uint32 magicXmlNumber = 0x21324356;

void AudioProcessor::copyXmlToBinary (const XmlElement& xml, juce::MemoryBlock& destData)
{
    const String xmlString (xml.createDocument (String::empty, true, false));
    const size_t stringLength = xmlString.getNumBytesAsUTF8();

    destData.setSize (stringLength + 9);

    uint32* const d = static_cast<uint32*> (destData.getData());
    d[0] = ByteOrder::swapIfBigEndian ((const uint32) magicXmlNumber);
    d[1] = ByteOrder::swapIfBigEndian ((const uint32) stringLength);

    xmlString.copyToUTF8 ((CharPointer_UTF8::CharType*) (d + 2), stringLength + 1);
}

XmlElement* AudioProcessor::getXmlFromBinary (const void* data, const int sizeInBytes)
{
    if (sizeInBytes > 8
         && ByteOrder::littleEndianInt (data) == magicXmlNumber)
    {
        const int stringLength = (int) ByteOrder::littleEndianInt (addBytesToPointer (data, 4));

        if (stringLength > 0)
            return XmlDocument::parse (String::fromUTF8 (static_cast<const char*> (data) + 8,
                                                         jmin ((sizeInBytes - 8), stringLength)));
    }

    return nullptr;
}

//==============================================================================
void AudioProcessorListener::audioProcessorParameterChangeGestureBegin (AudioProcessor*, int) {}
void AudioProcessorListener::audioProcessorParameterChangeGestureEnd (AudioProcessor*, int) {}

//==============================================================================
bool AudioPlayHead::CurrentPositionInfo::operator== (const CurrentPositionInfo& other) const noexcept
{
    return timeInSamples == other.timeInSamples
        && ppqPosition == other.ppqPosition
        && editOriginTime == other.editOriginTime
        && ppqPositionOfLastBarStart == other.ppqPositionOfLastBarStart
        && frameRate == other.frameRate
        && isPlaying == other.isPlaying
        && isRecording == other.isRecording
        && bpm == other.bpm
        && timeSigNumerator == other.timeSigNumerator
        && timeSigDenominator == other.timeSigDenominator
        && ppqLoopStart == other.ppqLoopStart
        && ppqLoopEnd == other.ppqLoopEnd
        && isLooping == other.isLooping;
}

bool AudioPlayHead::CurrentPositionInfo::operator!= (const CurrentPositionInfo& other) const noexcept
{
    return ! operator== (other);
}

void AudioPlayHead::CurrentPositionInfo::resetToDefault()
{
    zerostruct (*this);
    timeSigNumerator = 4;
    timeSigDenominator = 4;
    bpm = 120;
}
