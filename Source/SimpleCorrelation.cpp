//
//  SimpleCorrelation.cpp
//  RecordingTry
//
//  Created by Rithesh Kumar Ravikumar on 9/8/15.
//
//

#include "SimpleCorrelation.h"

SimpleCorrelation::SimpleCorrelation() {
}

SimpleCorrelation::~SimpleCorrelation() {
}

float SimpleCorrelation::findCorrCoeff(const float ** data, int numSamples) {
    
    float lSD = sqrt(calcVariance(data[0], numSamples));
    float rSD = sqrt(calcVariance(data[1], numSamples));
    float coV = calcCovariance(data, numSamples); 
    return coV/(lSD*rSD);
}

float SimpleCorrelation::calcVariance(const float *data, int numSamples) {
    int n = 0;
    float mean = 0.f,
          var  = 0.0f,
          delta;

    for ( int sample = 0; sample < numSamples; sample++ ) {
        n++;
        delta = data[sample] - mean;
        mean += delta/n;
        var  += delta*( data[sample] - mean );
    }

    if (n < 2)
        return NAN;
    else
        return var/(n-1);
    
}

float SimpleCorrelation::calcCovariance(const float ** data, int numSamples) {
    float mean1 = 0.0f,
          mean2 = 0.0f,
          coVar = 0.0f,
          delta1, delta2;

    for ( int sample = 0; sample < numSamples; sample++ ) {
        delta1 = (data[0][sample] - mean1) / (sample + 1);
        mean1 += delta1;
        delta2 = (data[1][sample] - mean2) / (sample + 1);
        mean2 += delta2;
        coVar += sample*delta1*delta2 - coVar/(sample + 1);
    }

    return  numSamples/(numSamples - 1.f) * coVar;
    
}
    


//____________________________________________________________________________________
//_____________________________**********************_________________________________
