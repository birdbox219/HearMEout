#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()

{
	formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
	transportSource2.addChangeListener(this);

    respeeder.setResamplingRatio(1.0);
    respeeder2.setResamplingRatio(1.0);
 
    mixer.addInputSource(&respeeder, false);
    mixer.addInputSource(&respeeder2, false);

    //setAudioChannels(0, 2); // no inputs, 2 outputs



    
	
}

PlayerAudio::~PlayerAudio()
{


    transportSource.removeChangeListener(this);
    transportSource.setSource(nullptr);
    transportSource2.removeChangeListener(this);
    transportSource2.setSource(nullptr);

    mixer.removeAllInputs();
}



void PlayerAudio::setTrackActive(int trackNumber, bool active)
{
    if (trackNumber == 1)
    {
        if (!active)
        {
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset(nullptr);
        }
    }
    else if (trackNumber == 2)
    {
        if (!active)
        {
            transportSource2.stop();
            transportSource2.setSource(nullptr);
            readerSource2.reset(nullptr);
        }
    }
}



void PlayerAudio::setGain(float newGain)
{
    transportSource.setGain(newGain);
    
}
void PlayerAudio::setGain2(float newGain)
{
 
    transportSource2.setGain(newGain);
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
        respeeder.setResamplingRatio(1.0);

        clearABPoints();

        return authorName;
    }

    return  "Unknown";
}

juce::String PlayerAudio::loadFile2(const juce::File& file)
{
    if (auto* reader2 = formatManager.createReaderFor(file))
    {
        transportSource2.stop();
        transportSource2.setSource(nullptr);



        juce::String authorName = "Unknown";
        auto metadata = reader2->metadataValues;

        DBG("=== Metadata for file: " + file.getFileName() + " ===");
        for (int i = 0; i < metadata.size(); ++i)
        {
            DBG("Key: " + metadata.getAllKeys()[i] + " = " + metadata.getAllValues()[i]);
        }
        DBG("=== End of metadata ===");




        if (metadata.containsKey("IART"))
            authorName = metadata["IART"];
        else if (metadata.containsKey("Author"))
            authorName = metadata["Author"];
        else if (metadata.containsKey("ARTIST"))
            authorName = metadata["ARTIST"];








        
        readerSource2.reset(new juce::AudioFormatReaderSource(reader2, true));
        transportSource2.setSource(readerSource2.get(), 0, nullptr, reader2->sampleRate);
        respeeder2.setResamplingRatio(1.0);
        clearABPoints();
        

        return authorName;
    }

    return  "Unknown";
}







void PlayerAudio::Start()
{
	transportSource.start();
   
}
void PlayerAudio::Start2()
{
    
    transportSource2.start();
}

void PlayerAudio::Stop()
{
	transportSource.stop();
   
}
void PlayerAudio::Stop2()
{
    transportSource2.stop();

}

void PlayerAudio::goStart() {
    transportSource.setPosition(0.0);
   
}
void PlayerAudio::goStart2() {
    transportSource2.setPosition(0.0);

}

void PlayerAudio::goEnd() {
  transportSource.setPosition(transportSource.getLengthInSeconds());

  
 }
void PlayerAudio::goEnd2() {
    transportSource2.setPosition(transportSource2.getLengthInSeconds());


}

void PlayerAudio::setLooping(bool shouldLoop)
{
    isLoopingEnabled = shouldLoop;

    if (readerSource)
    {
        readerSource->setLooping(shouldLoop);
    }
}
void PlayerAudio::setLooping2(bool shouldLoop)
{
    isLoopingEnabled2 = shouldLoop;

    if (readerSource2)
    {
        readerSource2->setLooping(shouldLoop);
    }
}






