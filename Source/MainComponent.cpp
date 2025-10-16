#include "MainComponent.h"
/*
Keep working on this project structure dont change without permision !
BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
 
*/
MainComponent::MainComponent()
{
   
    addAndMakeVisible(playerGUI);

    playerGUI.loadButton.addListener(this);
    
    
    playerGUI.loopButton.addListener(this);


    playerGUI.muteButton.addListener(this);


    playerGUI.startIcon.addListener(this);
    playerGUI.stopButtonIcon.addListener(this);

    
    playerGUI.goStartButton.addListener(this);
    playerGUI.goEndButton.addListener(this);
    playerGUI.speedSlider.addListener(this);


    playerGUI.volumeSlider.addListener(this);
    playerGUI.progressSlider.addListener(this);
    playerGUI.progressSlider.addMouseListener(this, false);
    //NOTE: I FIGURED WE CAN DO THIS MUCH COOLER THAN IF ELSE DOWN ~amr.
    playerGUI.skipBackButton.onClick = [this] { player.skipBackward(10.0); };
    playerGUI.skipForwardButton.onClick = [this] { player.skipForward(10.0); }; 


    
    playerGUI.loopButton.setVisible(true);

    playerGUI.startIcon.setVisible(true);
    playerGUI.stopButtonIcon.setVisible(false);
    playerGUI.skipBackButton.setVisible(true);
    playerGUI.skipForwardButton.setVisible(true);
    

    // Add buttons
   /* for (auto* btn : { &loadButton, &playButton , &stopButton  })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }*/

    

    setSize(500, 250);
    setAudioChannels(0, 2);

    startTimer(100);
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
    
    g.fillAll(juce::Colours::blueviolet);
}


void MainComponent::resized()
{
 

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

                double totalTime = player.getTotalLength();
                playerGUI.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
              
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
        playerGUI.progressSlider.setValue(0.0);
    }
    else if (button == &playerGUI.goEndButton) {
        player.goEnd();
        playerGUI.progressSlider.setValue(0.0);
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
        player.toggleMute();// tell PlayerAudio to toggle mute state
        playerGUI.volumeSlider.setValue(0.0); // update UI - mahmoud 

    // Change the button text to show current state
        if (player.isMuted)
        {
            playerGUI.muteButton.setButtonText("Unmute");
        }
        
        else
        {
            playerGUI.muteButton.setButtonText("Mute");
            playerGUI.volumeSlider.setValue(player.getPreviousGain()); // update UI - mahmoud 

        }
        
    }




    //the rest


}



void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &playerGUI.volumeSlider)
    {
        player.setGain((float)slider->getValue());
    }
        
    if (slider == &playerGUI.speedSlider)
    {
        player.setSpeed(slider->getValue());
    }
    
    if (slider == &playerGUI.progressSlider && isDraggingSlider)
    {
        double totalLength = player.getTotalLength();
        double newPosition = slider->getValue() * totalLength;
        player.setPosition(newPosition);
    }
}




void MainComponent::timerCallback()
{
    if (!isDraggingSlider)
    {
        double currentLenght = player.getCurrentPosition();
        double TotalLenght = player.getTotalLength();

        if (TotalLenght > 0.0)
        {
            playerGUI.progressSlider.setValue(currentLenght / TotalLenght, juce::dontSendNotification);
            playerGUI.currentTimeLabel.setText(formatTime(currentLenght), juce::dontSendNotification);
            
        }


    }
}


juce::String MainComponent::formatTime(double seconds)
{
    int mins = (int)seconds / 60;
    int secs = (int)seconds % 60;
    return juce::String(mins) + ":" + juce::String(secs).paddedLeft('0', 2);
}



void MainComponent::ShowButtons(juce::Button& button)
{
	button.setVisible(true);
}
void MainComponent::HideButtons(juce::Button& button)
{
    button.setVisible(false);
}


void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    if (event.eventComponent == &playerGUI.progressSlider)
    {
        isDraggingSlider = true;
    }
}

void MainComponent::mouseUp(const juce::MouseEvent& event)
{
    if (event.eventComponent == &playerGUI.progressSlider)
    {
        isDraggingSlider = false;
    }
}
