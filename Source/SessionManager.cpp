#include "SessionManager.h"
#include "PlayerAudio.h"
#include "PlayerGUI.h"

juce::File SessionManager::getSessionFile()
{
    juce::File appDataDir = juce::File::getSpecialLocation(
        juce::File::userApplicationDataDirectory)
        .getChildFile("HearMeOut");

    if (!appDataDir.exists())
        appDataDir.createDirectory();

    return appDataDir.getChildFile("session.xml");
}

void SessionManager::saveSession(PlayerAudio& audio, PlayerGUI& gui)
{
    if (!audio.getCurrentFile().existsAsFile())
        return;

    juce::XmlElement root("SESSION");

    //  AUDIO STATE
    auto* audioElement = root.createNewChildElement("Audio");

    audioElement->setAttribute("filePath", audio.getCurrentFile().getFullPathName());
    audioElement->setAttribute("position", audio.getCurrentPosition());
    audioElement->setAttribute("volume", audio.getPreviousGain());
    audioElement->setAttribute("muted", audio.isMuted);
    audioElement->setAttribute("lastGain", audio.lastGain);
    audioElement->setAttribute("looping", audio.isLooping());

    // A-B loop state
    audioElement->setAttribute("abLoopEnabled", audio.isABLoopEnabled());
    audioElement->setAttribute("abStartPosition", audio.getABStart());
    audioElement->setAttribute("abEndPosition", audio.getABEnd());

    // GUI STATE 
    auto* guiElement = root.createNewChildElement("GUI");

    // Theme
    guiElement->setAttribute("currentTheme", gui.currentThemeIndex);
    if (gui.customThemePath.isNotEmpty())
    {
        guiElement->setAttribute("customThemePath", gui.customThemePath);
    }

    // Slider positions
    guiElement->setAttribute("volumeSlider", gui.volumeSlider.getValue());
    guiElement->setAttribute("speedSlider", gui.speedSlider.getValue());
    guiElement->setAttribute("progressSlider", gui.progressSlider.getValue());

    // Time labels
    guiElement->setAttribute("currentTime", gui.currentTimeLabel.getText());
    guiElement->setAttribute("totalTime", gui.TotalTimeLabel.getText());

    // Metadata labels
    guiElement->setAttribute("title", gui.title.getText());
    guiElement->setAttribute("time", gui.time.getText());
    guiElement->setAttribute("author", gui.author.getText());

    // A-B Loop GUI state
    guiElement->setAttribute("abLoopActive", gui.abLoopActive);
    guiElement->setAttribute("abControlsVisible", gui.abControlsVisible);
    guiElement->setAttribute("abStartLabel", gui.abStartLabel.getText());
    guiElement->setAttribute("abEndLabel", gui.abEndLabel.getText());

    // Button states
    guiElement->setAttribute("loopButtonActive", audio.isLooping());
    guiElement->setAttribute("startIconVisible", gui.startIcon.isVisible());
    guiElement->setAttribute("stopIconVisible", gui.stopButtonIcon.isVisible());

    //PLAYLIST STATE 
    if (!audio.files.empty())
    {
        auto* playlistElement = root.createNewChildElement("Playlist");

        for (const auto& file : audio.files)
        {
            auto* fileElement = playlistElement->createNewChildElement("File");
            fileElement->setAttribute("path", file.getFullPathName());

            // Find corresponding time in GUI files
            for (const auto& guiFile : gui.files)
            {
                if (guiFile.file.getFullPathName() == file.getFullPathName())
                {
                    fileElement->setAttribute("time", guiFile.time);
                    for (double mtime : guiFile.markersTime)
                    {
                        if (mtime >= 0.0)
                        {
                            auto* markerEl = fileElement->createNewChildElement("Marker");
                            markerEl->setAttribute("time", mtime);
                        }
                    }

                    break;
                }
            }
        }
    }

    // Save to file
    juce::File sessionFile = getSessionFile();
    if (!root.writeTo(sessionFile))
    {
        DBG("Failed to save session!");
    }
    else
    {
        DBG("Session saved successfully!");
    }
}

