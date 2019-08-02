#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "shifter.h"
#include "InvShiftRows.h"

void InvShiftRows(struct state2 *s){
  s->block[1] = rshift32(s->block[1],1);
  s->block[2] = rshift32(s->block[2],2);
  s->block[3] = rshift32(s->block[3],3);
}
