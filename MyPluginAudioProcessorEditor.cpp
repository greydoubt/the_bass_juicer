MyPluginAudioProcessorEditor.cpp:

#include "PluginProcessor.h"
#include "PluginEditor.h"


MyPluginAudioProcessorEditor::MyPluginAudioProcessorEditor (MyPluginAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{


setSize (400, 300);
}

MyPluginAudioProcessorEditor::~MyPluginAudioProcessorEditor()
{
}


void MyPluginAudioProcessorEditor::paint (juce::Graphics& g)
{



g.fillAll (juce::Colours::white);


g.setColour (juce::Colours::black);


g.setFont (15.0f);
g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MyPluginAudioProcessorEditor::resized()
{


	

}


