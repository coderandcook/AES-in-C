//crosswise multiplication and additon
#include <stdio.h>
#include <math.h>
#include "mod3.c"
void crossMul(int *input, int *output);
int SubBytes(int *input, int *output);

int main(){
  int i;
  //test1

  int input[] = {0,1,0,1,0,0,1,1};
  int output[8]; clear(output);
  int result = 0;

  result = SubBytes(input, output);
  printf("result = %d\n", result);
  printf("inverse: ");
  for(i=0; i<8; i++) printf("%d", output[i]);
  printf("\n");


}

if(t>=0) t = t%2;
else if(t==-1) t=1;

void crossMul(int *input, int *output){
  int i, k;
  int temp, temp2=0;
  int multiplier[] = {1,1,1,1,1,0,0,0};

  for(i=0; i<8; i++){
    temp=0;
    for(k=0; k<8; k++){
      temp+=multiplier[k]*input[i];
    }
    if(temp>=0) temp=temp%2;
    else if(temp==-1)temp=1;
    output[i]=temp;
    //change multiplier
    temp2 = multiplier[0];
    multiplier[0] = multiplier[7];
    multiplier[7] = temp2;
  }
}

int SubBytes(int *input, int *output){
  int i;
  int dec_result = 0;

  //take mod of input
  int m[] = {1,0,0,0,1,1,0,1,1};
  int q[8]; clear(q);
  int rem[8]; clear(rem);
  int arr_result[8]; clear(arr_result);
  dec_result = mod(m, input, q, rem, arr_result);

  //crosswise multiplication
  int temp[8]; copy(arr_result, temp);
  int multiplier[] = {1,1,1,1,1,0,0,0};

  mulPoly(temp, multiplier);
  for(i=0; i<8; i++) printf("%d", temp[i]);
  printf("\n");

  //crosswise addition


  return dec_result;
}
