#include <stdio.h>
#include <stdlib.h>
//#include "ShiftRows2.h"
#include "KeyExpansion.h"
#include "SubBytes2.h"

//pass state, 4 words from expkey, and 0<=i<=10
void AddRoundKey_generic(struct state *s,struct expKey *ekey,int i){
  int k,j;
  uint8_t temp = 0x00;

  struct state *temp_state = newState();
  for(j=0; j<4; j++){
    for(k=0; k<4; k++){
      temp_state->block[k][j] = ekey->wordList[j+i][k];
    }
  }

  /*
  printf("\nstate copy\n");
  for(k=0; k<4; k++){
    for(j=0; j<4; j++) printf("%x ",temp_state->block[k][j]);
    printf("\n");
  }
  printf("\n");*/

  //add extracted key to state(similar to AddRoundKey)
  for(k=0; k<4; k++){
    for(j=0; j<4; j++){
      temp = (s->block[k][j])^(temp_state->block[k][j]);
      setState(k,j,temp,s);
    }

  }
}
