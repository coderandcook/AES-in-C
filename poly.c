#include <stdio.h>
#include <math.h>
#include "poly.h"
#include "div_poly.h"
#include "div_generic.h"
#include "mod3.h"


//sets decimal to polynomial
void setPoly(int num, int *poly){//2^7 is bin[0]
  //0 ~ 7
  int i;
  int temp;

  clear8(poly);
  for(i = 0; i<8; i++){
    temp = pow(2,7-i)/1;
    poly[i] = num / temp;
    num = num - poly[i]*temp;
  }
}
int getInt(const int *poly){
  int i;
  int result = 0;
  int temp;
  for(i=0; i<8; i++){
    temp = pow(2,7-i)/1;
    result += temp*poly[i];
  }
  return result;
}
//doesn't take mod
void addPoly(int *poly, const int *poly2){
  int i;
  int temp;
  for(i=0; i<8; i++){
    temp = poly[i]+poly2[i];
    poly[i] = temp%2;
  }
}
//takes mod
void addPoly_generic(const int *poly1, int poly1_size, const int *poly2, int poly2_size, int *output){
  int temp_size=0;
  int i;
  int diff;
  int t=0,prev=0;

  clear8(output);
  //set make a temporary array (size of bigger array)
  if(poly1_size>poly2_size) temp_size = poly1_size +1;
  else temp_size = poly2_size+1;
  int temp_poly[temp_size]; clear_generic(temp_poly,temp_size);
  //copy poly2 to temp_poly
  copy_generic2(poly2,poly2_size,temp_poly,temp_size);

  diff = temp_size-poly1_size;
  for(i=temp_size-1; i>=diff; i--){
    t = temp_poly[i]+poly1[i-diff]+prev;
    if(t>=0){
      prev = t/2;
      t = t%2;
      temp_poly[i] = t;
    }
  }
  temp_poly[i] = prev; i--;
  while(i>=0){
    temp_poly[i] = 0;
    i--;
  }
  mod(temp_poly,temp_size,output);
}

void subPoly(int *poly, const int *poly2){
  int i;
  int temp=0;
  for(i=0; i<8; i++){
    temp = poly[i]-poly2[i];

    if(temp==-1) poly[i] = 1;
    else poly[i] = temp%2;
  }
}
void mulPoly(int *poly, const int *poly2){
  int i,k,degree=0;
  int temp[15]; clear_generic(temp,15);
  for(i=0; i<8; i++){
    for(k=0; k<8; k++){
      if(poly[i]==1 && poly2[k]==1){
        //degree = (7-i)+(7-k);
        degree = 14- (7-i)-(7-k);
        temp[degree]++;
      }
    }
  }
  for(i=0; i<15; i++){
    if(temp[i]==-1)temp[i]=1;
    else temp[i] = temp[i]%2;
  }
  mod(temp,15,poly);
}

int isEqualPoly(const int *poly1, const int *poly2){
  int i;
  for(i=0; i<8; i++) {
    if(poly1[i]!=poly2[i]) return 0;
  }
  return 1;
}
