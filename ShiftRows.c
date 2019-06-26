#include <stdio.h>
#include <math.h>
void ShiftRows(int *input);

int main(){
  int i;
  int state[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};
  ShiftRows(state);
  for(i=0; i<16; i++){
    printf("%d ", state[i]);
  }
  printf("\n\n");

}
void ShiftRows(int *input){
  int row, k, i, s;
  int temp;
  for(row = 0; row<4; row++){
    printf("row%d: ", row);
    //temp = *(input+row*4);
    for(k=0; k<row; k++){//shift row0 0times, row1 1time, row2 2times

      //individual shift
      temp = *(input+row*4);
      for(s=0; s<3; s++){
        int t = row*4+s;
        *(input+t) = *(input+t+1);
      }
      *(input+row*4+3) = temp;
    }
    printf("\n");

  }
  for(i=0; i<16; i++){
    printf("%d ", *(input++));
  }
  printf("\n\n");
}
