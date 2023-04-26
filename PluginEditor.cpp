

#include "PluginEditor.h"

MyPluginAudioProcessorEditor::MyPluginAudioProcessorEditor (MyPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (400, 300);

    
    lowGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    lowGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    lowGainSlider.setRange(-24.0f, 24.0f, 0.1f);
    lowGainSlider.setValue(0.0f);
    lowGainSlider.addListener(this);
    addAndMakeVisible(&lowGainSlider);

    
    midGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    midGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    midGainSlider.setRange(-24.0f, 24.0f, 0.1f);
    midGainSlider.setValue(0.0f);
    midGainSlider.addListener(this);
    addAndMakeVisible(&midGainSlider);

    
    highGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    highGainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    highGainSlider.setRange(-24.0f, 24.0f, 0.1f);
    highGainSlider.setValue(0.0f);
    highGainSlider.addListener(this);
    addAndMakeVisible(&highGainSlider);
}

MyPluginAudioProcessorEditor::~MyPluginAudioProcessorEditor()
{
}

void MyPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll (juce::Colour(0xffe6e6e6));
}

void MyPluginAudioProcessorEditor::resized()
{
    
    lowGainSlider.setBounds(50, 50, 100, 100);
    midGainSlider.setBounds(150, 50, 100, 100);
    highGainSlider.setBounds(250, 50, 100, 100);
}
