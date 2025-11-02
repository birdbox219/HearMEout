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

    // Save complete application state
    void saveSession(PlayerAudio& audio, PlayerGUI& gui);

    // Load complete application state
    bool loadSession(PlayerAudio& audio, PlayerGUI& gui);

    // Get session file location
    juce::File getSessionFile();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SessionManager)
};
