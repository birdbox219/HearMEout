#include "PlayerGUI.h"
#include "BinaryData.h"



PlayerGUI::PlayerGUI()
{
    
   
    //backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::MakimaTheme1_png, BinaryData::MakimaTheme1_pngSize);
    //backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::NierAutomataTheme2_png, BinaryData::NierAutomataTheme2_pngSize);
    
    addAndMakeVisible(loadButton);
    addAndMakeVisible(changeThemeButton);
    changeThemeButton.setButtonText("Theme");
    changeThemeButton.onClick = [this]()
    {
            ChangeTheme(); 
    };
    
    addAndMakeVisible(goStartButton);
    addAndMakeVisible(goEndButton);
    addAndMakeVisible(title);
    addAndMakeVisible(time);
    addAndMakeVisible(author);
    addAndMakeVisible(startIcon);
    addAndMakeVisible(stopButtonIcon);
    
 
    addAndMakeVisible(loopButton);
    addAndMakeVisible(abLoopButton);
    addAndMakeVisible(abStartButton);

    

    addAndMakeVisible(muteButton);
    addAndMakeVisible(startIcon);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(skipBackButton);
    addAndMakeVisible(skipForwardButton);




    // Playlist-related components
    addAndMakeVisible(addToListButton);
    addAndMakeVisible(resetButton);
    addAndMakeVisible(playList);
    playList.setModel(this);
  addAndMakeVisible(removeButton);
    addAndMakeVisible(selectButton);
    speedSlider.setRange(0.1, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.setSliderStyle(juce::Slider::LinearBarVertical);

    speedSlider.setTextValueSuffix("x");
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    speedSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    speedSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    

   
  
 
    
    
    
    //Icon Manager
    

     
    stopImageIcon = juce::ImageFileFormat::loadFrom(BinaryData::pauseyellow_png, BinaryData::pauseyellow_pngSize);
    
    


    goEnd = juce::ImageFileFormat::loadFrom(BinaryData::goEnd_png, BinaryData::goEnd_pngSize);
    goStart = juce::ImageFileFormat::loadFrom(BinaryData::goStart_png, BinaryData::goStart_pngSize);
    remove = juce::ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize);
    


    
   

    
    
    //------------------------------------------//


    




    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);




    //volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //Progress Slider
    progressSlider.setRange(0.0, 1.0, 0.001);
    progressSlider.setValue(0.0);
    progressSlider.setSliderStyle(juce::Slider::LinearBar);  
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    progressSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow.withAlpha(0.6f));
    //progressSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    



    addAndMakeVisible(progressSlider);

    //Progress Lebel
    currentTimeLabel.setText("0:00", juce::dontSendNotification);
    //currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(currentTimeLabel);

    TotalTimeLabel.setText("0:00", juce::dontSendNotification);
    addAndMakeVisible(TotalTimeLabel);

    abStartTimeLabel.setText("Start:", juce::dontSendNotification);
    abStartTimeLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(abStartTimeLabel);

    abEndTimeLabel.setText("End:", juce::dontSendNotification);
    abEndTimeLabel.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(abEndTimeLabel);


    abStartLabel.setText("0:00", juce::dontSendNotification);
    abStartLabel.setEditable(true);
    abStartLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
    abStartLabel.setColour(juce::Label::outlineColourId, juce::Colours::orangered);
    abStartLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(abStartLabel);

    abEndLabel.setText("0:00", juce::dontSendNotification);
    abEndLabel.setEditable(true);
    abEndLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey);
    abEndLabel.setColour(juce::Label::outlineColourId, juce::Colours::orangered);
    abEndLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(abEndLabel);


    abStartTimeLabel.setVisible(false);
    abEndTimeLabel.setVisible(false);
    abStartLabel.setVisible(false);
    abEndLabel.setVisible(false);
    abStartButton.setVisible(false);

	//---------------Theme Manager-----------------//


     //Theme manager
    //setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::blueviolet);
   
    setOpaque(true); 

    // Make buttons semi-transparent with glass effect
    auto styleButton = [](juce::TextButton& btn, juce::Colour baseColour) {
        btn.setColour(juce::TextButton::buttonColourId, baseColour.withAlpha(0.2f));
        btn.setColour(juce::TextButton::buttonOnColourId, baseColour.withAlpha(0.4f));
        btn.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
        btn.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
        };

    styleButton(loadButton, juce::Colours::darkblue);
    styleButton(loopButton, juce::Colours::darkgrey);
    styleButton(abLoopButton, juce::Colours::darkgrey);
    styleButton(abStartButton, juce::Colours::darkgrey);
    styleButton(muteButton, juce::Colours::darkslategrey);
    styleButton(skipBackButton, juce::Colours::darkslategrey);
    styleButton(skipForwardButton, juce::Colours::darkslategrey);
    styleButton(addToListButton, juce::Colours::darkblue);
    styleButton(resetButton, juce::Colours::mediumvioletred);
    styleButton(selectButton, juce::Colours::green);
	styleButton(changeThemeButton, juce::Colours::purple);

    
    

    
    playList.setColour(juce::ListBox::backgroundColourId, juce::Colours::black.withAlpha(0.2f));
    playList.setColour(juce::ListBox::outlineColourId, juce::Colours::white.withAlpha(0.1f));
    playList.setColour(juce::ListBox::textColourId, juce::Colours::white);

   
    playList.setOpaque(false);




	










    //setSize(500, 250);
    //setAudioChannels(0, 2);
}


