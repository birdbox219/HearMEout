#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()

{
	formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);

	
}

PlayerAudio::~PlayerAudio()
{
    transportSource.removeChangeListener(this);
    transportSource.setSource(nullptr);
}

void PlayerAudio::setGain(float newGain)
{
    transportSource.setGain(newGain);
}

void PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
    }
}








void PlayerAudio::Start()
{
	transportSource.start();
}

void PlayerAudio::Stop()
{
	transportSource.stop();
}
void PlayerAudio::goStart() {
    transportSource.setPosition(0.0);
}
void PlayerAudio::goEnd() {
  transportSource.setPosition(transportSource.getLengthInSeconds());
  
 }


void PlayerAudio::setLooping(bool shouldLoop)
{
    isLoopingEnabled = shouldLoop;

    if (readerSource)
    {
        readerSource->setLooping(shouldLoop);
    }
}

void PlayerAudio::toggleMute()
{
    if (isMuted)
    {
        // Unmute: restore previous volume
        transportSource.setGain(lastGain);
        isMuted = false;
    }
    else
    {
        // Mute: save current volume and set to 0
        lastGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
}


//----------------------------------------------------------------//

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
	transportSource.releaseResources();
}

void PlayerAudio::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.hasStreamFinished() && isLoopingEnabled)
        {
            transportSource.setPosition(0.0);
            transportSource.start();
        }
    }
}


