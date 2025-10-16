﻿#include "PlayerAudio.h"

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

void PlayerAudio::setSpeed(double ratio)
{
    respeeder.setResamplingRatio(ratio);
}

// skip 10sec and rewind 10 sec:
void PlayerAudio::skipForward(double seconds)
{
    double newPos = transportSource.getCurrentPosition() + seconds;
    if (newPos < transportSource.getLengthInSeconds())
        transportSource.setPosition(newPos);
}
  
void PlayerAudio::skipBackward(double seconds)
{
    double newPos = transportSource.getCurrentPosition() - seconds;
    if (newPos < 0) newPos = 0;
    transportSource.setPosition(newPos);
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

//Get postion and total lenght of Audio 

float PlayerAudio::getPreviousGain() const
{
    return lastGain;
}

double PlayerAudio::getCurrentPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getTotalLength() const
{
    return transportSource.getLengthInSeconds();
}

void PlayerAudio::setPosition(double newPositon)
{
    transportSource.setPosition(newPositon);
}


//----------------------------------------------------------------//
// i need to edit this later to fix speed bug ~amr.
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    respeeder.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	respeeder.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::releaseResources()
{
    respeeder.releaseResources();
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


