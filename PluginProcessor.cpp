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
    
    double sampleRate = getSampleRate();
    double omega = 2.0 * juce::MathConstants<double>::pi * 40.0 / sampleRate;
    double alpha = std::sin(omega) / (2.0 * 0.707);
    double cosOmega = std::cos(omega);
    double sqrt2 = std::sqrt(2.0);
    double A = 1.0 + alpha / sqrt2;
    double B = -2.0 * cosOmega;
    double C = 1.0 - alpha / sqrt2;
    double D = 1.0 + alpha * sqrt2;
    double E = -2.0 * cosOmega;
    double F = 1.0 - alpha * sqrt2;
    A0 = 1.0;
    A1 = B / A;
    A2 = C / A;
    B0 = D / A;
    B1 = E / A;
    B2 = F / A;
}

MyPluginAudioProcessor::~MyPluginAudioProcessor()
{
}


const juce::
juce::String MyPluginAudioProcessor::getName() const
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
}

const juce::String MyPluginAudioProcessor::getProgramName (int index)
{
return {};
}

void MyPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void MyPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{


}

void MyPluginAudioProcessor::releaseResources()
{


}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
juce::ignoreUnused (layouts);
return true;
#else





if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
return false;

    
#if !JucePlugin_IsSynth
if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
return false;
#endif
return true;
#endif
}
#endif

void MyPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
juce::ScopedNoDenormals noDenormals;

const int numChannels = buffer.getNumChannels();
const int numSamples = buffer.getNumSamples();


for (int channel = 0; channel < numChannels; ++channel)
{
    float* channelData = buffer.getWritePointer(channel);

    for (int i = 0; i < numSamples; ++i)
    {
        float x0 = channelData[i];
        float y0 = B0 / A0 * x0 + B1 / A0 * z1[channel] + B2 / A0 * z2[channel] - A1 / A0 * y1[channel] - A2 / A0 * y2[channel];

                z2[channel] = z1[channel];
        z1[channel] = x0;
        y2[channel] = y1[channel];
        y1[channel] = y0;

        channelData[i] = y0;
    }
}


const float targetDB = 6.0f;
const float targetGain = std::pow(10.0f, targetDB / 20.0f);

const float lowCutoff = 40.0f;
const float midCutoff = 60.0f;
const float highCutoff = 80.0f;

for (int channel = 0; channel < numChannels; ++channel)
{
    float* channelData = buffer.getWritePointer(channel);

    for (int i = 0; i < numSamples; ++i)
    {
        float frequency = getFrequencyForSampleRate(getSampleRate(), i);

        if (frequency >= lowCutoff && frequency <= highCutoff)
        {
            float gain = targetGain;

            if (frequency >= midCutoff)
            {
                gain *= juce::jmap(frequency, midCutoff, highCutoff, 1.0f, targetGain);
            }
            else
            {
                gain *= juce::jmap(frequency, lowCutoff, midCutoff, targetGain, 1.0f);
            }

            channelData[i] *= gain;
        }
    }
}


keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
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



    juce::MemoryOutputStream stream(destData, true);
parameters.state.writeToStream(stream);
}

void MyPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{


    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);

if (tree.isValid())
{
    parameters.state = tree;
}
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
return new MyPluginAudioProcessor();
}
