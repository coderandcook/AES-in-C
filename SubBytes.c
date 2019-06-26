#include <stdio.h>
#include <math.h>
int SubBytes(int input);
int SuBytes_2(int input);

int main(){
  int r = SubBytes(4);
  printf("SubBytes(4)\n");
  printf("ans: %d\n", r);

  //printf("expected ans: %f\n", pow(2,7)+pow(2,6)+pow(2,5)+pow(2,4)+pow(2,2)+pow(2,1));
  int r2 = SubBytes(7);
  printf("SubBytes(7)\n");
  printf("ans: %d\n", r2);

  int r3 = SubBytes(0);
  printf("SubBytes(0)\n");
  printf("ans: %d\n", r3);


}
int SubBytes(int input){
  int i,k;
  int bit_result, temp_result, result=0;
  int num = input;
  int c, c2, prev_c, c3;
  int new_mul=0;

  //1. transform multiplier (significance of bits)
  /*
  for(i=8; i>0; i--){
    c = mul%2;
    mul = mul/2;
    new_mul += c*pow(2, i-1);
  }
  */


  //2. transform multiplier 8 times in total
  new_mul = pow(2,7)+pow(2,6)+pow(2,5)+pow(2,4)+pow(2,3);//i=-1 state of multiplier
  for(i=0; i<8; i++){
    int temp = pow(2,7)/1;

    //value of the most significant bit
    c2 = new_mul/temp;
    new_mul = new_mul%temp*2+c2;

    //^ operation
    temp_result = new_mul^input;
    printf("i=%d temp_result=%d ", i, temp_result);

    prev_c = temp_result%2;//bit value to compare
    temp_result = temp_result/2;
    printf("%d", prev_c);
    //& operation
    for(k=1; k<8; k++){
      c = temp_result%2;
      temp_result = temp_result/2;
      printf("%d", c);

      //prev_c = c^prev_c;
      prev_c = c&prev_c;
    }//now prev_c is bit_result
    printf(" final bit value: %d\n\n", prev_c);
    result += prev_c*pow(2,i);

  }
  return result;
}
int SuBytes_2(int input){






  return 0;
}
//test & operation
