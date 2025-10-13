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
    juce::Slider volumeSlider;

   


private:
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)


};