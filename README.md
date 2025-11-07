# HearMeOut Audio Player

A sophisticated JUCE-based audio player and mixer application with advanced features including dual track playback, playlist management, A-B looping, and session persistence.

## Project Overview

This is a JUCE-based Audio Player and Mixer supporting multiple audio tracks, volume and panning controls, waveform visualization, and session saving. The application provides an intuitive audio playback and mixing experience with a modern GUI and expandable modular structure.

The HearMeOut Audio Player is built using the JUCE framework, a powerful cross-platform C++ toolkit for developing audio applications. The application features a clean, modern interface with dual-track playback capabilities, making it ideal for DJs, podcasters, and audio professionals who need to analyze and mix audio tracks.

## Key Features

- **Dual Track Support**: Play and manage two audio tracks simultaneously with individual controls
- **Playlist Management**: Add, remove, and manage audio files with metadata display
- **Playback Controls**: Play, pause, stop, skip forward/backward (10s), speed adjustment (0.1x-2.0x)
- **Volume & Pan Controls**: Individual volume sliders for each track with mute functionality
- **Loop Modes**: Support for normal, shuffle, and repeat playback modes
- **A-B Loop**: Set custom start/end points for looping specific sections
- **Markers**: Add and remove time markers on audio files for quick reference
- **Session Persistence**: Automatically saves and loads application state, including current tracks, positions, and playlists
- **Theming**: Multiple visual themes with custom image support
- **Keyboard Shortcuts**: Comprehensive keyboard navigation and control
- **File Format Support**: Compatible with common audio formats (WAV, MP3, etc.)
- **Metadata Reading**: Displays title, author, and duration information from audio files
- **Waveform Visualization**: Visual representation of markers on the timeline

## Build Instructions

### Prerequisites

- C++ compiler with C++17 support or higher
- CMake 3.15 or higher (if building with CMake)
- Git
- JUCE Framework (v6.0 or higher)

### Setting up the Development Environment

1. **Install Prerequisites**:
   - For Windows: Install Visual Studio 2019 or later with C++ tools
   - For macOS: Install Xcode and command line tools (`xcode-select --install`)
   - For Linux: Install build essentials (`sudo apt install build-essential`)

2. **Install CMake** (if not already installed):
   - Download from [cmake.org](https://cmake.org/download/) or use package manager

### Building with CMake

1. **Clone the repository:**
   ```bash
   git clone https://github.com/birdbox219/HearMEout
   cd HearMeOut
   ```

2. **Initialize JUCE submodule:**
   ```bash
   git submodule update --init --recursive
   ```

3. **Navigate to the Source directory (where the project files are located):**
   ```bash
   cd Source
   ```

4. **Create build directory:**
   ```bash
   mkdir build
   cd build
   ```

5. **Configure with CMake:**
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

6. **Build the project:**
   ```bash
   # On Windows:
   cmake --build . --config Release

   # On macOS/Linux:
   make -j$(nproc)
   ```

7. **Run the application:**
   ```bash
   # On Windows:
   ./Release/HearMeOut.exe

   # On macOS/Linux:
   ./HearMeOut
   ```

### Using Projucer (Alternative Method)

JUCE's Projucer is the recommended way to manage JUCE projects:

1. Download and install the Projucer from [juce.com](https://juce.com)
2. Open the `HearMeOut.jucer` file in the Projucer (you may need to create this file if it doesn't exist)
3. Configure your desired export settings (Visual Studio, Xcode, etc.)
4. Click "Save and Open in IDE" to generate and open the project
5. Build and run from your chosen IDE

## Usage Guide

### Getting Started

When you first launch HearMeOut, you'll see a start screen with options to begin using the audio player. Click the "Start" button to open the main interface.

### Loading Files

1. Click the "Load Files" button to open the file browser
2. Select an audio file (WAV, MP3, or other supported formats)
3. The file will load into the currently active track
4. Use the "Select" button to switch between files in your playlist
5. Add additional files to your playlist using the "+" button
6. Use the playlist to manage and organize your audio files
7. Double-click a file in the playlist to play it directly

### Adjust Volume and Pan

1. Use the vertical slider on the right side of each track to adjust volume (0.0 to 1.0)
2. Click the volume/mute icon to toggle muting for each track
3. In dual-track mode, each track has its own independent volume control
4. The speed slider allows you to adjust playback speed from 0.1x to 2.0x

### Mixing and Playback

1. Toggle between single and dual-track modes using the "1" and "2" keys or the interface buttons
2. Use transport controls (play, pause, stop) to control playback
3. Navigate the audio timeline using the progress bar or keyboard arrow keys
4. Skip forward/backward by 10 seconds using the arrow buttons or left/right arrow keys
5. Use the loop button to cycle between normal, shuffle, and repeat modes (indicated by different icons)
6. Set A-B loops to repeat specific sections of audio

### Advanced Features

#### Markers
- Add markers at current playback position using the "Add Marker" button
- Remove markers using the "Remove Marker" button
- Markers appear as red lines on the progress bar for visual reference

#### A-B Loop
- Enable A-B mode by clicking the "Set A-B Loop" button
- Set custom time points by typing in the start and end time labels
- Enable the loop by clicking the "Start A-B" button
- Disable with "Stop A-B" or by hiding A-B controls

#### Themes
- Change the application theme using the "Theme" button
- Select custom background images using the "Custom" button
- Multiple pre-defined themes are available

#### Session Management
- The application automatically saves your session when closed
- Session includes current tracks, playlist, volume settings, and markers
- Session is automatically restored when you reopen the application

### Keyboard Shortcuts

- **Space**: Play/Pause current track
- **Left Arrow**: Skip backward 10 seconds
- **Right Arrow**: Skip forward 10 seconds
- **Up Arrow**: Increase volume
- **Down Arrow**: Decrease volume
- **M**: Toggle mute
- **L**: Toggle loop mode
- **1**: Switch to single track mode
- **2**: Switch to dual track mode

## Architecture Overview

The application is structured into several key components:

- **MainComponent**: The primary UI component that manages the overall application state
- **PlayerAudio**: Handles all audio processing, transport, and mixing functionality
- **PlayerGUI**: Provides the visual interface for each track with playlist and controls
- **SessionManager**: Manages saving and loading of application state to XML

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Support

If you encounter any issues or have feature requests, please open an issue on the GitHub repository.

## Acknowledgments

- Built with the [JUCE Framework](https://juce.com)
- Inspired by modern audio player applications
- Created as part of an Object-Oriented Programming course project