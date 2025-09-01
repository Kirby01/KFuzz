/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class KFuzzAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KFuzzAudioProcessor();
    ~KFuzzAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
//double rawVolume =200.0f;
    double rawVolume = 0.3;
            juce::AudioProcessorValueTreeState Parameters;


private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KFuzzAudioProcessor)
            juce::AudioSampleBuffer x1; ;double a,b,c,d,e,f,g,h,ad=0,ad2=0,ad3=0,ad4=0,ad5=0,ad6=0,ad7=0,ad8=0,ad9=0;double a2,b2,c2,d2,e2,f2,g2,h2,ad2x=0,ad22=0,ad32=0,ad42=0,ad52=0,ad62=0,ad72=0,ad82=0,ad92=0;    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();


    
};
