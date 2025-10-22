#pragma once 
#include <JuceHeader.h>	
#include<vector>


class PlayerAudio : public juce::AudioAppComponent,
	private juce::ChangeListener

{
public:
	PlayerAudio();
	~PlayerAudio() override;

	juce::String loadFile(const juce::File& file);
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

	void setABLoop(bool enabled);
	bool isABLoopEnabled() const { return abLoopEnabled; }
	void setABPoints(double startPos, double endPos);
	double getABStart() const { return abStartPosition; }
	double getABEnd() const { return abEndPosition; }
	void clearABPoints();



	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	// Playlist-related components
	std::vector <juce::File> files;
	void addToList(juce::File& file);
	

private:
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	void checkABLoop();
 
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
	juce::ResamplingAudioSource respeeder { &transportSource, false, 2 };//for speed.


	bool isLoopingEnabled = false;

	//A-B checkes

	bool abLoopEnabled = false;
	double abStartPosition = 0.0; 
	double abEndPosition = 0.0;

 
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};