#include <stdio.h>
#include <math.h>
#include "poly.h"


/*
int main(){
  int i;

  printf("mulPoly\n");
  int q[] = {0,0,0,1,0,1,0,0};
  int pre_b[] = {0,0,0,0,0,0,1,1};
  int pre_c[] = {0,0,0,0,0,0,0,1};
  //mulPoly(q,pre_b);
  //addPoly(q, pre_c);

  printPoly(q);
  printPoly(pre_b);
  printPoly(pre_c);
}*/


//sets decimal to polynomial
void setPoly(int num, int *bin){//2^7 is bin[0]
  //0 ~ 7
  int i;
  int temp;
  for(i = 0; i<8; i++){
    temp = pow(2,7-i)/1;
    bin[i] = num / temp;
    num = num - bin[i]*temp;
  }
}
int setInt(int *bin){
  int i;
  int result = 0;
  int temp;

  for(i=0; i<8; i++){
    temp = pow(2,7-i)/1;
    result += temp*bin[i];
  }
  return result;
}




//-1 becomes 1, 2 becomes 0
void addPoly(int *binary, int *binary2){
  int i;
  int temp;
  for(i=0; i<8; i++){
    temp = binary[i]+binary2[i];
    if(temp == 2) binary[i]=0;
    else if(temp==-1) binary[i]=1;
    else binary[i]=temp;
  }
}
void subPoly(int *binary, int *binary2){
  int i;
  int temp;
  for(i=0; i<8; i++){
    temp = binary[i]-binary2[i];
    if(temp==2) binary[i]=0;
    else if(temp==-1) binary[i]=1;
    else binary[i]=temp;
  }
}

void mulPoly(int *binary, int *binary2){
  int i,k;
  int ans[15];
  for(i=0; i<15; i++)ans[i]=0;

  for(i=0; i<8; i++){
    for(k=0; k<8; k++){
      ans[i+k] += binary[i]*binary2[k];
    }
  }

  for(i=0; i<15; i++){
    if(ans[i]>1) ans[i]=ans[i]%2;
    else if(ans[i]==-1) ans[i]=1;
  }
  for(i=7; i>=0; i--){
    binary[i] = ans[7+i];
  }
}

int isEqualPoly(int *poly1, int *poly2){
  int i;
  for(i=0; i<8; i++) {
    if(poly1[i]!=poly2[i]) return 0;
  }
  return 1;
}
