#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "AddRoundKey3.h"

void AddRoundKey(struct state2 *s, const struct expKey32 *ekey, int i){
  for(int j=0; j<4; j++) s->block[j] ^= ekey->block[j+i];
}
