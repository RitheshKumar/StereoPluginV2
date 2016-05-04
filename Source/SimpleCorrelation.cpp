//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation( int iMaxBlockSize, int iNumChannels, float fSampleRate )  :
                                                                                frequency (0.0),
                                                                               _iNumChannels(iNumChannels),
                                                                               _iAcfBufLen(2* iMaxBlockSize - 1),
                                                                               _ppfAucorr( new float*[iNumChannels] ),
                                                                               _fSampleRate( fSampleRate ),
                                                                               _fFrequency(0.0f),
                                                                               curFreq(0),
                                                                               prevFreq(0)
{

    iter   = 0;

    for( int c=0; c<iNumChannels; c++ ) {
        _ppfAucorr[c] = new float[ _iAcfBufLen ];
    }

}

SimpleCorrelation::~SimpleCorrelation() {

    for( int c=0; c<_iNumChannels; c++ ) {
        delete [] _ppfAucorr[c];
    }
    delete [] _ppfAucorr;
    _ppfAucorr = 0;

}



void SimpleCorrelation::correlate ( const float** inputData, float &freq, float &midiNote, int numSamples )
{

    int acfSize = 2*numSamples-1;
    startIndex = numSamples;



    for ( int i=numSamples-1,cnt = 0; cnt<numSamples; i--, cnt++ ) {
        for( int j=0; j<numSamples; j++ ) {
            _ppfAucorr[0][cnt+j] += inputData[0][i]*inputData[1][j];
        }
    }


    float maxVal=0.0;


    for ( int i = startIndex; i < acfSize - 1; i++ ) {
        if ( _ppfAucorr[0][i-1] < _ppfAucorr[0][i] && _ppfAucorr[0][i] >= _ppfAucorr[0][i+1] ) {
            if ( _ppfAucorr[0][i] >= maxVal ) {
                    maxVal   = _ppfAucorr[0][i];
                    endIndex = i;
            }
        }
    }
        
    
    reset(); //This function uses a lot of CPU!!

}


void SimpleCorrelation::reset() {
    for ( int c = 0; c < _iNumChannels; c++ ) {
        for ( int sample = 0; sample < _iAcfBufLen; sample++ ) {
            _ppfAucorr[c][sample] = 0.0f;
        }
    }
}


//____________________________________________________________________________________
//_____________________________**********************_________________________________
