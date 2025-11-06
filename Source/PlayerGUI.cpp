#include "PlayerGUI.h"
#include "BinaryData.h"
#include <memory>


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

    addAndMakeVisible(loadCustomThemeButton);
    loadCustomThemeButton.setButtonText("Custom");
    loadCustomThemeButton.onClick = [this]()
        {
            LoadCustomTheme();
        };

    // --- START: Ensure marker buttons belong to this PlayerGUI and are visible ---
    addAndMakeVisible(addMarkerButton);
    addAndMakeVisible(removeMarkerButton);

    // Give them visible labels (optional but helpful)
    addMarkerButton.setButtonText("Add Marker");
    removeMarkerButton.setButtonText("Remove Marker");

    // Basic style to match other buttons (adjust if you have a theme function)
    addMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue.withAlpha(0.18f));
    addMarkerButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkblue.withAlpha(0.36f));
    removeMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue.withAlpha(0.18f));
    removeMarkerButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkblue.withAlpha(0.36f));
    // --- END marker button block ---

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
    playList.addMouseListener(this, true);
    playList.setRowHeight(35);
    
    addAndMakeVisible(removeButton);
    addAndMakeVisible(addMarkerButton);
    addAndMakeVisible(removeMarkerButton);
    addMarkerButton.setButtonText("Add Marker");
    removeMarkerButton.setButtonText("Remove Marker");

    addMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue.withAlpha(0.18f));
    addMarkerButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkblue.withAlpha(0.36f));
    removeMarkerButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue.withAlpha(0.18f));
    removeMarkerButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::darkblue.withAlpha(0.36f));
    // --- END marker button block ---

    addAndMakeVisible(selectButton);
    speedSlider.setRange(0.1, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.setSliderStyle(juce::Slider::LinearBarVertical);

    speedSlider.setTextValueSuffix("x");
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);
    speedSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow.withAlpha(0.6f));
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
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow.withAlpha(0.6f));
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
    abStartLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey.withAlpha(0.2f));
    abStartLabel.setColour(juce::Label::outlineColourId, juce::Colours::orangered);
    abStartLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(abStartLabel);

    abEndLabel.setText("0:00", juce::dontSendNotification);
    abEndLabel.setEditable(true);
    abEndLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkgrey.withAlpha(0.2f));
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
    styleButton(addToListButton, juce::Colours::darkblue);
    styleButton(resetButton, juce::Colours::mediumvioletred);
    styleButton(selectButton, juce::Colours::green);
    styleButton(changeThemeButton, juce::Colours::darkblue);
    styleButton(loadCustomThemeButton, juce::Colours::darkgrey);


    playList.setColour(juce::ListBox::backgroundColourId, juce::Colours::black.withAlpha(0.05f));
    playList.setColour(juce::ListBox::outlineColourId, juce::Colours::white.withAlpha(0.05f));
    playList.setColour(juce::ListBox::textColourId, juce::Colours::white);

    /*playList.setColour(juce::ScrollBar::thumbColourId, juce::Colours::yellow.withAlpha(0.4f));
    playList.setColour(juce::ScrollBar::trackColourId, juce::Colours::black.withAlpha(0.1f));*/

    auto& scrollbar = playList.getVerticalScrollBar();
    scrollbar.setColour(juce::ScrollBar::thumbColourId, juce::Colours::yellow.withAlpha(0.6f));
    scrollbar.setColour(juce::ScrollBar::trackColourId, juce::Colours::black.withAlpha(0.2f));
    scrollbar.setColour(juce::ScrollBar::backgroundColourId, juce::Colours::transparentBlack);




    playList.setOpaque(false);
	playList.setRowHeight(40);
}