PlayerGUI::~PlayerGUI() {}

 
void PlayerGUI::paint(juce::Graphics& g)
{
    //g.fillAll(juce::Colours::blueviolet);
    if (backgroundImage.isValid())
    {
        g.drawImage(backgroundImage,
            getLocalBounds().toFloat(),
            juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        g.fillAll(juce::Colours::blueviolet);
    }

    g.setColour(juce::Colours::transparentBlack.withAlpha(0.25f)); 
	
    g.fillRect(getLocalBounds());
}

void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    changeThemeButton.setBounds(getWidth() - 230, 30, 100, 40);
    
     // Side buttons
    goStartButton.setBounds(200, 500, 100, 40);
    goEndButton.setBounds(660, 500, 100, 40);

    // Central control icons
    startIcon.setBounds(450, 500, 60, 60);
    stopButtonIcon.setBounds(450, 500, 60, 60);

    // New skip buttons
    skipBackButton.setBounds(370, 510, 60, 40);
    skipForwardButton.setBounds(530, 510, 60, 40);

    title.setBounds(320, 90, 100, 40);
    time.setBounds(320, 110, 100, 40);
    author.setBounds(320, 130, 100, 40);
    

    loopButton.setBounds(800, 500, 80, 40);
    abLoopButton.setBounds(760, 330, 120, 30);
    abStartButton.setBounds(760, 433, 120, 20);


    
    

    //mute button
    muteButton.setBounds(50, 500, 100, 40);
   



    

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
    removeButton.setImages(
        false, // resizeButtonImageAutomatically
        true,  // preserveProportions
        true,  // useAlphaChannel
        remove, 1.0f, juce::Colours::transparentWhite, // Normal opacity
        remove, 0.8f, juce::Colours::transparentWhite, // Hover opacity
        remove, 1.0f, juce::Colours::yellow  //Pressed
    );
    /*prevButton.setBounds(340, y, 80, 40);
    nextButton.setBounds(440, y, 80, 40);*/
    //Sliders Bounds

    volumeSlider.setBounds(830, 30, 30 , getHeight() - 310 );

    int progressY = 450;
    progressSlider.setBounds(90, progressY, getWidth() - 180, 30);
    //speed slider
    speedSlider.setBounds(780, 30, 30, getHeight() - 310);//audio speed length and width.







    //Lebels Bounds
    currentTimeLabel.setBounds(20, progressY - 30, 60, 80);
    TotalTimeLabel.setBounds(getWidth() - 80, progressY - 30, 60, 80);

    // Playlist-related components
    addToListButton.setBounds(125, 20, 40, 40);
    
    resetButton.setBounds(170, 20, 60, 40);
    
    playList.setBounds(20, 70, 300, 300);
    selectButton.setBounds(230, 20, 60, 40);
    removeButton.setBounds(280, 20, 60, 40);
   

 


  

    //A-B Lebels

    abStartTimeLabel.setBounds(700, 370, 50, 25);
    abStartLabel.setBounds(760, 370, 80, 25);

    abEndTimeLabel.setBounds(700, 405, 50, 25);
    abEndLabel.setBounds(760, 405, 80, 25);




}
void PlayerGUI::metaData(juce::String& fileName, double& totalTime, juce::String& authorName)
{
    title.setText("Title: " + fileName, juce::dontSendNotification);
    author.setText("Auhtor: " + authorName, juce::dontSendNotification);

    int h = 0;
    int m = 0;
    int s = 0;
    m = totalTime / 60;
    s = int(totalTime) % 60;
    if (m >= 60) {
        h = m / 60; m = m % 60;
        time.setText("duration: " + juce::String(h) + ":" + juce::String(m) + ":" + juce::String(s), juce::dontSendNotification);
    }
    //added if file less than 60min to will dispaly only mins
    else
    {
        time.setText("duration: " + juce::String(m) + ":" + juce::String(s).paddedLeft('0', 2), juce::dontSendNotification);
    }




}

