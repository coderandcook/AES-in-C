#include <stdio.h>
#include <math.h>
#include "poly.h"
#include "div_generic.h"
#include "mod3.h"


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
/*
int setInt(int *bin){//getInt
  int i;
  int result = 0;
  int temp;
  for(i=0; i<8; i++){
    temp = pow(2,7-i)/1;
    result += temp*bin[i];
  }
  return result;
}*/
int getInt(int *poly){
  int i;
  int result = 0;
  int temp;
  for(i=0; i<8; i++){
    temp = pow(2,7-i)/1;
    result += temp*poly[i];
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
void addPoly_generic(int *poly1, int poly1_size, int *poly2, int poly2_size, int *output){
  int m[] = {1,0,0,0,1,1,0,1,1};
  int temp_size=0;
  int i;
  int diff;

  if(poly1_size>poly2_size){
    temp_size = poly1_size +1;
  }
  else{
    temp_size = poly2_size+1;
  }
  int temp_poly[temp_size]; clear_generic(temp_poly,temp_size);
  copy_generic(poly2,temp_poly,temp_size);

  diff = temp_size-poly1_size;

  for(i=poly1_size; i>=0; i--){
    temp_poly[i] = temp_poly[i+diff]+poly1[i];
    if(temp_poly[i]>=0) temp_poly[i] = temp_poly[i]%2;
    else if(temp_poly[i]==-1) temp_poly[i] = 1;
  }
  while(i>=0){
    temp_poly[i] = 0;
    i--;
  }
  mod2(m,temp_poly,temp_size, output);

  /*
  int diff1 = temp_size-poly1_size;//5
  int diff2 = temp_size-poly2_size;//1
  for(i=temp_size-1; i>=0; i--){
    temp_poly[i] = poly1[i-diff1]+poly2[i-diff2];
  }
  */

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
/*
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
}*/
void mul2(int *poly, int *poly2){//output is size 15
  int i,k,degree=0;
  int m[] = {1,0,0,0,1,1,0,1,1};
  int temp[15]; clear_generic(temp,15);
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
    if(temp[i]>=0) temp[i] = temp[i]%2;
    else if(temp[i]==-1)temp[i]=1;
  }
  mod2(m,temp,15,poly);
}

int isEqualPoly(int *poly1, int *poly2){
  int i;
  for(i=0; i<8; i++) {
    if(poly1[i]!=poly2[i]) return 0;
  }
  return 1;
}
