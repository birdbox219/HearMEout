#include "MainComponent.h"
/*
Keep working on this project structure dont change without permision !
BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
 
*/
MainComponent::MainComponent()
{
  
    
 

    isStartWindow = true;
    startTimer(7000);
    addAndMakeVisible(playerGUI);
    playerGUI.setVisible(false);
    addAndMakeVisible(startButton);
    startButton.addListener(this);

    startButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkorange);
  
    playerGUI.loadButton.addListener(this);
    
    
        playerGUI.selectButton.addListener(this);
    playerGUI.loopButton.addListener(this);


    playerGUI.muteButton.addListener(this);


    playerGUI.startIcon.addListener(this);
    playerGUI.stopButtonIcon.addListener(this);

    
    playerGUI.goStartButton.addListener(this);
    playerGUI.goEndButton.addListener(this);
    playerGUI.addToListButton.addListener(this);
    playerGUI.resetButton.addListener(this);
    playerGUI.removeButton.addListener(this);
    playerGUI.speedSlider.addListener(this);


    playerGUI.volumeSlider.addListener(this);
    playerGUI.progressSlider.addListener(this);
    playerGUI.progressSlider.addMouseListener(this, false);
    //NOTE: I FIGURED WE CAN DO THIS MUCH COOLER THAN IF ELSE DOWN ~amr.
    playerGUI.skipBackButton.onClick = [this] { player.skipBackward(10.0); };
    playerGUI.skipForwardButton.onClick = [this] { player.skipForward(10.0); }; 


    
    playerGUI.loopButton.setVisible(true);

    playerGUI.abLoopButton.addListener(this);
    playerGUI.abStartButton.addListener(this);

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
    if (isStartWindow) {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(40.0f, juce::Font::bold));
        juce::Image startWindow = juce::ImageFileFormat::loadFrom(BinaryData::startWindow_png, BinaryData::startWindow_pngSize);
        g.drawImageWithin(startWindow,
            0, 0, getWidth(), getHeight(),
            juce::RectanglePlacement::stretchToFit);
      
        
    }
    else{g.fillAll(juce::Colours::blueviolet);}
    
}



