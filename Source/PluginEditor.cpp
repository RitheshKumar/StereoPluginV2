/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TestFilterAudioProcessorEditor::TestFilterAudioProcessorEditor (TestFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 620);
    
    
    for (int i = 0; i<7; i++) {
        freqKnob[i].setRange(0, 20000);
        freqKnob[i].setSkewFactorFromMidPoint(1200);
        addAndMakeVisible(freqKnob[i]);
        qKnob[i].setRange(0, 10);
        addAndMakeVisible(qKnob[i]);
        gainKnob[i].setRange(0,2.0);
        addAndMakeVisible(gainKnob[i]);
    }
   

    startTimer(500);
}

TestFilterAudioProcessorEditor::~TestFilterAudioProcessorEditor()
{
}

//==============================================================================
void TestFilterAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TestFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    for (int i=0; i<7; i++) {
        freqKnob[i].setBounds(0, 20 + i*85, getWidth(), 40);
        qKnob[i].setBounds(0, 40 + i*85, getWidth(), 40);
        gainKnob[i].setBounds(0, 60 + i*85, getWidth(), 40);
    }
    
}

void TestFilterAudioProcessorEditor::timerCallback() {
    for (int i=0; i<7; i++) {
        processor.setValue(i, freqKnob[i].getValue(), qKnob[i].getValue(), gainKnob[i].getValue());
    }
}

//void TestFilterAudioProcessorEditor::sliderValueChanged(Slider* slider) {
//
//    for (int i=0; i<7; i++) {
//        i f (slider == &freqKnob[i] || slider == &qKnob[i]) {
//            processor.setValue(i, freqKnob[i].getValue(), qKnob[i].getValue());
//            
//        }
//        break;
//    }
//    
//}