PlayerGUI::~PlayerGUI() {}

 
void PlayerGUI::paint(juce::Graphics& g)
{
    
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


        if (currentThemeIndex == 3)
        {
            gradient = juce::ColourGradient(
                juce::Colour(0xff1E1E1E).withAlpha(0.3f),
                0.0f, 0.0f,
                juce::Colour(0xff2D2D2D).withAlpha(0.4f),
                0.0f, (float)getHeight(),
                false);
        }

        else
        {
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


// === Marker visuals
    int row = playList.getSelectedRow();
    if (row < 0 || row >=static_cast<int>(files.size()))
    {
        return;
    }

    const auto& f = files[row];
    double len = std::max((double)f.time, 0.001);
    auto area = progressSlider.getBounds().toFloat();
    float y1 = area.getY();
    float y2 = area.getBottom();

    g.setColour(juce::Colours::red);

    for (double t : f.markersTime)
    {
        if (t < 0.0 || t > len)
            continue;

        float x = area.getX() + (float)(t / len) * area.getWidth();
        g.drawLine(x, y1, x, y2, 3.0f);
    }
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
    addMarkerButton.setBounds(345, 20, 100, 40);
    removeMarkerButton.setBounds(455, 20, 100, 40);


    changeThemeButton.setBounds(getWidth() - 210, 30, 100, 40);
    loadCustomThemeButton.setBounds(getWidth() - 210, 75, 100, 40);

    
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
        muteimage, 1.0f, juce::Colours::yellow.withAlpha(0.9f)
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
    


    bool isHovered = (rowNumber == hoveredRow);

    
    if (rowIsSelected)
    {
        // Gradient for selected item
        juce::ColourGradient selectedGradient(
            juce::Colours::yellow.withAlpha(0.15f), 4, 2,
            juce::Colours::yellow.withAlpha(0.25f), 4, height - 2,
            false
        );
        g.setGradientFill(selectedGradient);
        g.fillRoundedRectangle(4, 2, width - 8, height - 4, 8.0f);

        // Add a glowing accent line on the left
        g.setColour(juce::Colours::yellow.withAlpha(0.9f));
        g.fillRoundedRectangle(8, 8, 4, height - 16, 2.0f);
    }
    // Hover effect
    else if (isHovered)
    {
        g.setColour(juce::Colours::white.withAlpha(0.08f));
        g.fillRoundedRectangle(4, 2, width - 8, height - 4, 8.0f);

        // Subtle left accent on hover
        g.setColour(juce::Colours::yellow.withAlpha(0.3f));
        g.fillRoundedRectangle(8, 10, 2, height - 20, 1.0f);
    }

    // Draw track number
    g.setColour(juce::Colours::white.withAlpha(0.4f));
    g.setFont(juce::Font(11.0f, juce::Font::bold));
    g.drawText(juce::String(rowNumber + 1),
        16, 0, 20, height,
        juce::Justification::centredLeft, true);

    // Song name with better spacing
    g.setColour(rowIsSelected ? juce::Colours::white : juce::Colours::white.withAlpha(0.9f));
    g.setFont(juce::Font(14.0f, rowIsSelected ? juce::Font::bold : juce::Font::plain));

    juce::String songName = files[rowNumber].file.getFileNameWithoutExtension();
    // Truncate long names
    if (songName.length() > 30)
        songName = songName.substring(0, 27) + "...";

    g.drawText(songName,
        40, 0, width - 140, height,
        juce::Justification::centredLeft, true);

        
        int h = 0;
        int m = files[rowNumber].time / 60;
        int s = static_cast<int>(files[rowNumber].time) % 60;
        

    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font(12.0f, juce::Font::plain));

    

    g.drawText(juce::String(m) + ":" + juce::String(s).paddedLeft('0', 2),
        width - 75, 0, 60, height,
        juce::Justification::centredRight, true);

    // Draw subtle separator line between items (not on last item)
    if (rowNumber < files.size() - 1)
    {
        g.setColour(juce::Colours::white.withAlpha(0.05f));
        g.drawLine(15, height - 1, width - 15, height - 1, 1.0f);
    }

    // Add play icon when hovering
    if (isHovered && !rowIsSelected)
    {
        g.setColour(juce::Colours::yellow.withAlpha(0.6f));
        g.setFont(juce::Font(16.0f));
        
    }
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

void PlayerGUI::listBoxItemDoubleClicked(int row, const juce::MouseEvent&)
{
    if (row >= 0 && row < files.size())
    {
        sendFile = files[row].file;
        sendRow = row;
        
        selectButton.triggerClick();
    }
}


void PlayerGUI::mouseMove(const juce::MouseEvent& e)
{
    



    auto posInList = playList.getLocalPoint(e.eventComponent, e.getPosition());
    int row = playList.getRowContainingPosition(posInList.x, posInList.y);

    if (row != hoveredRow)
    {
        DBG("Hover changed to row " << row);

        // repaint old and new rows
        if (hoveredRow >= 0) playList.repaintRow(hoveredRow);
        hoveredRow = row;
        if (hoveredRow >= 0) playList.repaintRow(hoveredRow);
    }
}


void PlayerGUI::mouseExit(const juce::MouseEvent&)
{
    if (hoveredRow >= 0)
    {
        playList.repaintRow(hoveredRow);
        hoveredRow = -1;
    }
}

void PlayerGUI::ChangeTheme(int themeIndex)
{
    int numThemes = 3;

    if (themeIndex >= 0 && themeIndex < numThemes)
    {
        currentThemeIndex = themeIndex;
    }
    else
    {
        currentThemeIndex = (currentThemeIndex + 1) % numThemes;
    }

    switch (currentThemeIndex)
    {
    case 0:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::MakimaTheme1_png,
            BinaryData::MakimaTheme1_pngSize);
            customThemePath = "";
        break;

    case 1:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::NierAutomataTheme2_png,
            BinaryData::NierAutomataTheme2_pngSize);
            customThemePath = "";
        break;

    case 2:
        backgroundImage = juce::ImageFileFormat::loadFrom(
            BinaryData::DoctorXTheme3_png,
            BinaryData::DoctorXTheme3_pngSize);
            customThemePath = "";
        break;

    
    }

    repaint();
}


