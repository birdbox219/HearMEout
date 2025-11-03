#include "MainComponent.h"
#include "BinaryData.h"
/*
Keep working on this project structure dont change without permision !
BRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
 
*/
MainComponent::MainComponent()
{
	//Load saved session 
    //bool sessionLoaded = player.LoadLastSession();
    bool sessionLoaded = sessionManager.loadSession(player, playerGUI);

    player.readerSource2.reset(nullptr);
    player.transportSource2.setSource(nullptr);
    

  
    
 

    isStartWindow = true;
    addAndMakeVisible(playerGUI);

    playerGUI.setVisible(false);
    addAndMakeVisible(startButton);
    startButton.addListener(this);
    addAndMakeVisible(singleTrackButton);
    singleTrackButton.setVisible(false);
    singleTrackButton.addListener(this);
    singleTrackButton.setColour(juce::TextButton::buttonColourId, juce::Colours::purple);
	singleTrackButton.setColour(juce::TextButton::buttonColourId, juce::Colours::purple.withAlpha(0.2f));
	singleTrackButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::purple.withAlpha(0.4f));
	singleTrackButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
	singleTrackButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    addAndMakeVisible(twoTracksButton);
    twoTracksButton.addListener(this);
    twoTracksButton.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumpurple);
    twoTracksButton.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumpurple.withAlpha(0.2f));
    twoTracksButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::mediumpurple.withAlpha(0.4f));
    twoTracksButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    twoTracksButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
    twoTracksButton.setVisible(false);
   


  
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

    //================================================================== track2
    addAndMakeVisible(playerGUI2);
    playerGUI2.setVisible(false);

    playerGUI2.loadButton.addListener(this);
    playerGUI2.selectButton.addListener(this);
    playerGUI2.loopButton.addListener(this);
    playerGUI2.muteButton.addListener(this);
    playerGUI2.startIcon.addListener(this);
    playerGUI2.stopButtonIcon.addListener(this);
    playerGUI2.goStartButton.addListener(this);
    playerGUI2.goEndButton.addListener(this);
    playerGUI2.addToListButton.addListener(this);
    playerGUI2.resetButton.addListener(this);
    playerGUI2.removeButton.addListener(this);
    playerGUI2.speedSlider.addListener(this);
    playerGUI2.volumeSlider.addListener(this);
    playerGUI2.progressSlider.addListener(this);
    playerGUI2.progressSlider.addMouseListener(this, false);
    playerGUI2.skipBackButton.onClick = [this] { player.skipBackward2(10.0); };
    playerGUI2.skipForwardButton.onClick = [this] { player.skipForward2(10.0); };
    playerGUI2.loopButton.setVisible(true);
    playerGUI2.abLoopButton.addListener(this);
    playerGUI2.abStartButton.addListener(this);
    playerGUI2.startIcon.setVisible(true);
    playerGUI2.stopButtonIcon.setVisible(false);
    playerGUI2.skipBackButton.setVisible(true);
    playerGUI2.skipForwardButton.setVisible(true);

    // Add buttons
   /* for (auto* btn : { &loadButton, &playButton , &stopButton  })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }*/

    

    
    setSize(900, 600);
    setAudioChannels(0, 2);

    startTimer(100);
    setWantsKeyboardFocus(true);

    
    
}

MainComponent::~MainComponent()
{
    sessionManager.saveSession(player, playerGUI);
	//PlayerGUI().~PlayerGUI();
    shutdownAudio();
	

}
//----------------------------------------------------------------//NOTED
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

    singleTrackButton.setBounds(350, 200, 100, 40);
    twoTracksButton.setBounds(350, 200, 100, 40);
    playerGUI.setBounds(getLocalBounds().removeFromLeft(getLocalBounds().getWidth() / 2));
    playerGUI2.setBounds(getLocalBounds().removeFromRight(getLocalBounds().getWidth() / 2));
}
bool MainComponent::keyPressed(const juce::KeyPress& key) {
    if (key == juce::KeyPress::spaceKey) {
        if (isPlaying) {
           playerGUI.startIcon.triggerClick();
           isPlaying = false;
        }
        else {
            playerGUI.stopButtonIcon.triggerClick();
            isPlaying = true;
        }
       
        return true;
    }
    else if (key == juce::KeyPress::leftKey) {
        playerGUI.skipBackButton.triggerClick();
        return true;
    }
    else if (key == juce::KeyPress::rightKey) {
        playerGUI.skipForwardButton.triggerClick();
        return true;
    }
    return false;
}



