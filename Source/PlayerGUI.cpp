#include "PlayerGUI.h"
#include "BinaryData.h"


PlayerGUI::PlayerGUI()
{
    



    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(goStartButton);
    addAndMakeVisible(goEndButton);
    addAndMakeVisible(title);
    addAndMakeVisible(time);
    addAndMakeVisible(author);
    addAndMakeVisible(startIcon);
    addAndMakeVisible(stopButtonIcon);
    
 
    addAndMakeVisible(loopButton);
    

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
    speedSlider.setTextValueSuffix("x");
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);


   
  
 
    
    
    
    //Icon Manager
    

     
    stopImageIcon = juce::ImageFileFormat::loadFrom(BinaryData::pauseyellow_png, BinaryData::pauseyellow_pngSize);
    /*stopImageIcon = juce::ImageFileFormat::loadFrom(juce::File("D:/FCAI_SecondLevel/OOP/A_2/HearMEouT/HearMEout/Assetes/paused.png"));*/
    //i have an error here i don't have  BinaryData...? but i didn't touch the logic just uncomment it.
    // stopImageIcon = juce::ImageCache::getFromMemory(
    //     BinaryData::pasueBlue_png, 
    //     BinaryData::pasueBlue_pngSize
    // );
    


    goEnd = juce::ImageFileFormat::loadFrom(BinaryData::goEnd_png, BinaryData::goEnd_pngSize);
    goStart = juce::ImageFileFormat::loadFrom(BinaryData::goStart_png, BinaryData::goStart_pngSize);
    remove = juce::ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize);
    


    
   

    
    
    //------------------------------------------//


    




    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::orangered);
    volumeSlider.setColour(juce::Slider::trackColourId, juce::Colours::yellow);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::yellow);




    //volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    //Progress Slider
    progressSlider.setRange(0.0, 1.0, 0.001);
    progressSlider.setValue(0.0);
    progressSlider.setSliderStyle(juce::Slider::LinearHorizontal);  
    progressSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);



    addAndMakeVisible(progressSlider);

    //Progress Lebel
    currentTimeLabel.setText("0:00", juce::dontSendNotification);
    //currentTimeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(currentTimeLabel);

    TotalTimeLabel.setText("0:00", juce::dontSendNotification);
    addAndMakeVisible(TotalTimeLabel);











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
    
     // Side buttons
    goStartButton.setBounds(200, 500, 100, 40);
    goEndButton.setBounds(660, 500, 100, 40);

    // Central control icons
    startIcon.setBounds(450, 500, 60, 60);
    stopButtonIcon.setBounds(450, 500, 60, 60);

    // New skip buttons
    skipBackButton.setBounds(370, 510, 60, 40);
    skipForwardButton.setBounds(530, 510, 60, 40);

    title.setBounds(600, 90, 100, 40);
    time.setBounds(600, 110, 100, 40);
    author.setBounds(600, 130, 100, 40);
    

    loopButton.setBounds(800, 500, 80, 40);

    //mute button
    muteButton.setBounds(50, 500, 100, 40);
    //speed slider
    speedSlider.setBounds(20, progressSlider.getY() - 30, getWidth() - 40, 20);//audio speed length and width.



    

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

    volumeSlider.setBounds(800, 100, 30 , getHeight() - 300 );

    int progressY = 420;
    progressSlider.setBounds(90, progressY, getWidth() - 180, 80);







    //Lebels Bounds
    currentTimeLabel.setBounds(20, progressY, 60, 80);
    TotalTimeLabel.setBounds(getWidth() - 80, progressY, 60, 80);

    // Playlist-related components
    addToListButton.setBounds(200, 10, 40, 40);
    addToListButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkblue);
    resetButton.setBounds(250, 10, 60, 40);
    resetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumvioletred);
    playList.setBounds(200, 60, 300, 300);
    playList.setColour(juce::ListBox::backgroundColourId, juce::Colours::mediumpurple);  
    playList.setColour(juce::ListBox::textColourId, juce::Colours::white);    
    selectButton.setBounds(600, 60, 60, 40);
    removeButton.setBounds(660, 60, 60, 40);
   selectButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);

 


  


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

        g.fillAll(rowIsSelected ? juce::Colours::blue.withAlpha(0.3f) : juce::Colours::transparentBlack);

        g.setColour(juce::Colours::white);
        g.drawText(files[rowNumber].file.getFileNameWithoutExtension(),
            5, 0, width - 10, height,
            juce::Justification::centredLeft, true);
        int h = 0;
        int m = 0;
        int s = 0;
        m = files[rowNumber].time / 60;
        s = files[rowNumber].time % 60;

        g.drawText(juce::String(h) + ":" + juce::String(m) + ":" + juce::String(s),190, 0, width - 10, height,
            juce::Justification::centredLeft, true);
        
    }
}
 

void PlayerGUI::selectedRowsChanged(int lastRowSelected)
{
    if (lastRowSelected >= 0)
    {
        auto file = files[lastRowSelected];
       
        sendFile = file.file;

    }                                                                                                                                                                    
}





