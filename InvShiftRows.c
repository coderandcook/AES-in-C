#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "shifter.h"
#include "InvShiftRows.h"

void InvShiftRows(struct state2 *s){
  s->block[1] = rotR1(s->block[1]);
  s->block[2] = rotR2(s->block[2]);
  s->block[3] = rotR3(s->block[3]);
}
