#include <stdio.h>
#include <math.h>
#include "poly.h"
#include "div_generic.h"


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
void mulPoly(int *poly, int *poly2){
  int temp[15]; clear_generic(temp, 15);//0->14   14->0
  int i,k;
  int degree=0;
  for(i=0; i<8; i++){
    for(k=0; k<8; k++){
      if(poly[i]==1 && poly2[k]==1){
        degree = (7-i)+(7-k);
        degree = 14-degree;
        temp[degree]++;
      }
    }
  }
  for(i=0; i<15; i++){
    if(temp[i]>=0) temp[i]=temp[i]%2;
    else if(temp[i]==-1) temp[i]=1;
  }
  for(i=14; i>=7; i--) poly[i-7]=temp[i];
}





void mulPoly2(int *binary, int *binary2){
  int i;
  for(i=0; i<8; i++){
    binary[i] = binary[i]*binary2[i];
  }
}

int isEqualPoly(int *poly1, int *poly2){
  int i;
  for(i=0; i<8; i++) {
    if(poly1[i]!=poly2[i]) return 0;
  }
  return 1;
}
