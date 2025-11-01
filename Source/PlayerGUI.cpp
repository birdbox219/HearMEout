#include "PlayerGUI.h"
#include "BinaryData.h"


PlayerGUI::PlayerGUI()
{
    // Existing constructor code remains unchanged
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

    // Icon Manager
    stopImageIcon = juce::ImageFileFormat::loadFrom(BinaryData::pauseyellow_png, BinaryData::pauseyellow_pngSize);
    goEnd = juce::ImageFileFormat::loadFrom(BinaryData::goEnd_png, BinaryData::goEnd_pngSize);
    goStart = juce::ImageFileFormat::loadFrom(BinaryData::goStart_png, BinaryData::goStart_pngSize);
    remove = juce::ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize);
    forward_10 = juce::ImageFileFormat::loadFrom(BinaryData::ten_for_png,BinaryData::ten_for_pngSize);
    backward_10 = juce::ImageFileFormat::loadFrom(BinaryData::ten_back_png,BinaryData::ten_back_pngSize);
    muteimage = juce::ImageFileFormat::loadFrom(BinaryData::volume_png,BinaryData::volume_pngSize);
    unmuteimage = juce::ImageFileFormat::loadFrom(BinaryData::no_volume_png,BinaryData::no_volume_pngSize);



    
   

    
    
    //------------------------------------------//


    




    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);

    addAndMakeVisible(volumeSlider);

    // Progress Slider
    progressSlider.setRange(0.0, 1.0, 0.001);
    progressSlider.setValue(0.0);
    progressSlider.setSliderStyle(juce::Slider::LinearBar);
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    progressSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow.withAlpha(0.6f));

    addAndMakeVisible(progressSlider);

    // Progress Label
    currentTimeLabel.setText("0:00", juce::dontSendNotification);
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

    // Theme Manager
    setOpaque(true);

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
    //styleButton(muteButton, juce::Colours::darkslategrey);
    // styleButton(skipBackButton, juce::Colours::darkslategrey);
    // styleButton(skipForwardButton, juce::Colours::darkslategrey);
    styleButton(addToListButton, juce::Colours::darkblue);
    styleButton(resetButton, juce::Colours::mediumvioletred);
    styleButton(selectButton, juce::Colours::green);
    styleButton(changeThemeButton, juce::Colours::purple);

    playList.setColour(juce::ListBox::backgroundColourId, juce::Colours::black.withAlpha(0.2f));
    playList.setColour(juce::ListBox::outlineColourId, juce::Colours::white.withAlpha(0.1f));
    playList.setColour(juce::ListBox::textColourId, juce::Colours::white);

    playList.setOpaque(false);
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
     /*   juce::ColourGradient gradient(
            juce::Colour(0xffDB2777).withAlpha(0.5f),
            0.0f, 0.0f,
            juce::Colour(0xff7C3AED).withAlpha(0.65f),
            0.0f, (float)getHeight(),
            false);
        g.setGradientFill(gradient);
        g.fillAll();*/

		//you can change as you want :)))))))))))))))))))))))))

        juce::ColourGradient gradient;

        switch (currentThemeIndex)
        {
        case 0: // Makima Theme - Red/Pink gradient (power, intensity)
            gradient = juce::ColourGradient(
                juce::Colour(0xffDC2626).withAlpha(0.4f),  // Red
                0.0f, 0.0f,
                juce::Colour(0xff7C3AED).withAlpha(0.65f), // Purple
                0.0f, (float)getHeight(),
                false);
            gradient.addColour(0.5, juce::Colour(0xffDB2777).withAlpha(0.55f)); // Pink
            break;

        case 1: // Nier Automata Theme - Cool Blue/Teal gradient (sci-fi, melancholic)
            gradient = juce::ColourGradient(
                juce::Colour(0xff1E293B).withAlpha(0.5f),  // Dark slate
                0.0f, 0.0f,
                juce::Colour(0xff0891B2).withAlpha(0.6f),  // Cyan
                0.0f, (float)getHeight(),
                false);
            gradient.addColour(0.5, juce::Colour(0xff0F172A).withAlpha(0.55f)); // Very dark blue
            break;

        case 2: // Doctor X Theme - Purple/Blue gradient (medical, professional)
            gradient = juce::ColourGradient(
                juce::Colour(0xff6B46C1).withAlpha(0.55f), // Deep purple
                0.0f, 0.0f,
                juce::Colour(0xff1E40AF).withAlpha(0.7f),  // Blue
                0.0f, (float)getHeight(),
                false);
            gradient.addColour(0.5, juce::Colour(0xff4C1D95).withAlpha(0.6f)); // Mid purple
            break;

        default: // Fallback gradient
            gradient = juce::ColourGradient(
                juce::Colour(0xff6B46C1).withAlpha(0.6f),
                0.0f, 0.0f,
                juce::Colour(0xff1E3A8A).withAlpha(0.75f),
                0.0f, (float)getHeight(),
                false);
            gradient.addColour(0.5, juce::Colour(0xff7C3AED).withAlpha(0.65f));
            break;
        }

        g.setGradientFill(gradient);
        g.fillAll();







    }
    else
    {
        juce::ColourGradient gradient(
            juce::Colour(0xff0891B2),  // Cyan
            0.0f, 0.0f,
            juce::Colour(0xff1E40AF),  // Blue
            0.0f, (float)getHeight(),
            false);
        gradient.addColour(0.5, juce::Colour(0xff0284C7)); // Sky blue
        g.setGradientFill(gradient);
        g.fillAll();
    }

    g.setColour(juce::Colours::transparentBlack.withAlpha(0.1f)); 
	
    g.fillRect(getLocalBounds());
}

