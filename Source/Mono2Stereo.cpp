/*
  ==============================================================================

    Mono2Stereo.cpp
    Created: 3 May 2016 6:20:58pm
    Author:  Rithesh Kumar Ravikumar

  ==============================================================================
*/


#ifndef MONO2STEREO_H_INCLUDED
#define MONO2STEREO_H_INCLUDED

#include "biquadFilter.h"
#include "../JuceLibraryCode/JuceHeader.h"

class Mono2Stereo {
public:
    Mono2Stereo() {
        
    }
    
    ~Mono2Stereo() {
    }
    
    void init(int sampleRate) {
        _sampleRate = sampleRate;
        presetCoeff(5);

    }
    
    void process(AudioSampleBuffer &buffer) {
        const float* inputData   = buffer.getReadPointer(0);//since ours is a mono track
        
        float** channelData = buffer.getArrayOfWritePointers();
        for (int sample =0; sample< buffer.getNumSamples(); sample++ ) {
            float inputVal = inputData[sample];

            for (int channel = 0; channel<2; channel++) { //since we are only handling stereo
                channelData[channel][sample] = gainParams[channel][0]*biquadF[channel][0].filter(inputVal)
                + gainParams[channel][1]*biquadF[channel][1].filter(inputVal)
                + gainParams[channel][2]*biquadF[channel][2].filter(inputVal)
                + commonG*commonF.filter(inputVal);
            }
            
        }
    }
    
    void presetCoeff( int presetID ) {
        switch (presetID) {
            case 1:
                biquadF[0][0].calc_filter_coeffs(2,400,_sampleRate,1.0f,-20,true);
                biquadF[0][1].calc_filter_coeffs(2,10250,_sampleRate,3.1f,-20,true);
                biquadF[0][2].calc_filter_coeffs(2,16850,_sampleRate,5.1f,-20,true);
                biquadF[1][0].calc_filter_coeffs(2,6950,_sampleRate,2.1f,-20,true);
                biquadF[1][1].calc_filter_coeffs(2,13550,_sampleRate,4.1f,-20,true);
                biquadF[1][2].calc_filter_coeffs(2,20250,_sampleRate,5.8f,-20,true);
                commonF.calc_filter_coeffs(0, 1025, _sampleRate, 0.5f, -20, true);
                break;
                
            default:
                biquadF[0][0].calc_filter_coeffs(2,400,_sampleRate,1.0f,-20,true);
                biquadF[0][1].calc_filter_coeffs(2,10250,_sampleRate,3.1f,-20,true);
                biquadF[0][2].calc_filter_coeffs(2,16850,_sampleRate,5.1f,-20,true);
                biquadF[1][0].calc_filter_coeffs(2,6950,_sampleRate,2.1f,-20,true);
                biquadF[1][1].calc_filter_coeffs(2,13550,_sampleRate,4.1f,-20,true);
                biquadF[1][2].calc_filter_coeffs(2,20250,_sampleRate,5.8f,-20,true);
                commonF.calc_filter_coeffs(0, 1025, _sampleRate, 0.5f, -20, true);
                break;
        }
    }
    
    void setParam( int ID, float freqVal, float qVal, float gainVal) {
        if (freqVal>2 && qVal > 0.2f && gainVal > 0) {
            switch (ID) {
                case 0:
                    biquadF[0][0].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][0] = gainVal;
                    break;
                case 1:
                    biquadF[0][1].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][1] = gainVal;
                    break;
                case 2:
                    biquadF[0][2].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][1] = gainVal;
                    break;
                case 3:
                    biquadF[1][0].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][1] = gainVal;
                    break;
                case 4:
                    biquadF[1][1].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][1] = gainVal;
                    break;
                case 5:
                    biquadF[1][2].calc_filter_coeffs(2, freqVal, _sampleRate, qVal, -20, false);
                    gainParams[0][1] = gainVal;
                    break;
                case 6:
                    commonF.calc_filter_coeffs(0, freqVal, _sampleRate, qVal, -20, false);
                    commonG = gainVal;
                    break;
                default:
                    break;
            }
        }
        
    }
private:
    
    CFxRbjFilter biquadF[2][3],
                commonF;
    
    float gainParams[2][3] = { {  0.4,  0.8,  0.8},
        {1.4, 1.58, 1.58} }; //centre is 0.8
    float commonG = 0.5;
    
    int _sampleRate;
    
};

#endif