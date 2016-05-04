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

struct delayStruct {
    
    delayStruct() {
        
        delayLine = 0;
        readIdx = 0; writeIdx = 0;
        _delay  = 0;
        
    }
    ~delayStruct() {
        
        //Deallocate delayLine
        for (int c =0; c<2; c++)
            delete [] delayLine[c];
        delete [] delayLine;
        delayLine = 0;
        
        delete [] _delay;
    }
    
    void init(int sampleRate) {
        
        _sampleRate = sampleRate;
        
        //Allocate delayLine
        delayLine  = new float*[2];
        for (int c =0; c<2; c++) {
            delayLine[c] = new float[sampleRate]; //MaxDelayOneSec.
            memset(delayLine[c],0,sampleRate);
        }
        
        _delay     = new float[2]; _delay[0] = 0.1; _delay[1] = 0.1;
        
    }
    
    float getDelayVal(float input, int channel) {
        
        if( writeIdx >= _sampleRate)
            writeIdx = 0;
        
        delayLine[channel][writeIdx] = input;
        
        readIdx = writeIdx - _delay[channel]*_sampleRate;
        writeIdx++;
        
        if( readIdx < 0)
            readIdx = _sampleRate + readIdx;
        
        return delayLine[channel][readIdx];
    }
    
    void setDelay(float delay, int channel) { _delay[channel] = delay; }
    
private:
    float **delayLine, *_delay;
    int readIdx, writeIdx,
        _sampleRate;
    
};



class Mono2Stereo {
public:
    Mono2Stereo():_dly(new delayStruct) {

    }
    
    ~Mono2Stereo() {
        
    }
    
    void init(int sampleRate) {
        
        _sampleRate = sampleRate;
        
        _dly->init(sampleRate);
    
        presetCoeff(1);

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
                + commonG*commonF.filter(inputVal) + 0.3*_dly->getDelayVal(inputVal, channel);
            }
            
        }

    }
    
    void presetCoeff( int presetID ) {
        switch (presetID) {
            case 1:
                biquadF[0][0].calc_filter_coeffs(2,400,_sampleRate,1.0f,-20,true);    gainParams[0][0] = 0.8f;
                biquadF[0][1].calc_filter_coeffs(2,10250,_sampleRate,3.1f,-20,true);  gainParams[0][1] = 1.6f;
                biquadF[0][2].calc_filter_coeffs(2,16850,_sampleRate,5.1f,-20,true);  gainParams[0][2] = 1.6f;
                biquadF[1][0].calc_filter_coeffs(2,6950,_sampleRate,2.1f,-20,true);   gainParams[1][0] = 1.4f;
                biquadF[1][1].calc_filter_coeffs(2,13550,_sampleRate,4.1f,-20,true);  gainParams[1][1] = 1.58f;
                biquadF[1][2].calc_filter_coeffs(2,20250,_sampleRate,5.8f,-20,true);  gainParams[1][2] = 1.58f;
                commonF.calc_filter_coeffs(0, 1025, _sampleRate, 0.5f, -20, true);    commonG = 0.5f;
                break;
            case 2:
                biquadF[0][0].calc_filter_coeffs(2,4113.14,_sampleRate,3.31f,-20,true);    gainParams[0][0] = 0.9857f;
                biquadF[0][1].calc_filter_coeffs(2,9416.04,_sampleRate,2.81f,-20,true);    gainParams[0][1] = 0.7442f;
                biquadF[0][2].calc_filter_coeffs(2,17196.3,_sampleRate,2.58f,-20,true);    gainParams[0][2] = 0.3249f;
                biquadF[1][0].calc_filter_coeffs(2,5084.58,_sampleRate,3.17f,-20,true);    gainParams[1][0] = 0.9892f;
                biquadF[1][1].calc_filter_coeffs(2,12493.03,_sampleRate,2.69f,-20,true);   gainParams[1][1] = 0.7686f;
                biquadF[1][2].calc_filter_coeffs(2,17363.7,_sampleRate,3.17f,-20,true);    gainParams[1][2] = 0.3589f;
                commonF.calc_filter_coeffs(0, 1541.6, _sampleRate, 3.28f, -20, true);      commonG = 0.8273f;
                break;
                
            case 3:
                biquadF[0][0].calc_filter_coeffs(2,3446.01,_sampleRate,3.31f,-20,true);    gainParams[0][0] = 1.0319f;
                biquadF[0][1].calc_filter_coeffs(2,10770.58,_sampleRate,1.81f,-20,true);   gainParams[0][1] = 0.8194f;
                biquadF[0][2].calc_filter_coeffs(2,16450.77,_sampleRate,2.58f,-20,true);   gainParams[0][2] = 0.3249f;
                biquadF[1][0].calc_filter_coeffs(2,7261.96,_sampleRate,3.17f,-20,true);    gainParams[1][0] = 1.0287f;
                biquadF[1][1].calc_filter_coeffs(2,13316.24,_sampleRate,2.69f,-20,true);   gainParams[1][1] = 0.8033f;
                biquadF[1][2].calc_filter_coeffs(2,17367.51,_sampleRate,4.57f,-20,true);   gainParams[1][2] = 0.8114f;
                commonF.calc_filter_coeffs(0, 1728.73, _sampleRate, 1.39f, -20, true);     commonG = 0.8273f;
                break;
                
            case 4:
                biquadF[0][0].calc_filter_coeffs(2,4000,_sampleRate,2.26f,-20,true);     gainParams[0][0] = 0.3266f;
                biquadF[0][1].calc_filter_coeffs(2,9000,_sampleRate,0.61f,-20,true);     gainParams[0][1] = 0.4648f;
                biquadF[0][2].calc_filter_coeffs(2,16000,_sampleRate,1.78f,-20,true);    gainParams[0][2] = 0.8287f;
                biquadF[1][0].calc_filter_coeffs(2,3891.73,_sampleRate,1.38f,-20,true);  gainParams[1][0] = 0.3014f;
                biquadF[1][1].calc_filter_coeffs(2,13000,_sampleRate,1.04f,-20,true);    gainParams[1][1] = 0.5697f;
                biquadF[1][2].calc_filter_coeffs(2,17000,_sampleRate,4.84f,-20,true);    gainParams[1][2] = 0.8508f;
                commonF.calc_filter_coeffs(0, 87.46, _sampleRate, 0.85f, -20, true);     commonG = 0.8258f;
                break;
                
            default:
                break;
        }
        _dly->setDelay(0.2, 0); _dly->setDelay(0.2, 1);
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
    
    void setDelay(float delay){
        delay /= 10.f;
        _dly->setDelay(4*delay,      0);
        _dly->setDelay(4*delay+0.01, 1);
    }
    
private:
    
    CFxRbjFilter biquadF[2][3],
                 commonF,
                 allPass;
    delayStruct  *_dly;
    
    float gainParams[2][3] = { {  0.4,  0.8,  0.8},
        {1.4, 1.58, 1.58} }; //centre is 0.8
    float commonG = 0.5, _delay = 0.2;
    int _sampleRate;
    
};



#endif