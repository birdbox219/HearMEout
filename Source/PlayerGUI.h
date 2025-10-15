#pragma once
# include "JuceHeader.h"

class PlayerGUI : public juce::Component

{
public:
	PlayerGUI();
	~PlayerGUI() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    //void buttonClicked(juce::Button* button) override;
    //void sliderValueChanged(juce::Slider* slider) override;
    juce::TextButton loadButton{ "Load Files" };
    //juce::TextButton restartButton{ "Restart" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::ImageButton goStartButton;
    juce::ImageButton goEndButton;
    juce::TextButton loopButton{ "Loop" };
    juce::ArrowButton startIcon{ "Play" , 0.0f , juce::Colours::yellow };
    juce::TextButton muteButton{"Mute"};

    juce::Image stopImageIcon;
    juce::Image stopImageOverIcon;
    juce::Image stopImageDownIcon;
    juce::Image goEnd;
    juce::Image goStart;
    juce::ImageButton stopButtonIcon;
  


    juce::Slider volumeSlider;
    juce::Label title;

    void metaData(juce::String& fileName);

    
    




private:
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)


};


