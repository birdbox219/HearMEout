# HearMeOut Refactoring Plan

This document outlines a plan to refactor the HearMeOut audio player to improve its architecture, maintainability, and extensibility.

## 1. Code Review Summary

### The Good

*   **JUCE Framework:** Excellent choice for audio application development.
*   **Separation of Concerns (Initial):** A good start on separating audio, GUI, and application logic.
*   **Feature Set:** A solid set of basic features for an audio player.
*   **Session Management:** A user-friendly feature that improves the user experience.

### Areas for Improvement

*   **Massive `MainComponent`:** The `MainComponent` class has become a "god object," handling too many responsibilities.
*   **Tight Coupling:** `MainComponent` is too tightly coupled with `PlayerAudio` and `PlayerGUI`.
*   **UI Logic in `MainComponent`:** UI-related logic should be encapsulated within `PlayerGUI`.
*   **Empty Files:** `MainWindowUI.cpp` and `MainWindowUI.h` are unused and should be removed.
*   **Inconsistent Naming and Style:** The codebase would benefit from a consistent coding style.
*   **Magic Numbers:** Hardcoded values should be replaced with named constants.

## 2. Refactoring Goals

*   **Decouple Components:** Reduce the dependencies between `MainComponent`, `PlayerAudio`, and `PlayerGUI`.
*   **Improve Maintainability:** Make the code easier to understand, modify, and debug.
*   **Improve Extensibility:** Make it easier to add new features in the future.

## 3. Refactoring Steps

### Step 1: Decouple `MainComponent`

*   **Introduce a Command Pattern:**
    *   Create a `Command` base class with an `execute()` method.
    *   Create concrete command classes for each user action (e.g., `PlayCommand`, `StopCommand`, `LoadFileCommand`).
    *   `PlayerGUI` will create and trigger these commands in response to button clicks.
    *   `MainComponent` will be responsible for executing the commands, which will then call the appropriate methods on `PlayerAudio`.
*   **Use `juce::ValueTree` for State Management:**
    *   Create a `juce::ValueTree` to represent the application's state (e.g., current track, volume, loop status).
    *   `PlayerGUI` will observe this `ValueTree` and update itself automatically when the state changes.
    *   `MainComponent` will be responsible for updating the `ValueTree` in response to user actions.

### Step 2: Slim Down `MainComponent`

*   **Move UI Logic to `PlayerGUI`:**
    *   All code that manipulates the UI (e.g., showing/hiding buttons, setting colors, updating labels) should be moved into `PlayerGUI`.
    *   `PlayerGUI` should expose high-level methods like `showPlaybackState(bool isPlaying)` instead of having `MainComponent` directly control its child components.
*   **Create a `FileManager` Class:**
    *   Create a `FileManager` class that is responsible for all file-related operations (e.g., showing the file chooser, loading files, saving/loading sessions).

### Step 3: Improve `PlayerGUI`

*   **Encapsulate UI Components:**
    *   Make all UI components in `PlayerGUI` private.
    *   Provide public methods to interact with them.
*   **Use a Delegate or Callback:**
    *   `PlayerGUI` can be the listener for its own buttons.
    *   Use a delegate or a callback to notify `MainComponent` of user actions.

### Step 4: Implement New Features

Once the refactoring is complete, the codebase will be in a much better state to add the new features.

*   **Window Switching (Player/Playlist):**
    *   Create two new `juce::Component` classes: `PlayerView` and `PlaylistView`.
    *   `PlayerView` will contain the `PlayerGUI`.
    *   `PlaylistView` will contain a more advanced playlist component.
    *   In `MainComponent`, use a `juce::TabbedComponent` or a custom component to switch between these two views.
*   **Audio Mixer Window:**
    *   Create a new `AudioMixerWindow` component.
    *   This will require significant changes to `PlayerAudio`. You'll need to have two `juce::AudioTransportSource` instances, one for each track.
    *   The `AudioMixerWindow` will have controls to adjust the volume and other properties of each track.
    *   The `getNextAudioBlock` method in `PlayerAudio` will need to be updated to mix the audio from the two transport sources.

## 4. Documentation and Testing

*   **Documentation:** Add Doxygen-style comments to all classes and methods to explain their purpose.
*   **Unit Tests:** Create unit tests for the `PlayerAudio` and `FileManager` classes to ensure they are working correctly.

By following this plan, we can create a more robust, maintainable, and extensible audio player that is ready for future development.
