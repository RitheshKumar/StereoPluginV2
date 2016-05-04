//
//  SimpleCorrelation.h
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 11/2/15.
//
//

#ifndef __RecordingTry__SimpleCorrelation__
#define __RecordingTry__SimpleCorrelation__

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include "../JuceLibraryCode/JuceHeader.h"

class SimpleCorrelation  
{
public:
    SimpleCorrelation ( int iMaxBlockSize, int iNumChannels, float fSampleRate );
    ~SimpleCorrelation();
    
    //==============================================================================
    
    void correlate ( const float** inputData, float &freq, float &midiNote, int numSamples );

    //==============================================================================
    
private:
    int64 nextSampleNum;
    int startIndex,endIndex,minIndex, iter;

    float frequency;
    int _iNumChannels,
        _iAcfBufLen;
    float **_ppfAucorr,
          _fSampleRate,
          _fFrequency;
    int curFreq,prevFreq;

    //Private Functions
    void reset();

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */



