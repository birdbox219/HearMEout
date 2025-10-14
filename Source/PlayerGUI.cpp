#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    //for (auto* btn : { &loadButton, &playButton , &stopButton })
    //{
    //    //btn->addListener(this);
    //    addAndMakeVisible(btn);
    //}



    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(goStartButton);
    addAndMakeVisible(goEndButton);
    addAndMakeVisible(title);
    




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
    playButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);
    goStartButton.setBounds(20,80,100,40);
    goEndButton.setBounds(140, 80, 100, 40);
    title.setBounds(340, 80, 100, 40);
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 200, getWidth() - 40, 30);
}
void PlayerGUI :: metaData(juce::String& fileName) {
    title.setText("Title: " + fileName, juce::dontSendNotification);
}