void PlayerAudio::setSpeed(double ratio)
{
    respeeder.setResamplingRatio(ratio);
}
void PlayerAudio::setSpeed2(double ratio)
{
    respeeder2.setResamplingRatio(ratio);
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

void PlayerAudio::skipForward2(double seconds)
{
    double newPos = transportSource2.getCurrentPosition() + seconds;
    if (newPos < transportSource2.getLengthInSeconds())
        transportSource2.setPosition(newPos);
}
void PlayerAudio::skipBackward2(double seconds)
{
    double newPos = transportSource2.getCurrentPosition() - seconds;
    if (newPos < 0) newPos = 0;
    transportSource2.setPosition(newPos);
}

void PlayerAudio::toggleMute()
{
    if (isMuted)
    {
        
        transportSource.setGain(lastGain);
        isMuted = false;
    }
    else
    {
        
        lastGain = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
}
void PlayerAudio::toggleMute2()
{
    if (isMuted2)
    {
        // Unmute: restore previous volume
        transportSource2.setGain(lastGain2);
        isMuted2 = false;
    }
    else
    {
        // Mute: save current volume and set to 0
        lastGain2 = transportSource2.getGain();
        transportSource2.setGain(0.0f);
        isMuted2 = true;
    }
}

//Get postion and total lenght of Audio 

float PlayerAudio::getPreviousGain() const
{
    return lastGain;
}
float PlayerAudio::getPreviousGain2() const
{
    return lastGain2;
}

double PlayerAudio::getCurrentPosition() const
{
    return transportSource.getCurrentPosition();
}
double PlayerAudio::getCurrentPosition2() const
{
    return transportSource2.getCurrentPosition();
}

double PlayerAudio::getTotalLength() const
{
    return transportSource.getLengthInSeconds();
}
double PlayerAudio::getTotalLength2() const
{
    return transportSource2.getLengthInSeconds();
}

void PlayerAudio::setPosition(double newPositon)
{
    transportSource.setPosition(newPositon);
}
void PlayerAudio::setPosition2(double newPositon)
{
    transportSource2.setPosition(newPositon);
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
void PlayerAudio::setABLoop2(bool enabled)
{
    abLoopEnabled2 = enabled;

    // If enabling A-B loop, disable regular loop
    if (enabled && isLoopingEnabled2)
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
void PlayerAudio::setABPoints2(double startPos, double endPos)
{

    double totalLength = getTotalLength2();

    abStartPosition2 = juce::jlimit(0.0, totalLength, startPos);
    abEndPosition2 = juce::jlimit(0.0, totalLength, endPos);


    if (abStartPosition2 >= abEndPosition2)
    {
        abEndPosition2 = abStartPosition2 + 1.0;
        if (abEndPosition2 > totalLength)
        {
            abEndPosition2 = totalLength;
            abStartPosition2 = totalLength - 1.0;
            if (abStartPosition2 < 0) abStartPosition2 = 0;
        }
    }
}
void PlayerAudio::clearABPoints()
{
    abStartPosition = 0.0;
    abEndPosition = getTotalLength();
    abLoopEnabled = false;
}
void PlayerAudio::clearABPoints2()
{
    abStartPosition2 = 0.0;
    abEndPosition2 = getTotalLength2();
    abLoopEnabled2 = false;
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
void PlayerAudio::checkABLoop2()
{
    if (!abLoopEnabled2 || !transportSource2.isPlaying())
        return;

    double currentPos = transportSource2.getCurrentPosition();

    // If we've passed the B point, jump back to A
    if (currentPos >= abEndPosition2)
    {
        transportSource2.setPosition(abStartPosition2);
    }
}






// Playlist-related components
void PlayerAudio::addToList(juce::File& file)
{
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



//----------------------------------------------------------------//
// i need to edit this later to fix speed bug ~amr.
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    transportSource2.prepareToPlay(samplesPerBlockExpected, sampleRate);
   
    respeeder.prepareToPlay(samplesPerBlockExpected, sampleRate);
    respeeder2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bool track1Active = (readerSource != nullptr && transportSource.getTotalLength() > 0);
    bool track2Active = (readerSource2 != nullptr && transportSource2.getTotalLength() > 0);

    if (track1Active && track2Active)
    {
        // Both tracks loaded - use mixer
        mixer.getNextAudioBlock(bufferToFill);
        checkABLoop();
        checkABLoop2();
    }
    else if (track1Active && !track2Active)
    {
        // Only track 1 - bypass mixer completely
        respeeder.getNextAudioBlock(bufferToFill);
        checkABLoop();
    }
    else if (track2Active && !track1Active)
    {
        // Only track 2 - bypass mixer completely
        respeeder2.getNextAudioBlock(bufferToFill);
        checkABLoop2();
    }
    else
    {
        // No tracks loaded - output silence
        bufferToFill.clearActiveBufferRegion();
    }
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
    transportSource2.releaseResources();
   respeeder.releaseResources();
   respeeder2.releaseResources();
    mixer.releaseResources();
    

    
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
    else if (source == &transportSource2)
    {
        if (transportSource2.hasStreamFinished() && isLoopingEnabled2)
        {
            transportSource2.setPosition(0.0);
            transportSource2.start();
        }
    }
}


