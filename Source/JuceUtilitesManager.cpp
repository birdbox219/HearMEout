#include "JuceUtilitesManager.h"

AudioMetadata MetadataExtractor::extractMetadata(const juce::File& file)
{
    if (!file.existsAsFile())
        return AudioMetadata();

    juce::String extension = getFileExtension(file).toLowerCase();

    
    if (extension == "mp3")
        return extractFromMP3(file);
    else if (extension == "wav")
        return extractFromWAV(file);
    

    // Fallback: try JUCE's built-in reader
    return extractFromWAV(file);
}


AudioMetadata MetadataExtractor::extractFromWAV(const juce::File& file)
{
    AudioMetadata metadata;

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    if (reader != nullptr)
    {
        auto meta = reader->metadataValues;

        // Try various WAV metadata keys
        if (meta.containsKey("IART"))
            metadata.artist = meta["IART"];
        else if (meta.containsKey("Artist"))
            metadata.artist = meta["Artist"];
        else if (meta.containsKey("ARTIST"))
            metadata.artist = meta["ARTIST"];

        if (meta.containsKey("INAM"))
            metadata.title = meta["INAM"];
        else if (meta.containsKey("Title"))
            metadata.title = meta["Title"];

        if (meta.containsKey("IPRD"))
            metadata.album = meta["IPRD"];
        else if (meta.containsKey("Album"))
            metadata.album = meta["Album"];

        if (meta.containsKey("ICRD"))
            metadata.year = meta["ICRD"];
        else if (meta.containsKey("Year"))
            metadata.year = meta["Year"];

        if (meta.containsKey("IGNR"))
            metadata.genre = meta["IGNR"];
        else if (meta.containsKey("Genre"))
            metadata.genre = meta["Genre"];

        metadata.duration = reader->lengthInSamples / reader->sampleRate;

        // If no title found, use filename
        if (metadata.title == "Unknown")
            metadata.title = file.getFileNameWithoutExtension();
    }

    return metadata;
}



AudioMetadata MetadataExtractor::extractFromMP3(const juce::File& file)
{
    AudioMetadata metadata;

    juce::FileInputStream stream(file);
    if (!stream.openedOk())
        return metadata;

    // Try ID3v2 first (at beginning of file)
    metadata = parseID3v2(stream);

    // If ID3v2 failed, try ID3v1 (last 128 bytes of file)
    if (!metadata.isValid())
    {
        metadata = parseID3v1(stream);
    }

    // If still no title, use filename
    if (metadata.title == "Unknown")
        metadata.title = file.getFileNameWithoutExtension();

    // Get duration using JUCE
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    if (reader != nullptr)
    {
        metadata.duration = reader->lengthInSamples / reader->sampleRate;
    }

    return metadata;
}