//I added the same buttons again for the second track - Alaa
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
                
                authorName = player.loadFile(file);
                double totalTime = player.getTotalLength();
                playerGUI.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                juce::String fileName = file.getFileNameWithoutExtension();
                playerGUI.metaData(fileName, totalTime, authorName);


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
        player.toggleMute();
    if (player.isMuted)
    {
        playerGUI.volumeSlider.setValue(0.0);
        playerGUI.muteButton.setImages(
            false, true, true,
            playerGUI.unmuteimage, 1.0f, juce::Colours::transparentWhite,
            playerGUI.unmuteimage, 1.0f, juce::Colours::transparentWhite,
            playerGUI.unmuteimage, 1.0f, juce::Colours::transparentWhite
        );
    }
    else
    {
        playerGUI.volumeSlider.setValue(player.lastGain);// update UI - mahmoud 
        playerGUI.muteButton.setImages(
            false, true, true,
            playerGUI.muteimage, 1.0f, juce::Colours::transparentWhite,
            playerGUI.muteimage, 1.0f, juce::Colours::transparentWhite,
            playerGUI.muteimage, 1.0f, juce::Colours::transparentWhite
        );
    }

        
    }
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
                playerGUI.showFile(file, totalTime);


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

    else if (button == &playerGUI.removeButton) {
                        if (!playerGUI.files.empty()) {
                            playerGUI.files.erase(playerGUI.files.begin() + playerGUI.sendRow);
                            playerGUI.playList.updateContent();
                        }

                        }
    //===========================================================================================track2
    else  if (button == &playerGUI2.loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...", juce::File{}, "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                //player.loadFile(file);
                authorName = player.loadFile2(file);
                double totalTime = player.getTotalLength2();
                playerGUI2.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                juce::String fileName = file.getFileNameWithoutExtension();
                playerGUI2.metaData(fileName, totalTime, authorName);


                //reset A-B
                playerGUI2.abLoopActive = false;
                playerGUI2.abControlsVisible = false;
                playerGUI2.abStartTimeLabel.setVisible(false);
                playerGUI2.abEndTimeLabel.setVisible(false);
                playerGUI2.abStartLabel.setVisible(false);
                playerGUI2.abEndLabel.setVisible(false);
                playerGUI2.abStartButton.setVisible(false);
                playerGUI2.abLoopButton.setButtonText("Set A-B Loop");
                playerGUI2.abLoopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);


                HideButtons(playerGUI2.stopButtonIcon);
                ShowButtons(playerGUI2.startIcon);



            });


            }

    else if (button == &playerGUI2.startIcon)
    {
        player.Start2();
        HideButtons(playerGUI2.startIcon);
        ShowButtons(playerGUI2.stopButtonIcon);
        }
    else if (button == &playerGUI2.stopButtonIcon)
    {
        player.Stop2();
        HideButtons(playerGUI2.stopButtonIcon);
        ShowButtons(playerGUI2.startIcon);
        }
    else if (button == &playerGUI2.goStartButton) {
        player.goStart2();
            playerGUI2.progressSlider.setValue(0.0);
            }
    else if (button == &playerGUI2.goEndButton) {
        player.goEnd2();
                playerGUI2.progressSlider.setValue(0.0);
                }

    else if (button == &playerGUI2.loopButton)
    {
        bool currentlyLooping = player.isLooping2();
        player.setLooping2(!currentlyLooping);

        playerGUI2.loopButton.setColour(
            juce::TextButton::buttonColourId,
            player.isLooping2() ? juce::Colours::orangered : juce::Colours::darkgrey.withAlpha(0.2f)
        );

        if (player.isLooping2() && playerGUI2.abLoopActive)
        {
            playerGUI2.abLoopActive = false;
            player.setABLoop2(false);
            playerGUI2.abStartButton.setButtonText("Start A-B");
            playerGUI2.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey.withAlpha(0.2f));
        }


        }

    else if (button == &playerGUI2.abLoopButton)
    {

        playerGUI2.abControlsVisible = !playerGUI2.abControlsVisible;

        playerGUI2.abStartTimeLabel.setVisible(playerGUI2.abControlsVisible);
        playerGUI2.abEndTimeLabel.setVisible(playerGUI2.abControlsVisible);
        playerGUI2.abStartLabel.setVisible(playerGUI2.abControlsVisible);
        playerGUI2.abEndLabel.setVisible(playerGUI2.abControlsVisible);
        playerGUI2.abStartButton.setVisible(playerGUI2.abControlsVisible);

        if (playerGUI2.abControlsVisible)
        {

            double totalTime = player.getTotalLength2();
            playerGUI2.abStartLabel.setText("0:00", juce::dontSendNotification);
            playerGUI2.abEndLabel.setText(formatTime(totalTime), juce::dontSendNotification);
            playerGUI2.abLoopButton.setButtonText("Hide A-B");
        }
        else
        {
            playerGUI2.abLoopButton.setButtonText("Set A-B Loop");


            if (playerGUI2.abLoopActive)
            {
                playerGUI2.abLoopActive = false;
                player.setABLoop2(false);
                playerGUI2.abStartButton.setButtonText("Start A-B");
                playerGUI2.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
            }
        }
        }


    else if (button == &playerGUI2.abStartButton)
    {
        // Parse time strings and start A-B loop
        juce::String startTimeStr = playerGUI2.abStartLabel.getText();
        juce::String endTimeStr = playerGUI2.abEndLabel.getText();

        double startTime = parseTimeString(startTimeStr);
        double endTime = parseTimeString(endTimeStr);
        double totalTime = player.getTotalLength2();


        if (startTime < 0) startTime = 0;
        if (endTime > totalTime) endTime = totalTime;
        if (startTime >= endTime)
        {
            // Show error 
            playerGUI2.abStartButton.setButtonText("Invalid Times!");
            juce::Timer::callAfterDelay(2000, [this]() {
                playerGUI2.abStartButton.setButtonText(playerGUI2.abLoopActive ? "Stop A-B" : "Start A-B");
                });
            return;
        }


        playerGUI2.abLoopActive = !playerGUI2.abLoopActive;

        if (playerGUI2.abLoopActive)
        {

            player.setABPoints2(startTime, endTime);
            player.setABLoop2(true);


            if (player.isLooping2())
            {
                player.setLooping2(false);
                playerGUI2.loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
            }

            playerGUI2.abStartButton.setButtonText("Stop A-B");
            playerGUI2.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cyan);


            player.setPosition2(startTime);
        }
        else
        {
            // Disable A-B loop
            player.setABLoop2(false);
            playerGUI2.abStartButton.setButtonText("Start A-B");
            playerGUI2.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
        }
        }

    else if (button == &playerGUI2.muteButton)
    {
        player.toggleMute2();
        if (player.isMuted2)
        {
            playerGUI2.volumeSlider.setValue(0.0);
            playerGUI2.muteButton.setImages(
                false, true, true,
                playerGUI2.unmuteimage, 1.0f, juce::Colours::transparentWhite,
                playerGUI2.unmuteimage, 1.0f, juce::Colours::transparentWhite,
                playerGUI2.unmuteimage, 1.0f, juce::Colours::transparentWhite
            );
        }
        else
        {
            playerGUI2.volumeSlider.setValue(player.lastGain2);// update UI - mahmoud 
            playerGUI2.muteButton.setImages(
                false, true, true,
                playerGUI2.muteimage, 1.0f, juce::Colours::transparentWhite,
                playerGUI2.muteimage, 1.0f, juce::Colours::transparentWhite,
                playerGUI2.muteimage, 1.0f, juce::Colours::transparentWhite
            );
        }


        }

        // Playlist-related components
    else if (button == &playerGUI2.addToListButton) {
            fileChooser = std::make_unique<juce::FileChooser>(
                "Select an audio file...", juce::File{}, "*.wav;*.mp3");

            fileChooser->launchAsync(
                juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                [this](const juce::FileChooser& fc)
                {
                    auto file = fc.getResult();

                    authorName = player.loadFile2(file);
                    double totalTime = player.getTotalLength2();
                    playerGUI2.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                    juce::String fileName = file.getFileNameWithoutExtension();
                    playerGUI2.metaData(fileName, totalTime, authorName);
                    player.addToList(file);
                    playerGUI2.showFile(file, totalTime);


                });
                }
    else if (button == &playerGUI2.resetButton) {
                    player.files.clear();
                    playerGUI2.files.clear();
                    playerGUI2.playList.updateContent();

                    }
    else if (button == &playerGUI2.selectButton) {
        player.loadFile2(playerGUI2.sendFile);
                        double totalTime = player.getTotalLength2();
                        playerGUI2.TotalTimeLabel.setText(formatTime(totalTime), juce::dontSendNotification);
                        juce::String fileName = playerGUI2.sendFile.getFileNameWithoutExtension();
                        playerGUI2.metaData(fileName, totalTime, authorName);
                        HideButtons(playerGUI2.stopButtonIcon);
                        ShowButtons(playerGUI2.startIcon);
                        }
   
    else if (button == &playerGUI2.removeButton) {
                                if (!playerGUI2.files.empty()) {
                                    playerGUI2.files.erase(playerGUI2.files.begin() + playerGUI2.sendRow);
                                    playerGUI2.playList.updateContent();
                                }

                                }
    else if (button == &startButton) {
        isStartWindow = false;
        startButton.setVisible(false);
        singleTrackButton.setVisible(false);
        twoTracksButton.setVisible(true);
        playerGUI.setVisible(true);
        playerGUI2.setVisible(false);
        playerGUI.setBounds(getLocalBounds());

       
  
        repaint();
    }

 else if (button == &twoTracksButton) {
     singleTrackButton.setVisible(true);
     twoTracksButton.setVisible(false);
     playerGUI.setVisible(true);
     playerGUI2.setVisible(true);
     

     playerGUI.setBounds(getLocalBounds().removeFromLeft(getLocalBounds().getWidth() / 2));
     playerGUI2.setBounds(getLocalBounds().removeFromRight(getLocalBounds().getWidth() / 2));
	 
     repaint();
 }
 else if (button == &singleTrackButton) {
     singleTrackButton.setVisible(false);
     twoTracksButton.setVisible(true);
     playerGUI.setVisible(true);
     playerGUI2.setVisible(false);
     playerGUI.setBounds(getLocalBounds());


     player.setTrackActive(2, false);

    playerGUI2.progressSlider.setValue(0.0, juce::dontSendNotification);
    playerGUI2.currentTimeLabel.setText("0:00", juce::dontSendNotification);
    HideButtons(playerGUI2.stopButtonIcon);
    ShowButtons(playerGUI2.startIcon);
    
  
     repaint();
 }
 /*else if (button == &homeButton) {
     isStartWindow = true;
     singleTrackButton.setVisible(true);
     twoTracksButton.setVisible(true);
     playerGUI.setVisible(false);
     playerGUI2.setVisible(false);
     homeButton.setVisible(false);
     player.Stop2();
     player.Stop();

     repaint();
                            }*/

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
    //==========================================================track2
    if (slider == &playerGUI2.volumeSlider)
    {
        player.setGain2((float)slider->getValue());
    }

    if (slider == &playerGUI2.speedSlider)
    {
        player.setSpeed2(slider->getValue());
    }

    if (slider == &playerGUI2.progressSlider && isDraggingSlider2)
    {
        double totalLength = player.getTotalLength2();
        double newPosition = slider->getValue() * totalLength;
        player.setPosition2(newPosition);
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

    if (!isDraggingSlider2)
    {
       
        double currentLenght2 = player.getCurrentPosition2();
        double TotalLenght2 = player.getTotalLength2();


        if (TotalLenght2 > 0.0)
        {
            playerGUI2.progressSlider.setValue(currentLenght2 / TotalLenght2, juce::dontSendNotification);
            playerGUI2.currentTimeLabel.setText(formatTime(currentLenght2), juce::dontSendNotification);

        }
    }
    
}


juce::String MainComponent::formatTime(double seconds)
{
    int mins = (int)seconds / 60;
    int secs = (int)seconds % 60;
    return juce::String(mins) + ":" + juce::String(secs).paddedLeft('0', 2);
}

// Parse time string format 
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
    if (event.eventComponent == &playerGUI2.progressSlider)
    {
        isDraggingSlider2 = true;
    }
}

void MainComponent::mouseUp(const juce::MouseEvent& event)
{
    if (event.eventComponent == &playerGUI.progressSlider)
    {
        isDraggingSlider = false;
    }
    if (event.eventComponent == &playerGUI2.progressSlider)
    {
        isDraggingSlider2 = false;
    }
}
