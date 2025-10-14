#include "PlayerGUI.h"


PlayerGUI::PlayerGUI()
{
    



    addAndMakeVisible(loadButton);
    //addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(goStartButton);
    addAndMakeVisible(goEndButton);
    addAndMakeVisible(title);
    addAndMakeVisible(stopButtonIcon);
    
    addAndMakeVisible(loopButton);
    addAndMakeVisible(startIcon);


    
    

    loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);

    /*stopImageIcon = juce::ImageFileFormat::loadFrom(juce::File("D:/FCAI_SecondLevel/OOP/A_2/HearMEouT/HearMEout/Assetes/paused.png"));*/
    stopImageIcon = juce::ImageCache::getFromMemory(
        BinaryData::paused_png,
        BinaryData::paused_pngSize
    );
    


    stopImageOverIcon = juce::ImageFileFormat::loadFrom(juce::File("Assets/stop_hover.png"));
    stopImageDownIcon = juce::ImageFileFormat::loadFrom(juce::File("Assets/stop_pressed.png"));

    
    
    if (stopImageIcon.isValid())
    {
        

        stopButtonIcon.setImages(true , true ,true, 
            
            stopImageIcon, 1.0f, juce::Colours::transparentBlack,
            stopImageOverIcon, 1.0f, juce::Colours::transparentBlack,
            stopImageDownIcon, 1.0f, juce::Colours::transparentBlack);
            
            
    }
    




    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    //volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //setSize(500, 250);
    //setAudioChannels(0, 2);
}


PlayerGUI::~PlayerGUI() {}


void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::blueviolet);
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    //playButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    goStartButton.setBounds(20,80,100,40);
    goEndButton.setBounds(140, 80, 100, 40);
    title.setBounds(340, 80, 100, 40);

    //playButton.setBounds(140, y, 80, 40);

    stopButton.setBounds(450, 500, 40, 40);

    loopButton.setBounds(240, y, 80, 40);

    startIcon.setBounds(450, 500, 60, 60);
    stopButtonIcon.setBounds(300,500, 60, 60);

    


    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 200, getWidth() - 40, 30);
}
void PlayerGUI :: metaData(juce::String& fileName) {
    title.setText("Title: " + fileName, juce::dontSendNotification);
}

