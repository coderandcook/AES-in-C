#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#include "KeyExpansion.h"
#include "AddRoundKey3.h"
#include "InvShiftRows.h"
#include "InvMixColumns.h"
#include "InvSubBytes.h"
#include "InvCipher.h"

void invCipher32(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey){
  struct state2 s;
  for(int i=0; i<4; i++) s.block[i] = in[i];

  AddRoundKey32(&s,ekey,10*4);
  printf("\n");
  for(int i=9; i>=0; i--){
    InvShiftRows32(&s);
    InvSubState32(&s);
    AddRoundKey32(&s,ekey,i*4);
    if(i!=0) InvMixColumns32(&s);
  }
  for(int i=0; i<4; i++)out[i] = s.block[i];
}
