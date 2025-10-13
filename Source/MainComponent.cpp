#include "MainComponent.h"
/*
Keep working on this project structure dont change witout permision !
BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

*/
MainComponent::MainComponent()
{
   
    addAndMakeVisible(playerGUI);

    playerGUI.loadButton.addListener(this);
    playerGUI.stopButton.addListener(this);
    playerGUI.playButton.addListener(this);
    playerGUI.volumeSlider.addListener(this);

    // Add buttons
   /* for (auto* btn : { &loadButton, &playButton , &stopButton  })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }*/

    // Volume slider
    /*volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);*/

    setSize(500, 250);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}
//----------------------------------------------------------------
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    player.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player.releaseResources();
}
//----------------------------------------------------------------


void MainComponent::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::darkgrey);
    //playerGUI.paint(g);
    g.fillAll(juce::Colours::blueviolet);
}


void MainComponent::resized()
{
    //int y = 20;
    //loadButton.setBounds(20, y, 100, 40);
    //playButton.setBounds(140, y, 80, 40);
    //stopButton.setBounds(240, y, 80, 40);
    ///*prevButton.setBounds(340, y, 80, 40);
    //nextButton.setBounds(440, y, 80, 40);*/

    //volumeSlider.setBounds(20, 100, getWidth() - 40, 30);

    playerGUI.setBounds(getLocalBounds());
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playerGUI.loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                player.loadFile(file);
            });
    }

    else if (button == &playerGUI.playButton)
    {
        player.Start();
    }
    else if (button == &playerGUI.stopButton)
    {
        player.Stop();
    }

}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &playerGUI.volumeSlider)
        player.setGain((float)slider->getValue());
}