bool SessionManager::loadSession(PlayerAudio& audio, PlayerGUI& gui)
{
    juce::File sessionFile = getSessionFile();

    if (!sessionFile.existsAsFile())
        return false;

    auto xml = juce::XmlDocument::parse(sessionFile);
    if (xml == nullptr)
        return false;

    //  LOAD AUDIO 
    auto* audioElement = xml->getChildByName("Audio");
    if (audioElement == nullptr)
        return false;

    juce::String filePath = audioElement->getStringAttribute("filePath");
    juce::File fileToLoad(filePath);

    if (!fileToLoad.existsAsFile())
    {
        DBG("Session file no longer exists: " + filePath);
        return false;
    }

    // Load audio file
    audio.loadFile(fileToLoad);

    // Restore audio state
    double position = audioElement->getDoubleAttribute("position", 0.0);
    audio.setPosition(position);

    float volume = (float)audioElement->getDoubleAttribute("volume", 0.5);
    audio.setGain(volume);

    audio.isMuted = audioElement->getBoolAttribute("muted", false);
    audio.lastGain = (float)audioElement->getDoubleAttribute("lastGain", 0.5);

    bool looping = audioElement->getBoolAttribute("looping", false);
    audio.setLooping(looping);

    // A-B loop
    bool abLoopEnabled = audioElement->getBoolAttribute("abLoopEnabled", false);
    double abStart = audioElement->getDoubleAttribute("abStartPosition", 0.0);
    double abEnd = audioElement->getDoubleAttribute("abEndPosition", 0.0);

    if (abLoopEnabled)
    {
        audio.setABPoints(abStart, abEnd);
        audio.setABLoop(true);
    }

    //  LOAD GUI 
    auto* guiElement = xml->getChildByName("GUI");
    if (guiElement != nullptr)
    {
        // Theme
        gui.currentThemeIndex = guiElement->getIntAttribute("currentTheme", 0);
        //gui.ChangeTheme(gui.currentThemeIndex);
        juce::String customPath = guiElement->getStringAttribute("customThemePath", "");
        if (customPath.isNotEmpty())
        {
            juce::File customThemeFile(customPath);
            if (customThemeFile.existsAsFile())
            {
                juce::Image customImage = juce::ImageFileFormat::loadFrom(customThemeFile);
                if (customImage.isValid())
                {
                    gui.backgroundImage = customImage;
                    gui.customThemePath = customPath;
                    DBG("Custom theme restored from: " + customPath);
                }
                else
                {
                    
                    DBG("Custom theme file exists but couldn't be loaded, using default theme");
                    gui.ChangeTheme(0);
                }
            }
            else
            {
                
                DBG("Custom theme file no longer exists, using default theme");
                gui.ChangeTheme(0);
            }
        }
        else
        {
            // No custom theme, load built-in theme
            gui.ChangeTheme(gui.currentThemeIndex);
        }

        // sliders
        gui.volumeSlider.setValue(guiElement->getDoubleAttribute("volumeSlider", 0.5),
            juce::dontSendNotification);
        gui.speedSlider.setValue(guiElement->getDoubleAttribute("speedSlider", 1.0),
            juce::dontSendNotification);
        gui.progressSlider.setValue(guiElement->getDoubleAttribute("progressSlider", 0.0),
            juce::dontSendNotification);

        // labels
        gui.currentTimeLabel.setText(guiElement->getStringAttribute("currentTime", "0:00"),
            juce::dontSendNotification);
        gui.TotalTimeLabel.setText(guiElement->getStringAttribute("totalTime", "0:00"),
            juce::dontSendNotification);
        gui.title.setText(guiElement->getStringAttribute("title", ""),
            juce::dontSendNotification);
        gui.time.setText(guiElement->getStringAttribute("time", ""),
            juce::dontSendNotification);
        gui.author.setText(guiElement->getStringAttribute("author", ""),
            juce::dontSendNotification);

        // A-B Loop 
        gui.abLoopActive = guiElement->getBoolAttribute("abLoopActive", false);
        gui.abControlsVisible = guiElement->getBoolAttribute("abControlsVisible", false);

        gui.abStartLabel.setText(guiElement->getStringAttribute("abStartLabel", "0:00"),
            juce::dontSendNotification);
        gui.abEndLabel.setText(guiElement->getStringAttribute("abEndLabel", "0:00"),
            juce::dontSendNotification);

        // Show&hide A-B 
        gui.abStartTimeLabel.setVisible(gui.abControlsVisible);
        gui.abEndTimeLabel.setVisible(gui.abControlsVisible);
        gui.abStartLabel.setVisible(gui.abControlsVisible);
        gui.abEndLabel.setVisible(gui.abControlsVisible);
        gui.abStartButton.setVisible(gui.abControlsVisible);

        if (gui.abLoopActive)
        {
            gui.abLoopButton.setButtonText("Hide A-B");
            gui.abStartButton.setButtonText("Stop A-B");
            gui.abStartButton.setColour(juce::TextButton::buttonColourId, juce::Colours::cyan);
        }

		// Button start and Stop state
        gui.startIcon.setVisible(guiElement->getBoolAttribute("startIconVisible", true));
        gui.stopButtonIcon.setVisible(guiElement->getBoolAttribute("stopIconVisible", false));

        // Loop button color
        if (audio.isLooping())
        {
            gui.loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::orangered);
        }

        // Mute button icon
        if (audio.isMuted)
        {
            gui.muteButton.setImages(false, true, true,
                gui.unmuteimage, 1.0f, juce::Colours::transparentWhite,
                gui.unmuteimage, 1.0f, juce::Colours::transparentWhite,
                gui.unmuteimage, 1.0f, juce::Colours::transparentWhite);
        }
    }

    //  LOAD PLAYLIST 
    audio.files.clear();
    gui.files.clear();

    if (auto* playlistElement = xml->getChildByName("Playlist"))
{
    for (auto* fileElement : playlistElement->getChildIterator())
    {
        juce::String path = fileElement->getStringAttribute("path");
        juce::File file(path);

        if (!file.existsAsFile())
            continue;

        audio.files.push_back(file);

        // Add to GUI playlist with time
        PlayerGUI::fileInfo info;
        info.file = file;
        info.time = fileElement->getDoubleAttribute("time", 0);

        // i hate my life wallahy so confusing. this is for loading markers.
        for (auto* markerEl = fileElement->getFirstChildElement();
            markerEl != nullptr;
            markerEl = markerEl->getNextElement())
        {
            if (markerEl->hasTagName("Marker"))
            {
                double mtime = markerEl->getDoubleAttribute("time", -1.0);
                if (mtime >= 0.0)
                    info.markersTime.push_back(mtime);
            }
        }

        std::sort(info.markersTime.begin(), info.markersTime.end());
        gui.files.push_back(info);
    }

    gui.playList.updateContent();
    gui.playList.repaint();
}


    DBG("Session loaded successfully!");
    return true;
}