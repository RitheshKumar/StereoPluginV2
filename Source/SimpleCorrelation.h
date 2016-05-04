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
    SimpleCorrelation ();
    ~SimpleCorrelation();
    
    //==============================================================================
    
    float findCorrCoeff(const float ** data, int numSamples);

    //==============================================================================
    
private:

    //Private Functions
    void reset();
    float calcCovariance(const float **data, int numSamples);
    float calcVariance(const float *data, int numSamples);

};

#endif /* defined(__RecordingTry__SimpleCorrelation__) */



