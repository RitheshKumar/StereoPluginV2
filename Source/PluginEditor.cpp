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
//    setSize (400, 620);
    
    
//    for (int i = 0; i<7; i++) {
//        freqKnob[i].setRange(0, 20000);
//        freqKnob[i].setSkewFactorFromMidPoint(1200);
//        addAndMakeVisible(freqKnob[i]);
//        qKnob[i].setRange(0, 10);
//        addAndMakeVisible(qKnob[i]);
//        gainKnob[i].setRange(0,2.0);
//        addAndMakeVisible(gainKnob[i]);
//    }
    
    setSize (800, 600);
    
    addAndMakeVisible(correlationBar);
    corrBarLabel.setFont(Font("Times New Roman", 20.0f, Font::plain ));
    addAndMakeVisible(corrBarLabel);
    
    addAndMakeVisible(ppmBarL); ppmBarL.setVertical(true);
    addAndMakeVisible(ppmBarR); ppmBarR.setVertical(true);
    
    const char* options[] = { "Oldies", "Rock", "Classical", nullptr };
    presetList.addItemList(StringArray(options), 1);
    addAndMakeVisible(presetList);
    
    addAndMakeVisible(widthSetBox); widthSetBox.setSlider(true); //this is just for readability. The default is true.
    addAndMakeVisible(depthSetBox); depthSetBox.setSlider(false);
   

    startTimer(10);
}

TestFilterAudioProcessorEditor::~TestFilterAudioProcessorEditor()
{
}

//==============================================================================
void TestFilterAudioProcessorEditor::paint (Graphics& g)
{
//    g.fillAll (Colours::white);
//
//    g.setColour (Colours::black);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
    
    g.fillAll (Colours::white);
    
    g.setColour (Colours::black);
    g.setFont (Font("Times New Roman", 22.0f, Font::bold ));
    g.drawText("MONO2STEREO", proportionOfWidth(0.4f), proportionOfHeight(0.05f), proportionOfWidth(0.3f), proportionOfHeight(0.15f), true);
    g.setFont (Font("Times New Roman", 18.0f, Font::plain ));
    g.drawText("-1", 20, 520, 30, 10, true);
    g.drawText("0", getWidth()/2-10, 520, 30, 10, true);
    g.drawText("+1", getWidth()-40, 520, 30, 10, true);
}

void TestFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
//    for (int i=0; i<7; i++) {
//        freqKnob[i].setBounds(0, 20 + i*85, getWidth(), 40);
//        qKnob[i].setBounds(0, 40 + i*85, getWidth(), 40);
//        gainKnob[i].setBounds(0, 60 + i*85, getWidth(), 40);
//    }
    Rectangle<int> r (getLocalBounds().reduced (8));
    
    Rectangle<int> barArea ( r.removeFromBottom(120));
    
    barArea.removeFromRight( jmin(50, (r.removeFromLeft(10)).getWidth() ) );
    barArea.removeFromLeft(  jmin(50, (r.removeFromRight(10)).getWidth() ) );
    
    correlationBar.setBounds(barArea.removeFromTop(35));
    corrBarLabel.setBounds(barArea.removeFromRight(getWidth()/2 + 35));
    
    ppmBarL.setBounds(getWidth()/2-40, 100, 20, 300);
    ppmBarR.setBounds(getWidth()/2, 100, 20, 300);
    
    presetList.setBounds(getWidth()/2-75, 420, 130, 22);
    
    widthSetBox.setBounds(20, 100, 300, 225);
    depthSetBox.setBounds(475, 100, 300, 225);
    
    
}

void TestFilterAudioProcessorEditor::timerCallback() {
//    for (int i=0; i<7; i++) {
//        processor.setValue(i, freqKnob[i].getValue(), qKnob[i].getValue(), gainKnob[i].getValue());
//    }
    ppmBarL.setPeakVal(processor.getPeakVal(0));
    ppmBarL.repaint();
    
    ppmBarR.setPeakVal(processor.getPeakVal(1));
    ppmBarR.repaint();
    
    processor.preset(presetList.getSelectedId());
    
//    switch (presetList.getSelectedId()) {
//        case 1:
//            std::cout<<"Oldies\n";
//            break;
//        case 2:
//            std::cout<<"Rock\n";
//            break;
//        case 3:
//            std::cout<<"Classical\n";
//            break;
//        default:
//            break;
//    }
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