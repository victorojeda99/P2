#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {

  float power = 0;
  for(int i = 0; i<N; i++){
    power += x[i]*x[i];
  }
  power = 10*log10(power/N);

  return power;
}

float compute_am(const float *x, unsigned int N) {

  float amp = 0;
  for(int i = 0; i<N; i++){
    amp += fabs(x[i]);
  }
  amp = amp/N;
  return amp;
}

float compute_zcr(const float *x, unsigned int N, float fm){

  float zcr = 0;
  for(int i = 1; i<N; i++){
    if ((x[i]>0 && x[i-1]<=0) || (x[i]<0 && x[i-1]>=0))
    {
      zcr++;
    }      
  }
  zcr = zcr*fm/(2*(N-1));
  return zcr;
}
