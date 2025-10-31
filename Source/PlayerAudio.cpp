#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()

{
	formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    
	
}

PlayerAudio::~PlayerAudio()
{
    SaveSession();

    transportSource.removeChangeListener(this);
    transportSource.setSource(nullptr);
}

void PlayerAudio::setGain(float newGain)
{
    transportSource.setGain(newGain);
}

juce::String PlayerAudio::loadFile(const juce::File& file)
{
    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);



        juce::String authorName = "Unknown";
        auto metadata = reader->metadataValues;

        


        

        if (metadata.containsKey("IART"))
            authorName = metadata["IART"];
        else if (metadata.containsKey("Author"))
            authorName = metadata["Author"];
        else if (metadata.containsKey("ARTIST"))
            authorName = metadata["ARTIST"];
        
	







        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);

		currentFile = file;

        clearABPoints();

        return authorName;
    }

    return  "Unknown";
}








void PlayerAudio::Start()
{
	transportSource.start();
}

void PlayerAudio::Stop()
{
	transportSource.stop();
}
void PlayerAudio::goStart() {
    transportSource.setPosition(0.0);
}
void PlayerAudio::goEnd() {
  transportSource.setPosition(transportSource.getLengthInSeconds());
  
 }


void PlayerAudio::setLooping(bool shouldLoop)
{
    isLoopingEnabled = shouldLoop;

    if (readerSource)
    {
        readerSource->setLooping(shouldLoop);
    }
}

void PlayerAudio::setSpeed(double ratio)
{
    respeeder.setResamplingRatio(ratio);
}

// skip 10sec and rewind 10 sec:
void PlayerAudio::skipForward(double seconds)
{
    double newPos = transportSource.getCurrentPosition() + seconds;
    if (newPos < transportSource.getLengthInSeconds())
        transportSource.setPosition(newPos);
}
  
void PlayerAudio::skipBackward(double seconds)
{
    double newPos = transportSource.getCurrentPosition() - seconds;
    if (newPos < 0) newPos = 0;
    transportSource.setPosition(newPos);
}



