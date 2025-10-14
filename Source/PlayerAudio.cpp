#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()

{
	formatManager.registerBasicFormats();

	
}

PlayerAudio::~PlayerAudio()
{
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

void PlayerAudio::toggleMute()
{
    if (isMuted)
    {
        transportSource.setGain(lastGain);
        isMuted = false;
    }
    else
    {
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