void PlayerGUI::LoadCustomTheme()
{
    themeFileChooser = std::make_unique<juce::FileChooser>(
        "Select a theme image...",
        juce::File{},
        "*.png;*.jpg;*.jpeg;*.bmp");

    themeFileChooser->launchAsync(
        juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
        [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file.existsAsFile())
            {
                // Try to load the image
                juce::Image loadedImage = juce::ImageFileFormat::loadFrom(file);

                if (loadedImage.isValid())
                {
                    backgroundImage = loadedImage;
                    customThemePath = file.getFullPathName();
                    currentThemeIndex = 3;  // Set to custom theme index

                    DBG("Custom theme loaded: " + file.getFileName());
                    repaint();
                }
                else
                {
                    DBG("Failed to load image file: " + file.getFileName());
                    
                }
            }
        });
}


void PlayerGUI::addmarker(double currentTime, int selectedRow )
{

    if (selectedRow < 0 || selectedRow >= files.size())
        return;

    // law fadya
    if (files.empty())
    {
        return;
    }

    auto& song = files[selectedRow];
    double songLen = std::max((double)song.time, 0.001);

    double markerTime = std::clamp(currentTime,0.0, songLen);

    const double eps = 0.05;//change this for closer lines.  bet5aly el lines gamb ba3d ka2enohom wa7ed.
    for (double existing : song.markersTime)
    {
        if (std::abs(existing - markerTime) < eps)
        {
            return;
        }
    }

    song.markersTime.push_back(markerTime);
    std::sort(song.markersTime.begin(), song.markersTime.end());


    progressSlider.repaint();
    playList.updateContent();
    playList.repaint();
    repaint();
}
void PlayerGUI::deleteMarker(double currTime, int lastRowSelected){

    if (lastRowSelected < 0 || lastRowSelected >= files.size())
        return;

        auto& markers = files[lastRowSelected].markersTime;
    if (markers.empty())
        return;

    auto it = std::min_element(markers.begin(), markers.end(),
        [&](double a, double b)
        {
            return std::abs(a - currTime) < std::abs(b - currTime);
        });

    if (it != markers.end())
    {
        markers.erase(it);
        std::sort(markers.begin(), markers.end());

        progressSlider.repaint();
        playList.updateContent();
        repaint();
    }
}