void MainComponent::resized()
{
    if (isStartWindow){
    startButton.setBounds(getWidth() / 2 - 50, getHeight() - 60, 100, 40);
}

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
                //player.loadFile(file);
                authorName = player.loadFile(file);
                double totalTime = player.getTotalLength();
                playerGUI.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                juce::String fileName = file.getFileNameWithoutExtension();
                playerGUI.metaData(fileName,totalTime , authorName);


                //reset A-B
                playerGUI.abLoopActive = false;
                playerGUI.abControlsVisible = false;
                playerGUI.abStartTimeLabel.setVisible(false);
                playerGUI.abEndTimeLabel.setVisible(false);
                playerGUI.abStartLabel.setVisible(false);
                playerGUI.abEndLabel.setVisible(false);
                playerGUI.abStartButton.setVisible(false);
                playerGUI.abLoopButton.setButtonText("Set A-B Loop");
                playerGUI.abLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);


                HideButtons(playerGUI.stopButtonIcon);
                ShowButtons(playerGUI.startIcon);
                 
               
       
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
            player.isLooping() ? juce::Colours::orangered : juce::Colours::darkgrey.withAlpha(0.2f)
        );

        if (player.isLooping() && playerGUI.abLoopActive)
        {
            playerGUI.abLoopActive = false;
            player.setABLoop(false);
            playerGUI.abStartButton.setButtonText("Start A-B");
            playerGUI.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey.withAlpha(0.2f));
        }
            
        
    }

    else if (button == &playerGUI.abLoopButton)
    {
        
        playerGUI.abControlsVisible = !playerGUI.abControlsVisible;

        playerGUI.abStartTimeLabel.setVisible(playerGUI.abControlsVisible);
        playerGUI.abEndTimeLabel.setVisible(playerGUI.abControlsVisible);
        playerGUI.abStartLabel.setVisible(playerGUI.abControlsVisible);
        playerGUI.abEndLabel.setVisible(playerGUI.abControlsVisible);
        playerGUI.abStartButton.setVisible(playerGUI.abControlsVisible);

        if (playerGUI.abControlsVisible)
        {
            
            double totalTime = player.getTotalLength();
            playerGUI.abStartLabel.setText("0:00", juce::dontSendNotification);
            playerGUI.abEndLabel.setText(formatTime(totalTime), juce::dontSendNotification);
            playerGUI.abLoopButton.setButtonText("Hide A-B");
        }
        else
        {
            playerGUI.abLoopButton.setButtonText("Set A-B Loop");

            
            if (playerGUI.abLoopActive)
            {
                playerGUI.abLoopActive = false;
                player.setABLoop(false);
                playerGUI.abStartButton.setButtonText("Start A-B");
                playerGUI.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
            }
        }
    }


    else if (button == &playerGUI.abStartButton)
    {
        // Parse time strings and start A-B loop
        juce::String startTimeStr = playerGUI.abStartLabel.getText();
        juce::String endTimeStr = playerGUI.abEndLabel.getText();

        double startTime = parseTimeString(startTimeStr);
        double endTime = parseTimeString(endTimeStr);
        double totalTime = player.getTotalLength();

        
        if (startTime < 0) startTime = 0;
        if (endTime > totalTime) endTime = totalTime;
        if (startTime >= endTime)
        {
            // Show error 
            playerGUI.abStartButton.setButtonText("Invalid Times!");
            juce::Timer::callAfterDelay(2000, [this]() {
                playerGUI.abStartButton.setButtonText(playerGUI.abLoopActive ? "Stop A-B" : "Start A-B");
                });
            return;
        }

        
        playerGUI.abLoopActive = !playerGUI.abLoopActive;

        if (playerGUI.abLoopActive)
        {
            
            player.setABPoints(startTime, endTime);
            player.setABLoop(true);

            
            if (player.isLooping())
            {
                player.setLooping(false);
                playerGUI.loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
            }

            playerGUI.abStartButton.setButtonText("Stop A-B");
            playerGUI.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cyan);

            
            player.setPosition(startTime);
        }
        else
        {
            // Disable A-B loop
            player.setABLoop(false);
            playerGUI.abStartButton.setButtonText("Start A-B");
            playerGUI.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
        }
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
    
    // Playlist-related components
    else if (button == &playerGUI.addToListButton) {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
               
                authorName = player.loadFile(file);
                double totalTime = player.getTotalLength();
                playerGUI.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                juce::String fileName = file.getFileNameWithoutExtension();
                playerGUI.metaData(fileName, totalTime, authorName);
                player.addToList(file);
                playerGUI.showFile(file,totalTime);


            });
    }
    else if (button == &playerGUI.resetButton) {
        player.files.clear();
        playerGUI.files.clear();
        playerGUI.playList.updateContent();
       
    }
    else if (button == &playerGUI.selectButton) {
        player.loadFile(playerGUI.sendFile);
        double totalTime = player.getTotalLength();
        playerGUI.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
        juce::String fileName = playerGUI.sendFile.getFileNameWithoutExtension();
        playerGUI.metaData(fileName, totalTime, authorName);
        HideButtons(playerGUI.stopButtonIcon);
        ShowButtons(playerGUI.startIcon);
    }
    else if (button == &startButton) {
        isStartWindow = false;
        startButton.setVisible(false);

        playerGUI.setVisible(true);
        repaint();
    }

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


double MainComponent::parseTimeString(const juce::String& timeStr)
{
    
    int colonPos = timeStr.indexOfChar(':');

    if (colonPos == -1)
    {
        
        return timeStr.getDoubleValue();
    }

    juce::String minsStr = timeStr.substring(0, colonPos);
    juce::String secsStr = timeStr.substring(colonPos + 1);

    int mins = minsStr.getIntValue();
    int secs = secsStr.getIntValue();

    return (double)(mins * 60 + secs);
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
