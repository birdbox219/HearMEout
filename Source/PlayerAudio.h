#pragma once 
#include <JuceHeader.h>	

class PlayerAudio : public juce::AudioAppComponent

{
public:
	PlayerAudio();
	~PlayerAudio() override;

	void loadFile(const juce::File& file);
	void Start();
	void Stop();
	void setGain(float gain);

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	void toggleMute();
	bool isMuted = false;
	float lastGain = 0.5f;

private:
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;

	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};