void PlayerAudio::toggleMute()
{
    if (isMuted)
    {
        // Unmute: restore previous volume
        transportSource.setGain(lastGain);
        isMuted = false;
    }
    else
    {
        // Mute: save current volume and set to 0
        lastGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
}

//Get postion and total lenght of Audio 

float PlayerAudio::getPreviousGain() const
{
    return lastGain;
}

double PlayerAudio::getCurrentPosition() const
{
    return transportSource.getCurrentPosition();
}

double PlayerAudio::getTotalLength() const
{
    return transportSource.getLengthInSeconds();
}

void PlayerAudio::setPosition(double newPositon)
{
    transportSource.setPosition(newPositon);
}

//A-B logic

void PlayerAudio::setABLoop(bool enabled)
{
    abLoopEnabled = enabled;

    // If enabling A-B loop, disable regular loop
    if (enabled && isLoopingEnabled)
    {
        setLooping(false);
    }
}
void PlayerAudio::setABPoints(double startPos, double endPos)
{
    
    double totalLength = getTotalLength();

    abStartPosition = juce::jlimit(0.0, totalLength, startPos);
    abEndPosition = juce::jlimit(0.0, totalLength, endPos);

    
    if (abStartPosition >= abEndPosition)
    {
        abEndPosition = abStartPosition + 1.0; 
        if (abEndPosition > totalLength)
        {
            abEndPosition = totalLength;
            abStartPosition = totalLength - 1.0;
            if (abStartPosition < 0) abStartPosition = 0;
        }
    }
}

void PlayerAudio::clearABPoints()
{
    abStartPosition = 0.0;
    abEndPosition = getTotalLength();
    abLoopEnabled = false;
}


void PlayerAudio::checkABLoop()
{
    if (!abLoopEnabled || !transportSource.isPlaying())
        return;

    double currentPos = transportSource.getCurrentPosition();

    
    if (currentPos >= abEndPosition)
    {
        transportSource.setPosition(abStartPosition);
    }
}






// Playlist-related components
void PlayerAudio::addToList(juce::File& file) {
    bool exist{};
    if (!files.empty()) {
        for (auto f : files) {

            if (file.getFileNameWithoutExtension() == f.getFileNameWithoutExtension()) {
                exist = 1;
            }
        }
    }
    if (!exist) {
        files.push_back(file);
       
    }
}
juce::File PlayerAudio::getSessionFile()
{
    
    juce::File appDataDir = juce::File::getSpecialLocation(
        juce::File::userApplicationDataDirectory)
        .getChildFile("HearMeOut");

    
    if (!appDataDir.exists())
        appDataDir.createDirectory();

    return appDataDir.getChildFile("session.xml");
}



void PlayerAudio::SaveSession()
{
    if(!currentFile.existsAsFile())
		return;

    


	juce::XmlElement root("SESSION");

    root.setAttribute("filePath", currentFile.getFullPathName());

    root.setAttribute("position", getCurrentPosition());

    // Save volume
    root.setAttribute("volume", transportSource.getGain());

    // Save speed
    root.setAttribute("speed", respeeder.getResamplingRatio());

    // Save loop state
    root.setAttribute("looping", isLoopingEnabled);

    // Save mute state
    root.setAttribute("muted", isMuted);
    root.setAttribute("lastGain", lastGain);

    // Save A-B loop data
    root.setAttribute("abLoopEnabled", abLoopEnabled);
    root.setAttribute("abStartPosition", abStartPosition);
    root.setAttribute("abEndPosition", abEndPosition);

    //Save theme
	

    // Save playlist
    if (!files.empty())
    {
        auto* playlistElement = root.createNewChildElement("Playlist");
        for (const auto& file : files)
        {
            auto* fileElement = playlistElement->createNewChildElement("File");
            fileElement->setAttribute("path", file.getFullPathName());
        }
    }

    
    juce::File sessionFile = getSessionFile();

    if (!root.writeTo(sessionFile))
    {
        DBG("Failed to save session!");
    }
}

bool PlayerAudio::LoadLastSession()
{
    juce::File sessionFile = getSessionFile();

    if (!sessionFile.existsAsFile())
        return false;

    auto xml = juce::XmlDocument::parse(sessionFile);

    if (xml == nullptr)
        return false;

    
    juce::String filePath = xml->getStringAttribute("filePath");
    juce::File fileToLoad(filePath);

    if (!fileToLoad.existsAsFile())
    {
        DBG("Session file no longer exists: " + filePath);
        return false;
    }

    
    loadFile(fileToLoad);

    
    double position = xml->getDoubleAttribute("position", 0.0);
    setPosition(position);

    
    float volume = (float)xml->getDoubleAttribute("volume", 0.5);
    setGain(volume);

    
    double speed = xml->getDoubleAttribute("speed", 1.0);
    setSpeed(speed);

    
    bool looping = xml->getBoolAttribute("looping", false);
    setLooping(looping);

    
    isMuted = xml->getBoolAttribute("muted", false);
    lastGain = (float)xml->getDoubleAttribute("lastGain", 0.5);
    if (isMuted)
    {
        transportSource.setGain(0.0f);
    }

    
    abLoopEnabled = xml->getBoolAttribute("abLoopEnabled", false);
    abStartPosition = xml->getDoubleAttribute("abStartPosition", 0.0);
    abEndPosition = xml->getDoubleAttribute("abEndPosition", 0.0);

    // Restore playlist
    files.clear();
    if (auto* playlistElement = xml->getChildByName("Playlist"))
    {
        for (auto* fileElement : playlistElement->getChildIterator())
        {
            juce::String path = fileElement->getStringAttribute("path");
            juce::File file(path);
            if (file.existsAsFile())
            {
                files.push_back(file);
            }
        }
    }

    return true;
}


//----------------------------------------------------------------//
// i need to edit this later to fix speed bug ~amr.
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    respeeder.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	respeeder.getNextAudioBlock(bufferToFill);

    checkABLoop();
}

void PlayerAudio::releaseResources()
{
    respeeder.releaseResources();
	transportSource.releaseResources();
    
}















void PlayerAudio::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.hasStreamFinished() && isLoopingEnabled)
        {
            transportSource.setPosition(0.0);
            transportSource.start();
        }
    }
}


