#include "MainComponent.h"
/*
Keep working on this project structure dont change witout permision !
BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

*/
MainComponent::MainComponent()
{
   
    addAndMakeVisible(playerGUI);

    playerGUI.loadButton.addListener(this);
    //playerGUI.stopButton.addListener(this);
    //playerGUI.playButton.addListener(this);
    
    playerGUI.loopButton.addListener(this);
    playerGUI.muteButton.addListener(this);


    playerGUI.startIcon.addListener(this);
    playerGUI.stopButtonIcon.addListener(this);

    playerGUI.volumeSlider.addListener(this);
    playerGUI.goStartButton.addListener(this);
    playerGUI.goEndButton.addListener(this);


    //playerGUI.stopButton.setVisible(false);
    //playerGUI.playButton.setVisible(true);
    playerGUI.loopButton.setVisible(true);

    playerGUI.startIcon.setVisible(true);
    playerGUI.stopButtonIcon.setVisible(false);

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
                juce::String fileName = file.getFileNameWithoutExtension();
            
                playerGUI.metaData(fileName);
              
            });

       

    }


    


    else if (button == &playerGUI.startIcon)
    {
        player.Start();
		HideButtons(playerGUI.startIcon);
		ShowButtons(playerGUI.stopButtonIcon);
    }
    else if (button == &playerGUI.stopButtonIcon)
    {
        player.Stop();
		HideButtons(playerGUI.stopButtonIcon);
		ShowButtons(playerGUI.startIcon);
    }
    else if (button == &playerGUI.goStartButton) {
        player.goStart();
    }
    else if (button == &playerGUI.goEndButton) {
        player.goEnd();
    }

    else if (button == &playerGUI.loopButton)
    {
        bool currentlyLooping = player.isLooping();
        player.setLooping(!currentlyLooping);

        playerGUI.loopButton.setColour(
            juce::TextButton::buttonColourId,
            player.isLooping() ? juce::Colours::orangered : juce::Colours::darkgrey
        );
            
        
    }
    else if (button == &playerGUI.muteButton)
{
    player.toggleMute();  // tell PlayerAudio to toggle mute state

    // Change the button text to show current state
    if (player.isMuted)
        playerGUI.muteButton.setButtonText("Unmute");
    else
        playerGUI.muteButton.setButtonText("Mute");
}




    //the rest


}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &playerGUI.volumeSlider)
        player.setGain((float)slider->getValue());
}

void MainComponent::ShowButtons(juce::Button& button)
{
	button.setVisible(true);
}
void MainComponent::HideButtons(juce::Button& button)
{
    button.setVisible(false);
}