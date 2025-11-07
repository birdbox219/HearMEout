#pragma once
#include <JuceHeader.h>

// Forward declarations
class PlayerAudio;
class PlayerGUI;

class SessionManager
{
public:
    SessionManager() = default;
    ~SessionManager() = default;

    // Save 
    void saveSession(PlayerAudio& audio, PlayerGUI& gui);

    // Load 
    bool loadSession(PlayerAudio& audio, PlayerGUI& gui);

    // Get session file location
    juce::File getSessionFile();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SessionManager)
};