void PlayerGUI::resized()
{
    auto bounds = getLocalBounds();
    const int margin = 10;

    
    float scale = juce::jmin(getWidth() / 900.0f, getHeight() / 600.0f);

   
    auto topBar = bounds.removeFromTop(70);

    
    loadButton.setBounds(20, 20, 100, 40);
    addToListButton.setBounds(125, 20, 40, 40);
    resetButton.setBounds(170, 20, 60, 40);
    selectButton.setBounds(230, 20, 60, 40);
    removeButton.setBounds(280, 20, 60, 40);

    
    changeThemeButton.setBounds(getWidth() - 210, 30, 100, 40);

    
    playList.setBounds(20, 70, 300, 300);

    
    int centerX = 320;
    title.setBounds(centerX, 90, 200, 20);
    time.setBounds(centerX, 115, 200, 20);
    author.setBounds(centerX, 140, 200, 20);

    
    int rightEdge = getWidth() - 20;

    
    int sliderWidth = 30;
    int sliderTop = 30;
    int sliderBottom = getHeight() - 310;;
    //int sliderBottom = 290;
    int sliderHeight = sliderBottom - sliderTop;

    volumeSlider.setBounds(rightEdge - sliderWidth, sliderTop, sliderWidth, sliderHeight);
    speedSlider.setBounds(rightEdge - (sliderWidth * 2 + 20), sliderTop, sliderWidth, sliderHeight);

    
    int abX = rightEdge - 180;
    int abY = sliderBottom + 20; 

    abLoopButton.setBounds(abX, abY, 160, 30);

    
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
    skipBackButton.setImages(
        false, // resizeButtonImageAutomatically
        true,  // preserveProportions
        true,  // useAlphaChannel
        backward_10, 1.0f, juce::Colours::transparentWhite, // Normal opacity
        backward_10, 0.8f, juce::Colours::transparentWhite, // Hover opacity
        backward_10, 1.0f, juce::Colours::yellow  //Pressed
    );
    skipForwardButton.setImages(
        false, // resizeButtonImageAutomatically
        true,  // preserveProportions
        true,  // useAlphaChannel
        forward_10, 1.0f, juce::Colours::transparentWhite, // Normal opacity
        forward_10, 0.8f, juce::Colours::transparentWhite, // Hover opacity
        forward_10, 1.0f, juce::Colours::yellow  //Pressed
    );
    muteButton.setImages(
        false, true, true,
        muteimage, 1.0f, juce::Colours::transparentWhite.withAlpha(0.1f),
        muteimage, 1.0f, juce::Colours::transparentWhite.withAlpha(0.1f),
        muteimage, 1.0f, juce::Colours::yellow.withAlpha(0.1f)
    );

    
    abStartTimeLabel.setBounds(abX, abY + 40, 50, 25);
    abStartLabel.setBounds(abX + 55, abY + 40, 105, 25);

    abEndTimeLabel.setBounds(abX, abY + 75, 50, 25);
    abEndLabel.setBounds(abX + 55, abY + 75, 105, 25);

    abStartButton.setBounds(abX, abY + 110, 160, 25);

    

   
    int progressY = getHeight() - 150;
    int progressLeft = 90;
    int progressRight = getWidth() - 90;

    currentTimeLabel.setBounds(20, progressY - 5, 60, 40);
    progressSlider.setBounds(progressLeft, progressY, progressRight - progressLeft, 30);
    TotalTimeLabel.setBounds(progressRight + 10, progressY - 5, 60, 40);

    
    int controlsY = getHeight() - 100;
    centerX = getWidth() / 2;

   
    int playBtnWidth = 60;
    int playBtnHeight = 60;
    int smallBtnWidth = 60;
    int smallBtnHeight = 40;
    int largeBtnWidth = 100;
    int largeBtnHeight = 40;
    int spacing = 20;

    
    startIcon.setBounds(centerX - playBtnWidth / 2, controlsY, playBtnWidth, playBtnHeight);
    stopButtonIcon.setBounds(startIcon.getBounds());

    
    skipBackButton.setBounds(centerX - playBtnWidth / 2 - smallBtnWidth - spacing,
        controlsY + 10, smallBtnWidth, smallBtnHeight);
    skipForwardButton.setBounds(centerX + playBtnWidth / 2 + spacing,
        controlsY + 10, smallBtnWidth, smallBtnHeight);

    
    goStartButton.setBounds(centerX - playBtnWidth / 2 - smallBtnWidth - largeBtnWidth - spacing * 2,
        controlsY, largeBtnWidth, largeBtnHeight);
    goEndButton.setBounds(centerX + playBtnWidth / 2 + smallBtnWidth + spacing * 2,
        controlsY, largeBtnWidth, largeBtnHeight);

    
    muteButton.setBounds(50, controlsY, largeBtnWidth, largeBtnHeight);
    loopButton.setBounds(getWidth() - 50 - 80, controlsY, 80, largeBtnHeight);

    
    if (stopImageIcon.isValid())
    {
        stopButtonIcon.setImages(false, true, true,
            stopImageIcon, 1.0f, juce::Colours::transparentBlack,
            stopImageOverIcon, 0.8f, juce::Colours::transparentWhite,
            stopImageDownIcon, 1.0f, juce::Colours::yellow);
    }

    if (goEnd.isValid())
    {
        goEndButton.setImages(false, true, true,
            goEnd, 1.0f, juce::Colours::transparentWhite,
            goEnd, 0.8f, juce::Colours::transparentWhite,
            goEnd, 1.0f, juce::Colours::yellow);
    }

    if (goStart.isValid())
    {
        goStartButton.setImages(false, true, true,
            goStart, 1.0f, juce::Colours::transparentWhite,
            goStart, 0.8f, juce::Colours::transparentWhite,
            goStart, 1.0f, juce::Colours::yellow);
    }

    if (remove.isValid())
    {
        removeButton.setImages(false, true, true,
            remove, 1.0f, juce::Colours::transparentWhite,
            remove, 0.8f, juce::Colours::transparentWhite,
            remove, 1.0f, juce::Colours::yellow);
    }

    //skipBackButton.setImages(false, true, true,
    //    backward_10, 1.0f, juce::Colours::transparentWhite,
    //    backward_10, 0.8f, juce::Colours::transparentWhite,
    //    backward_10, 1.0f, juce::Colours::yellow);

    //skipForwardButton.setImages(false, true, true,
    //    forward_10, 1.0f, juce::Colours::transparentWhite,
    //    forward_10, 0.8f, juce::Colours::transparentWhite,
    //    forward_10, 1.0f, juce::Colours::yellow);

    //muteButton.setImages(false, true, true,
    //    muteimage, 1.0f, juce::Colours::transparentWhite,
    //    muteimage, 1.0f, juce::Colours::transparentWhite,
    //    muteimage, 1.0f, juce::Colours::transparentWhite);
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














