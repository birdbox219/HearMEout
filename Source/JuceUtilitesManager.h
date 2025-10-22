
#pragma once
#include <JuceHeader.h>

/**
 * @brief Metadata extraction for various audio formats
 *
 * Supports:

 * - MP3 (ID3v1 and ID3v2 tags)

 *

 */

struct AudioMetadata
{
    juce::String title = "Unknown";
    juce::String artist = "Unknown";
    juce::String album = "Unknown";
    juce::String year = "";
    juce::String genre = "";
    juce::String comment = "";
    int trackNumber = 0;
    double duration = 0.0;


    bool isValid() const { return artist != "Unknown" || title != "Unknown"; }
};


class MetadataExtractor
{
public:
    MetadataExtractor() = default;
    ~MetadataExtractor() = default;

    /**
     * @brief Extract metadata from audio file
     * @param file The audio file to extract metadata from
     * @return AudioMetadata structure with extracted information
     */
    static AudioMetadata extractMetadata(const juce::File& file);

private:
    // Format-specific extractors
    static AudioMetadata extractFromWAV(const juce::File& file);
    static AudioMetadata extractFromMP3(const juce::File& file);
    

    // Helper functions
    static juce::String cleanString(const juce::String& str);
    static juce::String getFileExtension(const juce::File& file);

    // ID3v2 parsing helpers
    static AudioMetadata parseID3v2(juce::FileInputStream& stream);
    static AudioMetadata parseID3v1(juce::FileInputStream& stream);
    static juce::String readID3String(juce::MemoryBlock& data, int offset, int length);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MetadataExtractor)
};