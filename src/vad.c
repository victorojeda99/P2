#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pav_analysis.h"
#include "vad.h"

const float FRAME_TIME = 10.0F; /* in ms. */
const int   FRAME_SILENCE_UNDEF = 17; 
const float THRESHOLD_K1 = 4.20; 



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

Features compute_features(const float *x, int N) {
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  Features feat;
  feat.zcr=compute_zcr(x, N, 16000);
  feat.p=compute_power(x, N);
  feat.am=compute_am(x, N);
  return feat;
}

VAD_DATA * vad_open(float rate, float alfa0) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->previous_state = ST_INIT;
  vad_data->state = ST_INIT;
  vad_data->alfa0 = alfa0;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->k0 = 0;
  vad_data->last_feature = 0;
  vad_data->last_change = 0;
  vad_data->frame = 0;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  VAD_STATE state = vad_data->previous_state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

VAD_STATE vad(VAD_DATA *vad_data, float *x) {
  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
    case ST_INIT:
      vad_data->k0 = f.p + vad_data->alfa0;
      vad_data->state = ST_AUX_SILENCE;
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
      if (f.p > (vad_data->k0 + THRESHOLD_K1)){
        vad_data->state = ST_VOICE;
      }else if((vad_data->frame - vad_data->last_change) == FRAME_SILENCE_UNDEF){
        vad_data->state = ST_SILENCE;
      }
    break;

    case ST_AUX_VOICE:
      if (f.p < (vad_data->k0 + THRESHOLD_K1)){
        vad_data->state = ST_SILENCE;
      }else{
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
