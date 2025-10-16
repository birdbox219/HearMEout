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
	void goStart();
	void goEnd();
	void toggleMute();

	void setSpeed(double ratio);
	bool isMuted = false;     // to remember if sound is muted
	float lastGain = 0.5f;    // to remember the old volume

	float getPreviousGain() const;

	void skipForward(double seconds);
	void skipBackward(double seconds);

	double getCurrentPosition() const;
	
	double getTotalLength() const;


	void setPosition(double newPositon);

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

private:
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
 
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
	juce::ResamplingAudioSource respeeder { &transportSource, false, 2 };//for speed.


	bool isLoopingEnabled = false;
 
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};