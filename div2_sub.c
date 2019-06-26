//edit updateRemainder
//apply the functions below to the whole div

#include <stdio.h>
#include <math.h>
void clear(int *poly);
void copy(int *poly, int *poly2);
int findDeg(int *poly);
void updateRemainder(int *remainder, int *divisor, int new_q);
int updateQ(int *quotient, int reDeg, int dDeg);
int main(){
  int i;
  int divisor[] = {0,0,0,0,0,1,0,1};
  int dividend[] = {0,0,1,0,0,0,1,1};
  int quotient[]={0,0,0,0,0,0,0,0};
  int remainder[]={0,0,1,0,0,0,1,1};
  /*
  clear(divisor);
  for(i=0; i<8; i++){
    printf("%d", divisor[i]);
  }printf("\n");
  */

  int dDeg = findDeg(divisor); printf("dDeg = %d\n", dDeg);//2
  int reDeg = findDeg(dividend); printf("reDeg = %d\n", reDeg);//5

  int num = updateQ(quotient, reDeg, dDeg);
  printf("quotient\n");
  for(i=0; i<8; i++){
    printf("%d", quotient[i]);
  }printf("\n");
  printf("num = %d\n\n", num);

  //update remainder
  updateRemainder(remainder, divisor, num);
  for(i=0; i<8; i++){
    printf("%d", remainder[i]);
  }
  printf("\n\n");



  //(x^2+1)/(x) = x...1
  //dividend = {0,0,0,0,0,1,0,1}; divisor = {0,0,0,0,0,0,1,0};
  //quotient = {0,0,0,0,0,0,1,0}; remainder = {0,0,0,0,0,0,0,1};
  int dividend2[] = {0,0,0,0,0,1,0,1};
  int divisor2[] = {0,0,0,0,0,0,1,0};
  int q2[8], remainder2[8];
  clear(q2); clear(remainder2); copy(dividend2, remainder2);
  int new_q2 = 0;
  int rDeg2 = findDeg(dividend2), dDeg2 = findDeg(divisor2);

  printf("degree of dividend2 = %d\ndegree of divisor2 = %d\n", rDeg2, dDeg2);
  new_q2 = updateQ(q2, rDeg2, dDeg2);
  printf("new_q2 = %d\n", new_q2);

  for(i=0; i<8; i++) printf("%d", remainder2[i]);
  printf("\n");
  updateRemainder(remainder2, divisor2, new_q2);
  for(i=0; i<8; i++) printf("%d", remainder2[i]);
  printf("\n");


}
//poly length of 8
void clear(int *poly){
  int i=0;
  for(i=0; i<8; i++){
    poly[i]=0;
  }
}
void copy(int *poly, int *poly2){
  int i;
  for(i=0; i<8; i++){
    *(poly2++) = *(poly++);
  }
}
int findDeg(int *poly){
  int i=0;
  for(i=0; i<8; i++){
    if(poly[i]==1) return 7-i;
  }
  return -1;
}
void updateRemainder(int *remainder, int *divisor, int new_q){//subtract divisor*(one time quotient) from remainder
  //temp[] = divisor*(one time quotient)  loop through divisor. When there is 1, shift that by degree(new_q)

  //loop through 0~7. remainder[i]-temp[i]. change other than 0,1

  //return remainder
  int i,t;
  int temp[] = {0,0,0,0,0,0,0,0};
  for(i=0; i<8-new_q; i++){
    temp[i]=divisor[i+new_q];
  }
  for(i=0; i<8; i++){
    t = remainder[i]-temp[i];
    //change t
    if(t>=0) t=t%2;
    else if(t==-1) t=1;
    remainder[i]=t;
  }


/*
  divisor = {0,0,0,0,0,1,0,1};
  remainder = {0,0,1,0,0,0,1,1};
  new_q = 3;

  temp = {0,0,1,0,1,0,0,0}; remainder = {0,0,0,0,-1,0,1,1}; remainder = {0,0,0,0,1,0,1,1};
  */

}




//returns degree of new quotient
//reDeg is the degree of remainder, dDeg is the degree of divisor
int updateQ(int *quotient, int reDeg, int dDeg){
  int i;
  int new_q = reDeg-dDeg;
  if(new_q<0) return -1;
  quotient[7-new_q]++;

  quotient[7-new_q] = quotient[7-new_q]%2;
  return new_q;
}
