#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "poly.h"
#include "div_poly.h"
#include "MixColumns.h"
#include "ShiftRows2.h"
#include "SubBytes2.h"
#include "shifter.h"
#include "InvMixColumns.h"

void InvMixColumns32(struct state2 *s){
  for(int i=0; i<4; i++){
    uint32_t multiplier = 0x0e0b0d09;
    uint32_t col = getColumn32(s,i);

    uint32_t temp0=0;
    for(int k=0; k<4; k++){
      uint32_t temp = mul32(col,multiplier);
      temp0 ^= temp<<(8*(3-k));
      multiplier = rshift32(multiplier,1);
    }
    setColumn32(s,i,temp0);
  }
}
