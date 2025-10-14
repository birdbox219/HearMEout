cmake_minimum_required(VERSION 3.15)
project(HearMEout VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to your local JUCE clone
set(JUCE_DIR "D:/programming/MSYS2_SETUP/home/amrat/JUCE")

# Make sure JUCE exists
if(NOT EXISTS ${JUCE_DIR}/CMakeLists.txt)
    message(FATAL_ERROR "JUCE_DIR not found at ${JUCE_DIR}")
endif()

# Add JUCE
add_subdirectory(${JUCE_DIR} JUCE-build)

# Automatically collect all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_SOURCE_DIR}/Source/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

# Define the app
juce_add_gui_app(HearMEout PRODUCT_NAME "HearMEout")

# Link JUCE modules first (so JUCE CMake target machinery can set up includes, compile definitions, etc.)
target_link_libraries(HearMEout PRIVATE
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_utils
    juce::juce_audio_processors
)

# Generate JuceHeader.h for this target (this makes <JuceHeader.h> available)
juce_generate_juce_header(HearMEout)

# Then add source files to the target
target_sources(HearMEout PRIVATE ${PROJECT_SOURCES})
# Make sure the compiler can find JuceHeader.h
target_include_directories(HearMEout PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode
    ${CMAKE_CURRENT_BINARY_DIR}/HearMEout_artefacts/JuceLibraryCode
    ${JUCE_DIR}/modules
)
