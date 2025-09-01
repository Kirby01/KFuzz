/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KFuzzAudioProcessorEditor::KFuzzAudioProcessorEditor (KFuzzAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 285);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(0.01, 1.0);
    gainSlider.setValue(0.1);
    gainSlider.addListener(this);
    gainSlider.setBounds (32, 100, 150, 150);
    gainSlider.setTextValueSuffix ("%");
    AttachmentgainSlider = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.Parameters, "HZ", gainSlider);

    addAndMakeVisible(gainSlider);
}

KFuzzAudioProcessorEditor::~KFuzzAudioProcessorEditor()
{
}

//==============================================================================
void KFuzzAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//const auto image = juce::ImageCache::getFromMemory(BinaryData::bun_jpg, BinaryData::bun_jpgSize);
    g.setColour (juce::Colours::white);

    g.setFont (15.0f);
    g.drawFittedText ("KFuzz v1.2 - Harmonious Records", 1, 1, 200, 40, juce::Justification::centred, true);
        g.drawFittedText ("Input", 1, 1, 200, 520, juce::Justification::centred, true);
}

void KFuzzAudioProcessorEditor::resized()
{
   
    gainSlider.setBounds(getLocalBounds());
// This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
void KFuzzAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.rawVolume = gainSlider.getValue();
    }
}