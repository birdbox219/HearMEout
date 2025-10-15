#pragma once
# include "JuceHeader.h"

class PlayerGUI : public juce::Component

{
public:
	PlayerGUI();
	~PlayerGUI() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void metaData(juce::String& fileName,double&totalTime);

    //void buttonClicked(juce::Button* button) override;
    //void sliderValueChanged(juce::Slider* slider) override;
    
    //juce::TextButton restartButton{ "Restart" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::ImageButton goStartButton;
    juce::ImageButton goEndButton;
    


    // Text Buttons
    juce::TextButton loadButton{ "Load Files" };
    //juce::TextButton goStartButton{ "Go to start" };
    //juce::TextButton goEndButton{ "Go to end" };
    juce::TextButton loopButton{ "Loop" };

    juce::ArrowButton startIcon{ "Play" , 0.0f , juce::Colours::yellow };
    //juce::TextButton stopButton{ "Stop" };


    juce::TextButton muteButton{"Mute"};
    

    //Icon Buttons
    juce::Image stopImageIcon;
    juce::Image stopImageOverIcon;
    juce::Image stopImageDownIcon;
    juce::Image goEnd;
    juce::Image goStart;
    juce::ImageButton stopButtonIcon;
  




    //Sliders
    juce::Slider volumeSlider;
    juce::Slider progressSlider;






    // Lebels
    juce::Label title;
    juce::Label time;

    juce::Label currentTimeLabel;
    juce::Label TotalTimeLabel;


    

    
    




private:
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)


};


