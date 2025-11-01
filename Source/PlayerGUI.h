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


    //A-B intinales  -Mahdmoud
    juce::TextButton abLoopButton{ "Set A-B Loop" };
    juce::TextButton abStartButton{ "Start A-B" };



    juce::ImageButton goStartButton;
    juce::ImageButton goEndButton;
   
    //skip buttons:
    juce::ImageButton skipBackButton;
    juce::ImageButton skipForwardButton;

 
    // Text Buttons
    juce::TextButton loadButton{ "Load Files" };
    //juce::TextButton goStartButton{ "Go to start" };
    //juce::TextButton goEndButton{ "Go to end" };
    juce::TextButton loopButton{ "Loop" };

    juce::ArrowButton startIcon{ "Play" , 0.0f , juce::Colours::yellow.withAlpha(0.6f)};
    //juce::TextButton stopButton{ "Stop" };


    juce::ImageButton muteButton;
    

    //Icon Buttons
    juce::Image stopImageIcon;
    juce::Image stopImageOverIcon;
    juce::Image stopImageDownIcon;
    juce::Image goEnd;
    juce::Image goStart;
    juce::Image remove;
    juce::Image forward_10;
    juce::Image backward_10;
    juce::Image muteimage;
    juce::Image unmuteimage;
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




	//Theme Bground Image
	juce::Image backgroundImage;
    juce::TextButton changeThemeButton{ "Theme" };
    int currentThemeIndex = 0;



    // Playlist-related components
    juce::TextButton addToListButton{"+"}; 
    juce::TextButton resetButton{ "Clear" };
    juce::TextButton selectButton{ "Select" };
    juce::ImageButton removeButton;

    juce::ListBox playList;
    struct fileInfo {
        juce::File file;
        int time;

    };
    std::vector<fileInfo> files;
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void showFile(juce::File& file,double time);
    void selectedRowsChanged(int lastRowSelected);
	void ChangeTheme(int themeIndex = -1);
  

    juce::File sendFile;
    int sendRow;

    juce::Label abStartLabel;
    juce::Label abEndLabel;
    juce::Label abStartTimeLabel;
    juce::Label abEndTimeLabel;








    bool abLoopActive = false;
    bool abControlsVisible = false;





    

    
    




private:

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)


};