AudioMetadata MetadataExtractor::parseID3v2(juce::FileInputStream& stream)
{
    AudioMetadata metadata;

    stream.setPosition(0);

    // Check for ID3v2 header
    char header[10];
    if (stream.read(header, 10) != 10)
        return metadata;

    // Verify ID3v2 signature
    if (header[0] != 'I' || header[1] != 'D' || header[2] != '3')
        return metadata;

    int version = header[3];
    int flags = header[5];

    // Calculate tag size (synchsafe integer)
    int tagSize = ((header[6] & 0x7F) << 21) |
        ((header[7] & 0x7F) << 14) |
        ((header[8] & 0x7F) << 7) |
        (header[9] & 0x7F);

    if (tagSize <= 0 || tagSize > 10000000) // Sanity check
        return metadata;

    // Read the entire tag data
    juce::MemoryBlock tagData;
    tagData.setSize(tagSize);
    stream.read(tagData.getData(), tagSize);

    // Parse frames
    int pos = 0;
    while (pos + 10 < tagSize)
    {
        // Read frame header
        char frameID[5] = { 0 };
        memcpy(frameID, (char*)tagData.getData() + pos, 4);

        if (frameID[0] == 0) // Padding reached
            break;

        // Frame size (4 bytes after frame ID)
        int frameSize = 0;
        if (version == 4) // ID3v2.4 uses synchsafe integers
        {
            unsigned char* sizeBytes = (unsigned char*)tagData.getData() + pos + 4;
            frameSize = ((sizeBytes[0] & 0x7F) << 21) |
                ((sizeBytes[1] & 0x7F) << 14) |
                ((sizeBytes[2] & 0x7F) << 7) |
                (sizeBytes[3] & 0x7F);
        }
        else // ID3v2.3 uses regular integers
        {
            unsigned char* sizeBytes = (unsigned char*)tagData.getData() + pos + 4;
            frameSize = (sizeBytes[0] << 24) |
                (sizeBytes[1] << 16) |
                (sizeBytes[2] << 8) |
                sizeBytes[3];
        }

        if (frameSize <= 0 || frameSize > tagSize - pos - 10)
            break;

        int frameDataPos = pos + 10; // Skip frame header (4 + 4 + 2 bytes)

        // Extract frame content (skip encoding byte)
        juce::String content = readID3String(tagData, frameDataPos + 1, frameSize - 1);

        // Map frame ID to metadata field
        juce::String frame(frameID);
        if (frame == "TIT2") metadata.title = content;
        else if (frame == "TPE1") metadata.artist = content;
        else if (frame == "TALB") metadata.album = content;
        else if (frame == "TYER" || frame == "TDRC") metadata.year = content;
        else if (frame == "TCON") metadata.genre = content;
        else if (frame == "COMM") metadata.comment = content;
        else if (frame == "TRCK") metadata.trackNumber = content.getIntValue();

        pos += 10 + frameSize;
    }

    return metadata;
}

AudioMetadata MetadataExtractor::parseID3v1(juce::FileInputStream& stream)
{
    AudioMetadata metadata;

    // ID3v1 is in last 128 bytes
    juce::int64 fileSize = stream.getTotalLength();
    if (fileSize < 128)
        return metadata;

    stream.setPosition(fileSize - 128);

    char tag[128];
    if (stream.read(tag, 128) != 128)
        return metadata;

    // Check for TAG signature
    if (tag[0] != 'T' || tag[1] != 'A' || tag[2] != 'G')
        return metadata;

    // Extract fields (fixed positions in ID3v1)
    metadata.title = cleanString(juce::String::fromUTF8(tag + 3, 30));
    metadata.artist = cleanString(juce::String::fromUTF8(tag + 33, 30));
    metadata.album = cleanString(juce::String::fromUTF8(tag + 63, 30));
    metadata.year = cleanString(juce::String::fromUTF8(tag + 93, 4));
    metadata.comment = cleanString(juce::String::fromUTF8(tag + 97, 28));

    // Track number (ID3v1.1 extension)
    if (tag[125] == 0 && tag[126] != 0)
        metadata.trackNumber = (unsigned char)tag[126];

    // Genre
    unsigned char genreCode = (unsigned char)tag[127];
    if (genreCode < 148) // Valid genre codes
        metadata.genre = juce::String(genreCode);

    return metadata;
}



juce::String MetadataExtractor::readID3String(juce::MemoryBlock& data, int offset, int length)
{
    if (offset + length > (int)data.getSize())
        return "";

    // Get encoding (first byte of frame data was skipped by caller)
    const char* strData = (const char*)data.getData() + offset;

    // Try UTF-8 first, fallback to Latin-1
    juce::String result = juce::String::fromUTF8(strData, length);

    return cleanString(result);
}

juce::String MetadataExtractor::cleanString(const juce::String& str)
{
    // Remove null terminators and trim
    return str.upToFirstOccurrenceOf(juce::String::charToString('\0'), false, false).trim();
}

juce::String MetadataExtractor::getFileExtension(const juce::File& file)
{
    return file.getFileExtension().substring(1); // Remove leading dot
}



