#pragma once 
#include <JuceHeader.h>	

class PlayerAudio : public juce::AudioAppComponent,
	private juce::ChangeListener

{
public:
	PlayerAudio();
	~PlayerAudio() override;

	void loadFile(const juce::File& file);
	void Start();
	void Stop();
	void setLooping(bool shouldLoop);
	bool isLooping() const { return isLoopingEnabled; }

	void setGain(float gain);

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	void toggleMute();
	bool isMuted = false;
	float lastGain = 0.5f;

private:
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;

	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;

	bool isLoopingEnabled = false;

	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};