#include "PlayerGUI.h"


PlayerGUI::PlayerGUI()
{
    



    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(goStartButton);
    addAndMakeVisible(goEndButton);
    addAndMakeVisible(title);

    addAndMakeVisible(startIcon);
    addAndMakeVisible(stopButtonIcon);
    

    addAndMakeVisible(loopButton);
    

    addAndMakeVisible(muteButton);


    
    
    
    //Icon Manager
    

     
    stopImageIcon = juce::ImageFileFormat::loadFrom(BinaryData::pauseyellow_png, BinaryData::pauseyellow_pngSize);

    goEnd = juce::ImageFileFormat::loadFrom(BinaryData::goEnd_png, BinaryData::goEnd_pngSize);
    goStart = juce::ImageFileFormat::loadFrom(BinaryData::goStart_png, BinaryData::goStart_pngSize);
    


    
   

    
    
    //------------------------------------------//


    




    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::orangered);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);




    //volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //Progress Slider
    progressSlider.setRange(0.0, 1.0, 0.001);
    progressSlider.setValue(0.0);
    progressSlider.setSliderStyle(juce::Slider::LinearHorizontal);  
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);



    addAndMakeVisible(progressSlider);

    //Progress Lebel
    currentTimeLabel.setText("0:00", juce::dontSendNotification);
    //currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(currentTimeLabel);

    TotalTimeLabel.setText("0:00", juce::dontSendNotification);
    addAndMakeVisible(TotalTimeLabel);











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
    
    startIcon.setBounds(450, 500, 60, 60);
    stopButtonIcon.setBounds(450, 500, 60, 60);
    

    goStartButton.setBounds(300,500,100,40);
    goEndButton.setBounds(550, 500, 100, 40);
    title.setBounds(340, 80, 100, 40);

    loopButton.setBounds(800, 500, 80, 40);

    muteButton.setBounds(100, 500, 100, 40);


    

    if (stopImageIcon.isValid())
    {


        stopButtonIcon.setImages(false, true, true,

            stopImageIcon, 1.0f, juce::Colours::transparentBlack,
            stopImageOverIcon, 0.8f, juce::Colours::transparentWhite,
            stopImageDownIcon, 1.0f, juce::Colours::yellow);


    }

    
    

    
    goEndButton.setImages(
        false, // resizeButtonImageAutomatically
        true,  // preserveProportions
        true,  // useAlphaChannel
        goEnd, 1.0f, juce::Colours::transparentWhite, // Normal opacity
        goEnd, 0.8f, juce::Colours::transparentWhite, // Hover opacity
        goEnd, 1.0f, juce::Colours::yellow  //Pressed
     
    );
    goStartButton.setImages(
        false, // resizeButtonImageAutomatically
        true,  // preserveProportions
        true,  // useAlphaChannel
        goStart, 1.0f, juce::Colours::transparentWhite, // Normal opacity
        goStart, 0.8f, juce::Colours::transparentWhite, // Hover opacity
        goStart, 1.0f, juce::Colours::yellow  //Pressed
    );

    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/
    //Sliders Bounds

    volumeSlider.setBounds(800, 100, 30 , getHeight() - 300 );

    int progressY = 420;
    progressSlider.setBounds(90, progressY, getWidth() - 180, 80);







    //Lebels Bounds
    currentTimeLabel.setBounds(20, progressY, 60, 80);
    TotalTimeLabel.setBounds(getWidth() - 80, progressY, 60, 80);
}



void PlayerGUI :: metaData(juce::String& fileName) {
    title.setText("Title: " + fileName, juce::dontSendNotification);
}

