/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestFilterAudioProcessor::TestFilterAudioProcessor()
{
//    for (int i=0; i<7; i++) {
//        q[i] = 0.5;
//    } 
}

TestFilterAudioProcessor::~TestFilterAudioProcessor()
{
}

//==============================================================================
const String TestFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TestFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String TestFilterAudioProcessor::getProgramName (int index)
{
    return String();
}

void TestFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

//    testFilter.calc_filter_coeffs(0, freq, getSampleRate(), q, -20, true);
    
    biquadF[0][0].calc_filter_coeffs(2,400,sampleRate,1.0f,-20,true);
    biquadF[0][1].calc_filter_coeffs(2,10250,sampleRate,3.1f,-20,true);
    biquadF[0][2].calc_filter_coeffs(2,16850,sampleRate,5.1f,-20,true);
    biquadF[1][0].calc_filter_coeffs(2,6950,sampleRate,2.1f,-20,true);
    biquadF[1][1].calc_filter_coeffs(2,13550,sampleRate,4.1f,-20,true);
    biquadF[1][2].calc_filter_coeffs(2,20250,sampleRate,5.8f,-20,true);
    commonF.calc_filter_coeffs(0, 1025, sampleRate, 0.5f, -20, true);
}

void TestFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void TestFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    const float* inputData   = buffer.getReadPointer(0);//since ours is a mono track
    
    float** channelData = buffer.getArrayOfWritePointers();
    for (int sample =0; sample< buffer.getNumSamples(); sample++ ) {
        float inputVal = inputData[sample];
//        channelData[0][sample] = testFilter.filter(inputVal);
//        channelData[1][sample] = channelData[0][sample];
        for (int channel = 0; channel<2; channel++) {
            channelData[channel][sample] = gainParams[channel][0]*biquadF[channel][0].filter(inputVal)
                                         + gainParams[channel][1]*biquadF[channel][1].filter(inputVal)
                                         + gainParams[channel][2]*biquadF[channel][2].filter(inputVal)
                                         + commonG*commonF.filter(inputVal);
        }

    }
    
}

//==============================================================================
bool TestFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestFilterAudioProcessor::createEditor()
{
    return new TestFilterAudioProcessorEditor (*this);
}

//==============================================================================
void TestFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestFilterAudioProcessor();
}

void TestFilterAudioProcessor::setValue(int ID, float freqVal, float qVal, float gainVal) {
    
    if (freqVal>2 && qVal > 0.2f && gainVal > 0) {
        switch (ID) {
            case 0:
                biquadF[0][0].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][0] = gainVal;
                break;
            case 1:
                biquadF[0][1].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][1] = gainVal;
                break;
            case 2:
                biquadF[0][2].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][1] = gainVal;
                break;
            case 3:
                biquadF[1][0].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][1] = gainVal;
                break;
            case 4:
                biquadF[1][1].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][1] = gainVal;
                break;
            case 5:
                biquadF[1][2].calc_filter_coeffs(2, freqVal, getSampleRate(), qVal, -20, false);
                gainParams[0][1] = gainVal;
                break;
            case 6:
                commonF.calc_filter_coeffs(0, freqVal, getSampleRate(), qVal, -20, false);
                commonG = gainVal;
                break;
            default:
                break;
        }
    }

//    if (freq > 2 && q > 0.2f) {
//        testFilter.calc_filter_coeffs(0, freq, getSampleRate(), q, -20, false);
//    }
    
}
