/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "biquadFilter.h"
#include "PeakProgramMeter.h"
#include "Mono2Stereo.cpp"
#include "SimpleCorrelation.h"


//==============================================================================
/**
*/
class TestFilterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TestFilterAudioProcessor();
    ~TestFilterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void setValue( int filterID, float freqVal, float qVal, float gainVal);
    void setDelay(float delay){  M2S.setDelay(delay); }
    float getPeakVal(int channel ){ return _peakVal[channel]; }
    float getCorrCoeff(){ return isnan(_corrCoeff)?0:_corrCoeff; }
    void preset(int presetNum);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestFilterAudioProcessor)
    
//    float freq[7] = {400, 10250, 16850, 6950, 13550, 20250, 1025}, q[7];
    CFxRbjFilter testFilter;
    
    CFxRbjFilter biquadF[2][3],
                 commonF;
    float gainParams[2][3] = { {  0.4,  0.8,  0.8},
                               {1.4, 1.58, 1.58} }; //centre is 0.8
    float commonG = 0.5;
    
    float *_peakVal; //we will store only values for the first 2 channels
    float _corrCoeff;
    
    PeakProgramMeter *pPPM;
    Mono2Stereo M2S;
    SimpleCorrelation corrCoeff;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
