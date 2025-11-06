#pragma once 
#include <JuceHeader.h>	
#include<vector>


class PlayerAudio : public juce::AudioAppComponent,  public juce::ChangeListener
{
public:
	PlayerAudio();
	~PlayerAudio() override;
	void setTrackActive(int trackNumber, bool active);

	juce::String loadFile(const juce::File& file);
	juce::String loadFile2(const juce::File& file); //track2

	void Start();
	void Start2(); //track2

	void Stop();
	void Stop2(); //track2

	void setLooping(bool shouldLoop);
	void setLooping2(bool shouldLoop);

	bool isLooping() const { return isLoopingEnabled; }
	bool isLooping2() const { return isLoopingEnabled2; }

	void setGain(float gain);
	void setGain2(float gain);

	void goStart();
	void goStart2();

	void goEnd();
	void goEnd2();

	void toggleMute();
	void toggleMute2();

	void setSpeed(double ratio);
	void setSpeed2(double ratio);
	bool isMuted = false;     // to remember if sound is muted
	bool isMuted2 = false;
	float lastGain = 0.5f;    // to remember the old volume
	float lastGain2 = 0.5f;

	float getPreviousGain() const;
	float getPreviousGain2() const;

	void skipForward(double seconds);
	void skipBackward(double seconds);
	void skipForward2(double seconds);
	void skipBackward2(double seconds);

	double getCurrentPosition() const;
	double getCurrentPosition2() const;
	
	double getTotalLength() const;
	double getTotalLength2() const;

	void setPosition(double newPositon);
	void setPosition2(double newPositon);

	void setABLoop(bool enabled);
	void setABLoop2(bool enabled);

	bool isABLoopEnabled() const { return abLoopEnabled; }
	bool isABLoopEnabled2() const { return abLoopEnabled2; }

	void setABPoints(double startPos, double endPos);
	void setABPoints2(double startPos, double endPos);

	double getABStart() const { return abStartPosition; }
	double getABStart2() const { return abStartPosition2; }

	double getABEnd() const { return abEndPosition; }
	double getABEnd2() const { return abEndPosition2; }
	void clearABPoints();
	void clearABPoints2();


	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	//// Playlist-related components
	std::vector <juce::File> files;
	void addToList(juce::File& file);

	
	juce::File getCurrentFile() const { return currentFile; }
	
	

	juce::AudioTransportSource transportSource2; //for track2
	juce::ResamplingAudioSource respeeder2{ &transportSource2, false, 2 };
	// Made public instead of private so I can access them from MainComponent
// when switching between singleTrack and doubleTrack -alaa

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;
	void checkABLoop();
	void checkABLoop2();
	juce::MixerAudioSource mixer; //To mix the two sounds together
	juce::AudioFormatManager formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource2; //for track2
	juce::AudioTransportSource transportSource;

	juce::ResamplingAudioSource respeeder { &transportSource, false, 2 };//for speed.
	


	bool isLoopingEnabled = false;
	bool isLoopingEnabled2 = false;

	//A-B checkes

	bool abLoopEnabled = false;
	double abStartPosition = 0.0; 
	double abEndPosition = 0.0;
	//-------

	juce::File currentFile;

	bool abLoopEnabled2 = false;
	double abStartPosition2 = 0.0;
	double abEndPosition2 = 0.0;
	//for calling that the song has ended.
	std::function<void()> onTrackFinished;
	

	
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)

};