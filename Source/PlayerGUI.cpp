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
<<<<<<< HEAD
    addAndMakeVisible(muteButton);
=======
    addAndMakeVisible(loopButton);

    loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
>>>>>>> upstream/master
    




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
<<<<<<< HEAD
    stopButton.setBounds(240, y, 80, 40);
    muteButton.setBounds(350, 20, 80, 40);
=======

    stopButton.setBounds(140, y, 80, 40);

    loopButton.setBounds(240, y, 80, 40);

>>>>>>> upstream/master

    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}
