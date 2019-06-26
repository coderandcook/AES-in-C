#include <stdio.h>
int *decimalToBin(int in);
int main(){
//round key addition
  //state array (-> first copied to the State array)
  //1. convert input (message) into State(array of words/ 2 dimensional array of bits)
  int i;
  int test = 2;
  int *res;
  res = decimalToBin(test);
  //int num = res;
  for(i=0; i<2; i++){
    printf("%d\n", res[i]);
  }
  int j=0;
  int w4[4];
  int w3[4];
  int w2[4];
  int w[4];
  int w4_count, w3_count, w2_count, w_count;

  printf("chunk loops");
  //for(j=0; j<16; j++){
    for(w4_count=0; w4_count<4; w4_count++){
      printf("%d\n", res[j]);
      w4[w4_count] = res[j];
      j++;
    }
    printf("w4 stopped\n");
    for(w3_count=0; w3_count<4; w3_count++){
      w3[w3_count] = res[j];
      j++;
    }
    for(w2_count=0; w2_count<4; w2_count++){
      w2[w2_count] = res[j];
      j++;
    }
    for(w_count=0; w_count<4; w_count++){
      w[w_count] = res[j];
      j++;
    }
  //}
  printf("");
  for(int i=0; i<4; i++){
    printf("%d\n", w4[i]);
  }
  int w_big[16];
  printf("big loop -start\n");
  int h=0;
  for(h=0; h<16; h++){
    w_big[h] = res[h];
    printf("%d\n", w_big[h]);
  }

  //2. round function







}
int SubBytes(int[] input){
  //GF(2^8)
  //S-box
}








//convert input to State (use for)
int *decimalToBin(int dec){
  int bi[32];
  int i;

  int temp = dec;
  for(i=0; i<dec; i++){
    bi[i] = temp % 2;
    temp = temp/2;
    printf("%d\n", bi[i]);
  }
  return bi;

}