void PlayerGUI::showFile(juce::File& file,double time) {
 juce::File f;
    bool exist{};
    if (!files.empty()) {
        for (auto f : files) {

            if (file.getFileNameWithoutExtension() == f.file.getFileNameWithoutExtension()) {
                exist = 1;
            }
        }
    }
    if (!exist) {
        fileInfo info;
        info.file = file;
        info.time = time;
        files.push_back(info);
       

    }
    playList.updateContent();
    playList.repaint();
}
int PlayerGUI::getNumRows()
{
    return files.size();
 

}


void PlayerGUI::paintListBoxItem(int rowNumber, juce::Graphics& g,
    int width, int height, bool rowIsSelected)
{
;
    if (rowNumber < files.size())
    {

        if (rowIsSelected)
        {
            g.setColour(juce::Colours::white.withAlpha(0.2f));
            g.fillRoundedRectangle(2, 2, width - 4, height - 4, 3.0f);
        }

        
        g.setColour(juce::Colours::white);
        g.drawText(files[rowNumber].file.getFileNameWithoutExtension(),
            5, 0, width - 10, height,
            juce::Justification::centredLeft, true);

        
        int h = 0;
        int m = files[rowNumber].time / 60;
        int s = files[rowNumber].time % 60;

        g.drawText(juce::String(h) + ":" + juce::String(m) + ":" + juce::String(s),
            190, 0, width - 10, height,
            juce::Justification::centredLeft, true);
        
    }
}
 

void PlayerGUI::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected >= 0)
    {
        auto file = files[lastRowSelected];
       
        sendFile = file.file;
        sendRow = lastRowSelected;
    }                                                                                                                                                                    
}

void PlayerGUI::ChangeTheme()
{
	int numpersOfThemes = 3;
    // cycle between 2 or more backgrounds
    currentThemeIndex = (currentThemeIndex + 1) % numpersOfThemes;
    switch (currentThemeIndex)
    {
    case 0:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::MakimaTheme1_png,
            BinaryData::MakimaTheme1_pngSize);
        break;

    case 1:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::NierAutomataTheme2_png,
            BinaryData::NierAutomataTheme2_pngSize);
        break;

    case 2:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::DoctorXTheme3_png,
            BinaryData::DoctorXTheme3_pngSize);
        break;
    }

    

    repaint();
}














