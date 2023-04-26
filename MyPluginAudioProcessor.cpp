#include "PluginProcessor.h"
#include "PluginEditor.h"


MyPluginAudioProcessor::MyPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                           .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                           .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                           )
#endif
{
}

MyPluginAudioProcessor::~MyPluginAudioProcessor()
{
}


const juce::String MyPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyPluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool MyPluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool MyPluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double MyPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyPluginAudioProcessor::getNumPrograms()
{
    return 1;   
                
}

int MyPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused(index);
}

const juce::String MyPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused(index);
    return {};
}

void MyPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}


void MyPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    

    juce::ignoreUnused(samplesPerBlock);

    
    fs = sampleRate;

    
    lowShelfFilter.setCoefficients(juce::IIRCoefficients::makeLowShelf(fs, 40.0, 0.5, 3.0));
    midShelfFilter.setCoefficients(juce::IIRCoefficients::makePeakFilter(fs, 60.0, 1.0, 3.0));
    highShelfFilter.setCoefficients(juce::IIRCoefficients::makeHighShelf(fs, 80.0, 0.5, 3.0));
}

void MyPluginAudioProcessor::releaseResources()
{
    
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    
    
    
    
#if Juce
void MyPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
juce::ignoreUnused(midiMessages);

const int numSamples = buffer.getNumSamples();


for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
{
    auto* channelData = buffer.getWritePointer(channel);

    
    lowShelfFilter.processSamples(channelData, numSamples);

    
    midShelfFilter.processSamples(channelData, numSamples);

    
    highShelfFilter.processSamples(channelData, numSamples);

    
    juce::FloatVectorOperations::normalize(channelData, numSamples);
}
}


bool MyPluginAudioProcessor::hasEditor() const
{
return true;
}

juce::AudioProcessorEditor* MyPluginAudioProcessor::createEditor()
{
return new MyPluginAudioProcessorEditor (*this);
}


void MyPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{




juce::XmlElement xml ("MYPLUGINSETTINGS");


xml.setAttribute ("lowGain", lowGain);
xml.setAttribute ("midGain", midGain);
xml.setAttribute ("highGain", highGain);


if (auto* xmlFilter = lowShelfFilter.state.createXml())
{
    xml.addChildElement (xmlFilter);
}

if (auto* xmlFilter = midShelfFilter.state.createXml())
{
    xml.addChildElement (xmlFilter);
}

if (auto* xmlFilter = highShelfFilter.state.createXml())
{
    xml.addChildElement (xmlFilter);
}


copyXmlToBinary (xml, destData);
}

void MyPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{




juce::MemoryInputStream mem (data, static_cast<size_t> (sizeInBytes), false);
const auto xml = juce::parseXML (mem);

if (xml != nullptr && xml->hasTagName ("MYPLUGINSETTINGS"))
{
    
    lowGain = xml->getDoubleAttribute ("lowGain", lowGain);
    midGain = xml->getDoubleAttribute ("midGain", midGain);
    highGain = xml->getDoubleAttribute ("highGain", highGain);

    
    if (auto* xmlFilter = xml->getChildByName ("LOW_SHELF"))
    {
        lowShelfFilter.state = *juce::ValueTree::fromXml (*xmlFilter);
    }

    if (auto* xmlFilter = xml->getChildByName ("MID_PEAK"))
    {
        midShelfFilter.state = *juce::ValueTree::fromXml (*xmlFilter);
    }

    if (auto* xmlFilter = xml->getChildByName ("HIGH_SHELF"))
    {
        highShelfFilter.state = *juce::ValueTree::fromXml (*xmlFilter);
    }
}
}


juce::AudioProcessorValueTreeState::ParameterLayout MyPluginAudioProcessor::createParameterLayout()
{
juce::AudioProcessorValueTreeState::ParameterLayout layout;

layout.add(std::make_unique<juce::AudioParameterFloat>(
    "lowGain",   
    "Low Gain",  
    juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),   
    0.0f         
));


layout.add(std::make_unique<juce::AudioParameterFloat>(
    "midGain",   
    "Mid Gain",  
    juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),   
    0.0f         
));


layout.add(std::make_unique<juce::AudioParameterFloat>(
    "highGain",  
    "High Gain", 
    juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),   
    0.0f         
));

return layout;
}