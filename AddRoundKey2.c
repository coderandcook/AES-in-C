#include <stdio.h>
#include <math.h>
void AddRoundKey(int *dest, int message);
int SubBytes(int input);
int main(){
  int result[16];
  int message = 4;
  AddRoundKey(result, message);
  int i;
  for(i=0; i<16; i++){
    printf("%d ", result[i]);
  }
  printf("\n\n");

  printf("expected ans: %f\n", pow(2,7)+pow(2,6)+pow(2,5)+pow(2,4)+pow(2,2)+pow(2,0));
  int r = SubBytes(4);
  printf("ans: %d\n", r);

}
//transform message in decimal to binary (list form)
void AddRoundKey(int *dest, int message){
  int i;
  int num = message;
  for(i=0; i<16; i++){
    *(dest++) = num%2;
    num = num/2;
  }
}

int SubBytes(int input){
  int i;
  int result;
  int num = input;
  int c;
  int new_mul=0;
  //int mul = 4;
  int mul = (pow(2,7)+pow(2,3)+pow(2,2)+pow(2,1)+1)/1;
  for(i=8; i>0; i--){
    c = mul%2;
    mul = mul/2;
    new_mul += c*pow(2, i-1);
  }
  printf("%d\n", new_mul);

  result = new_mul^input;

  return result;
}
