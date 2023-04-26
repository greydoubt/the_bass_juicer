#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"



class MyPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
MyPluginAudioProcessorEditor (MyPluginAudioProcessor&);
~MyPluginAudioProcessorEditor() override;

void paint (juce::Graphics&) override;
void resized() override;
private:


MyPluginAudioProcessor& audioProcessor;
JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPluginAudioProcessorEditor)
};

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