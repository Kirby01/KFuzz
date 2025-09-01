/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//==============================================================================
KFuzzAudioProcessor::KFuzzAudioProcessor()
:x1(2, 9),Parameters(*this, nullptr, "Parameters", createParameters()) // x1(channel, bufferSize)
{
}

KFuzzAudioProcessor::~KFuzzAudioProcessor()
{
}

//==============================================================================
const juce::String KFuzzAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KFuzzAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KFuzzAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KFuzzAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KFuzzAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KFuzzAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KFuzzAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KFuzzAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KFuzzAudioProcessor::getProgramName (int index)
{
    return {};
}

void KFuzzAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KFuzzAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
      x1.clear();
}

void KFuzzAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
      x1.clear();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KFuzzAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void KFuzzAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
 for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (0);
        auto* channelData1 = buffer.getWritePointer (1);
                const float* readData = buffer.getReadPointer (channel);
          float* z = x1.getWritePointer (channel);
          float* z2 = x1.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {

           if (channelData[sample]==0 || channelData1[sample]==0)
            
            {channelData[sample]=0;
            channelData1[sample]=0;} else{
            
            if (channel==0){
            ad = channelData[sample]-z[0];
            z[0]=z[0]+(10000.00/44100.00)*ad;
            channelData[sample]=z[0];
            
            ad2 = channelData[sample]-z[1];
            z[1]=z[1]+(10000.00/44100.00)*ad2;
            channelData[sample]=z[1];
            
            ad3 = channelData[sample]-z[2];
            z[2]=z[2]+(10000.00/44100.00)*ad3;
            channelData[sample]=z[2];
            
            ad4 = channelData[sample]-z[3];
            z[3]=z[3]+(10000.00/44100.00)*ad4;
            channelData[sample]=z[3]; 
            

            
            a = abs(channelData[sample]/2);
            b = (abs(channelData[sample]*2));
            c = abs(pow(b,rawVolume));
            d = abs((a*c)/abs(channelData[sample]));
            e = channelData[sample]*(1/sqrt(channelData[sample]*channelData[sample]))*d;
             
            
            if (d>0 || d<0) 
            {channelData[sample]=e/4;}
            {channelData[sample]=channelData[sample];}
            
            ad5 = channelData[sample]-z[4];
            z[4]=z[4]+(160.00/44100.00)*ad5;
            channelData[sample]-=z[4];
            
            ad6 = channelData[sample]-z[5];
            z[5]=z[5]+(10000.00/44100.00)*ad6;
            channelData[sample]=z[5];
            
            ad7 = channelData[sample]-z[6];
            z[6]=z[6]+(10000.00/44100.00)*ad7;
            channelData[sample]=z[6];
            
            ad8 = channelData[sample]-z[7];
            z[7]=z[7]+(10000.00/44100.00)*ad8;
            channelData[sample]=z[7];
            
            ad9 = channelData[sample]-z[8];
            z[8]=z[8]+(10000.00/44100.00)*ad9;
            channelData[sample]=z[8];}
            
            else if (channel==1)
                
            {ad2x = channelData1[sample]-z2[0];
            z2[0]=z2[0]+(10000.00/44100.00)*ad2x;
            channelData1[sample]=z2[0];
            
            ad22 = channelData1[sample]-z2[1];
            z2[1]=z2[1]+(10000.00/44100.00)*ad22;
            channelData1[sample]=z2[1];
            
            ad32 = channelData1[sample]-z2[2];
            z2[2]=z2[2]+(10000.00/44100.00)*ad32;
            channelData1[sample]=z2[2];
            
            ad42 = channelData1[sample]-z2[3];
            z2[3]=z2[3]+(10000.00/44100.00)*ad42;
            channelData1[sample]=z2[3]; 
            

            
            a2 = abs(channelData1[sample]/2);
            b2 = (abs(channelData1[sample]*2));
            c2 = abs(pow(b2,rawVolume));
            d2 = abs((a2*c2)/abs(channelData1[sample]));
            e2 = channelData1[sample]*(1/sqrt(channelData1[sample]*channelData1[sample]))*d2;
             
            
            if (d2>0 || d2<0) 
            {channelData1[sample]=e2/4;}
            {channelData1[sample]=channelData1[sample];}
            
            ad52 = channelData1[sample]-z2[4];
            z2[4]=z2[4]+(160.00/44100.00)*ad52;
            channelData1[sample]-=z2[4];
            
            ad62 = channelData1[sample]-z2[5];
            z2[5]=z2[5]+(10000.00/44100.00)*ad62;
            channelData1[sample]=z2[5];
            
            ad72 = channelData1[sample]-z2[6];
            z2[6]=z2[6]+(10000.00/44100.00)*ad72;
            channelData1[sample]=z2[6];
            
            ad82 = channelData1[sample]-z2[7];
            z2[7]=z2[7]+(10000.00/44100.00)*ad82;
            channelData1[sample]=z2[7];
            
            ad92 = channelData1[sample]-z2[8];
            z2[8]=z2[8]+(10000.00/44100.00)*ad92;
            channelData1[sample]=z2[8];}
            
            
            }
            
        }
        

        // ..do something to the data...
    }
}

//==============================================================================
bool KFuzzAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KFuzzAudioProcessor::createEditor()
{
    return new KFuzzAudioProcessorEditor (*this);
}

//==============================================================================
void KFuzzAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
     auto state = Parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void KFuzzAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(Parameters.state.getType()))
            Parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }

}
juce::AudioProcessorValueTreeState::ParameterLayout KFuzzAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("HZ", "hz", juce::NormalisableRange<float> { 0.01f, 1.0f, 0.01f }, 0.00, "hz"));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KFuzzAudioProcessor();
}
