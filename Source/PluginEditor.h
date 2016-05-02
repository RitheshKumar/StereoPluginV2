/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class TestFilterAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer
//                                        public SliderListener
{
public:
    TestFilterAudioProcessorEditor (TestFilterAudioProcessor&);
    ~TestFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
//    void sliderValueChanged (Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestFilterAudioProcessor& processor;
    Slider freqKnob[7], qKnob[7], gainKnob[7];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestFilterAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED