#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pav_analysis.h"
#include "vad.h"

const float FRAME_TIME = 10.0F; /* in ms. */
const int T_VOZ_UNDEF=1; 
const int T_SIL_UNDEF=11; /*cambiar*/
const int N_INIT=13;
const float UMBRAL_K0 = 0.9; /*cambiar*/
const float UMBRAL_K1 = 4.72; /*cambiar*/



/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
  "UNDEF", "S", "V", "INIT"
};

const char *state2str(VAD_STATE st) {
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct {
  float zcr;
  float p;
  float am;
} Features;

/* 
 * TODO: Delete and use your own features!
 */

Features compute_features(const float *x, int N) {
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DONE: Include a call to your own functions
   */
  Features feat;
  feat.zcr=compute_zcr(x, N, 16000);
  feat.p=compute_power(x, N);
  feat.am=compute_am(x, N);
  return feat;
}

/* 
 * DONE: Init the values of vad_data
 */

VAD_DATA * vad_open(float rate, float alfa0) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->previous_state = ST_INIT;
  vad_data->state = ST_INIT;
  vad_data->alfa0 = alfa0;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->k0 = 0;
  vad_data->k1 = 0;
  vad_data->last_feature = 0;
  vad_data->last_change = 0;
  vad_data->frame = 0;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state = vad_data->previous_state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x) {

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
    case ST_INIT:
      vad_data->k0 = f.p + vad_data->alfa0;
      vad_data->k1 = vad_data->k0 + vad_data->alfa0;
      vad_data->state = ST_AUX_SILENCE;
/*      if(vad_data->frame < N_INIT){
        vad_data->k0 = pow(10, f.p/10);
      }else{
        vad_data->k0 = 10*log10(vad_data->k0 / N_INIT)*UMBRAL_K0;
        vad_data->state=ST_AUX_SILENCE;
      }*/
      break;

    case ST_SILENCE:
      if (f.p > vad_data->k0){
        vad_data->previous_state = ST_SILENCE;
        vad_data->state = ST_AUX_VOICE;
        vad_data->last_change = vad_data->frame;
      }
      break;

    case ST_VOICE:
      if (f.p < vad_data->k0)
        vad_data->previous_state = ST_VOICE;
        vad_data->state = ST_AUX_SILENCE;
        vad_data->last_change = vad_data->frame;
      break;

    case ST_AUX_SILENCE:
      if (f.p > (vad_data->k0 + UMBRAL_K1)){
        vad_data->state = ST_VOICE;
      }else if((vad_data->frame - vad_data->last_change) == T_SIL_UNDEF){
        vad_data->state = ST_SILENCE;
      }
    break;

    case ST_AUX_VOICE:
      if (f.p < (vad_data->k0 + UMBRAL_K1)){
        vad_data->state = ST_SILENCE;
      }else if((vad_data->frame - vad_data->last_change) == T_VOZ_UNDEF){
        vad_data->state = ST_VOICE;
      }
    break;

    case ST_UNDEF:
      break;
    
  }
  vad_data->frame ++;
  if (vad_data->state == ST_SILENCE || vad_data->state == ST_VOICE)
    return vad_data->state;
  else if (vad_data->state == ST_INIT)
    return ST_SILENCE;
  else
    return ST_UNDEF;

}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
