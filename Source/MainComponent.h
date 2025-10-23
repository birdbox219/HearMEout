#pragma once

#include <JuceHeader.h>
#include <vector>


#include "PlayerAudio.h"
#include "PlayerGUI.h"

class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer,
    public juce::MouseListener
   
{
public:
    MainComponent();
    ~MainComponent() override;
    bool isStartWindow = true;
 
    // Audio
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // GUI
    void paint(juce::Graphics& g) override;
    void resized() override;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
 

    void timerCallback() override;


    // GUI MainWindow visuals 
    /*
    * Dont touch them ! All effects and visuals will be refactored to PlayerUIvisuls.cpp & PlayerUIvisuals.h -Mahmod
    * 
    */
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;


   
    void ShowButtons(juce::Button &button);
    void HideButtons(juce::Button &button);
    juce::TextButton startButton{ "Start" };

private:
    // Audio
	PlayerAudio player;

	// GUI
    PlayerGUI playerGUI;

 
    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::String formatTime(double seconds);
    double parseTimeString(const juce::String& timeStr);
    bool isDraggingSlider = false;

    juce::String authorName = "Unknown";

    
    
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};