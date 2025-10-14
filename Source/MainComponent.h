#pragma once

#include <JuceHeader.h>
#include <vector>
#include "PlayerAudio.h"
#include "PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    // Audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // GUI
    void paint(juce::Graphics& g) override;
    void resized() override;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // Audio
	PlayerAudio player;
	
    PlayerGUI playerGUI;

 //   // GUI Controls
 //   juce::TextButton loadButton{ "Load Files" };
 //   //juce::TextButton restartButton{ "Restart" };
	//juce::TextButton playButton{ "Play" };
 //   juce::TextButton stopButton{ "Stop" };
 //   juce::Slider volumeSlider;

    //void loadTrack(const juce::File& file);
    std::unique_ptr<juce::FileChooser> fileChooser;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};