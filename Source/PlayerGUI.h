#pragma once
# include "JuceHeader.h"
#include <vector>

class PlayerGUI : public juce::Component, public juce::ListBoxModel
{
public:
	PlayerGUI();
	~PlayerGUI() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void metaData(juce::String& fileName,double&totalTime , juce::String& authorName);

    //void buttonClicked(juce::Button* button) override;
    //void sliderValueChanged(juce::Slider* slider) override;
    
    //juce::TextButton restartButton{ "Restart" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::ImageButton goStartButton;
    juce::ImageButton goEndButton;
    
    //skip buttons:
    juce::TextButton skipBackButton { "⏪ 10s" };
    juce::TextButton skipForwardButton { "10s ⏩" };

 
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
    juce::Slider speedSlider;
    juce::Label title;
    juce::Label time;
    juce::Label author;

    juce::Label currentTimeLabel;
    juce::Label TotalTimeLabel;


    // Playlist-related components
    juce::TextButton addToListButton{"+"}; 
    juce::TextButton resetButton{ "Clear" };
    juce::TextButton selectButton{ "Select" };
    juce::ListBox playList;
    std::vector<juce::File> files;
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void showFile(juce::File& file);
    void selectedRowsChanged(int lastRowSelected);
  
\
    juce::File sendFile;


    
    




private:
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)


};


