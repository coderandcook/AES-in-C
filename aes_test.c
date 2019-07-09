#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "div_generic.h"
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "MixColumns.h"
#include "AddRoundKey3.h"
#include "KeyExpansion.h"
#include "cipher.h"
#include "InvShiftRows.h"
#include "InvSubBytes.h"
#include "InvMixColumns.h"

#define TEST_EQUAL(x, y) if ((x) != (y)) printf("ERR " #x "!=" #y "\n");
#define TEST_ASSERT(x) if (!(x)) printf("ERR " #x "\n");
int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}


/*
void test_SubBytes(){
	int exp2[] = {0,0,0,1,0,0,0,1};
	int input[] = {1,1,1,0,0,0,1,1};
	int res[8]; clear8(res);
	SubBytes(input, res);
	TEST_ASSERT(isEqualPoly(res, exp2));
}


void test_crossMul(){
	int exp[]= {1,0,0,0,1,1,1,0};
	int input[] = {1,1,0,0,1,0,1,0};
	int multiplier[] = {1,1,1,1,1,0,0,0};
	int output[8]; clear8(output);
	crossMul(input, multiplier, output);

	TEST_ASSERT(isEqualPoly(output, exp));
}

void test_div_generic(){
	int m[] = {1,0,0,0,1,1,0,1,1};
	int poly[] = {0,1,0,1,0,0,1,1};
	int remainder[8]; clear8(remainder);
	int q[8]; clear8(q);
	//int dividend[8]; clear(dividend);

	int exp_q[] = {0,0,0,0,0,1,0,1};
	int exp_rem[] = {0,0,0,0,0,1,0,0};
	div_generic(m, 9, poly, q, remainder);
	//clear(q);
	TEST_ASSERT(isEqualPoly(q, exp_q));
	TEST_ASSERT(isEqualPoly(remainder, exp_rem));

}
void test_substate(){
	struct state *s = newState();
	struct state *s2 = newState();
	struct state *exp = newState();

	setState(0,0,0x32,s);
	setState(1,0,0x43,s);
	setState(2,0,0xf6,s);
	setState(3,0,0xa8,s);

	setState(0,1,0x88,s);
	setState(1,1,0x5a,s);
	setState(2,1,0x30,s);
	setState(3,1,0x8d,s);

	setState(0,0,0x23,exp);
	setState(1,0,0x1a,exp);
	setState(2,0,0x42,exp);
	setState(3,0,0xc2,exp);

	setState(0,1,0xc4,exp);
	setState(1,1,0xbe,exp);
	setState(2,1,0x04,exp);
	setState(3,1,0x5d,exp);

	SubState(s,s2);

	printState(s2);
	printf("\n");
	printState(exp);
}*/



void test_keyexpansion(){
	int i,k;
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	key->block[0][0] = 0x2b;
	key->block[0][1] = 0x7e;
	key->block[0][2] = 0x15;
	key->block[0][3] = 0x16;

	key->block[1][0] = 0x28;
	key->block[1][1] = 0xae;
	key->block[1][2] = 0xd2;
	key->block[1][3] = 0xa6;

	key->block[2][0] = 0xab;
	key->block[2][1] = 0xf7;
	key->block[2][2] = 0x15;
	key->block[2][3] = 0x88;

	key->block[3][0] = 0x09;
	key->block[3][1] = 0xcf;
	key->block[3][2] = 0x4f;
	key->block[3][3] = 0x3c;



	//first four words must be the same as first four in key
	KeyExpansion(key, ekey);

	for(i=0; i<44; i++){//i<4
		for(k=0; k<4; k++) printf("%x ", ekey->wordList[i][k]);
		printf("\n");
	}
}
/*
void test_addroundkeyG(){
	struct state *s = newState();
	struct expKey *ekey = newekey();
	int i=4;
	uint8_t w[] = {0xa0,0xfa,0xfe,0x17};
	uint8_t w2[] = {0x88,0x54,0x2c,0xb1};
	uint8_t w3[] = {0x23,0xa3,0x39,0x39};
	uint8_t w4[] = {0x2a,0x6c,0x76,0x05};

	CopyWord(w,ekey->wordList[4]);
	CopyWord(w2,ekey->wordList[5]);
	CopyWord(w3,ekey->wordList[6]);
	CopyWord(w4,ekey->wordList[7]);

	AddRoundKey_generic(s,ekey,i);//data from ekey is copied to s
	i=0; int k;
	for(i=0; i<4; i++){
		for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
		printf("\n");
	}
}
void test_setkey(){
	uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	struct key *k = newKey();
	setKey(k,in);
	int i,j;
	for(i=0; i<4; i++){
		for(j=0; j<4; j++) printf("%x ",k->block[i][j]);
		printf("\n");
	}
}
*/
/*
void test_mixcolumns(){
	struct state *s = newState();
	setState(0,0,0xd4,s);
	setState(0,1,0xe0,s);
	setState(0,2,0xb8,s);
	setState(0,3,0x1e,s);

	setState(1,0,0xbf,s);
	setState(1,1,0xb4,s);
	setState(1,2,0x41,s);
	setState(1,3,0x27,s);

	setState(2,0,0x5d,s);
	setState(2,1,0x52,s);
	setState(2,2,0x11,s);
	setState(2,3,0x98,s);

	setState(3,0,0x30,s);
	setState(3,1,0xae,s);
	setState(3,2,0xf1,s);
	setState(3,3,0xe5,s);

	MixColumns(s);

	int i,k;
	for(i=0; i<4; i++){
		for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
		printf("\n");
	}
}
void test_subbytes(){
	struct state *s = newState();
	setState(0,0,0x19,s);
	setState(0,1,0xa0,s);
	setState(0,2,0x9a,s);
	setState(0,3,0xe9,s);

	setState(1,0,0x3d,s);
	setState(1,1,0xf4,s);
	setState(1,2,0xc6,s);
	setState(1,3,0xf8,s);

	setState(2,0,0xe3,s);
	setState(2,1,0xe2,s);
	setState(2,2,0x8d,s);
	setState(2,3,0x48,s);

	setState(3,0,0xbe,s);
	setState(3,1,0x2b,s);
	setState(3,2,0x2a,s);
	setState(3,3,0x08,s);

	SubState(s,s);
	int i,k;
	for(i=0; i<4; i++){
		for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
		printf("\n");
	}
}*/


void test_cipher(){
	//int i,k;
	struct key *key = newKey();
	struct expKey *ekey = newekey();
	/*
	key->block[0][0] = 0x2b;
	key->block[0][1] = 0x7e;
	key->block[0][2] = 0x15;
	key->block[0][3] = 0x16;

	key->block[1][0] = 0x28;
	key->block[1][1] = 0xae;
	key->block[1][2] = 0xd2;
	key->block[1][3] = 0xa6;

	key->block[2][0] = 0xab;
	key->block[2][1] = 0xf7;
	key->block[2][2] = 0x15;
	key->block[2][3] = 0x88;

	key->block[3][0] = 0x09;
	key->block[3][1] = 0xcf;
	key->block[3][2] = 0x4f;
	key->block[3][3] = 0x3c;
	*/
	key->block[0][0] = 0x00;
	key->block[0][1] = 0x01;
	key->block[0][2] = 0x02;
	key->block[0][3] = 0x03;

	key->block[1][0] = 0x04;
	key->block[1][1] = 0x05;
	key->block[1][2] = 0x06;
	key->block[1][3] = 0x07;

	key->block[2][0] = 0x08;
	key->block[2][1] = 0x09;
	key->block[2][2] = 0x0a;
	key->block[2][3] = 0x0b;

	key->block[3][0] = 0x0c;
	key->block[3][1] = 0x0d;
	key->block[3][2] = 0x0e;
	key->block[3][3] = 0x0f;
	//first four words must be the same as first four in key
	KeyExpansion(key, ekey);

	//uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	uint8_t in[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	uint8_t out[16]; //clear_generic(out,16);

	cipher(in,out,ekey);

	int i;
	for(i=0; i<16; i++) printf("%x ",out[i]);
	printf("\n");
}

void test_invshiftright(){
	struct state *s = newState();

	setState(0,0,0x1,s);
	setState(0,1,0x2,s);
	setState(0,2,0x3,s);
	setState(0,3,0x4,s);

	setState(1,0,0x1,s);
	setState(1,1,0x2,s);
	setState(1,2,0x3,s);
	setState(1,3,0x4,s);

	setState(2,0,0x1,s);
	setState(2,1,0x2,s);
	setState(2,2,0x3,s);
	setState(2,3,0x4,s);

	setState(3,0,0x1,s);
	setState(3,1,0x2,s);
	setState(3,2,0x3,s);
	setState(3,3,0x4,s);

	InvShiftRows(s);

	printState(s);
}

void test_invsb(){
	struct state *s = newState();

	setState(0,0,0x7a,s);
	setState(0,1,0x9f,s);
	setState(0,2,0x10,s);
	setState(0,3,0x27,s);

	setState(1,0,0x89,s);
	setState(1,1,0xd5,s);
	setState(1,2,0xf5,s);
	setState(1,3,0x0b,s);

	setState(2,0,0x2b,s);
	setState(2,1,0xef,s);
	setState(2,2,0xfd,s);
	setState(2,3,0x9f,s);

	setState(3,0,0x3d,s);
	setState(3,1,0xca,s);
	setState(3,2,0x4e,s);
	setState(3,3,0xa7,s);

	InvSubState(s,s);

	/*
	int i,k;
	for(i=0; i<4; i++){
		for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
		printf("\n");
	}*/
	printState(s);
}

void test_invmc(){
	struct state *s = newState();
	setState(0,0,0xbd,s);
	setState(0,1,0x6e,s);
	setState(0,2,0x7c,s);
	setState(0,3,0x3d,s);

	setState(1,0,0xf2,s);
	setState(1,1,0xb5,s);
	setState(1,2,0x77,s);
	setState(1,3,0x9e,s);

	setState(2,0,0x0b,s);
	setState(2,1,0x61,s);
	setState(2,2,0x21,s);
	setState(2,3,0x6e,s);

	setState(3,0,0x8b,s);
	setState(3,1,0x10,s);
	setState(3,2,0xb6,s);
	setState(3,3,0x89,s);

	InvMixColumns(s);

	printState(s);
}

void test_cmgeneric(){
	/*
	uint8_t col[] = {0xbd,0xf2,0x0b,0x8b};
	uint8_t mp[] = {0x0e,0x0b,0x0d,0x09};
	uint8_t ans=0;*/

	//ans = colMultiply_generic(col,mp);

	int poly[] = {1,0,0,0,1,1,1,0};
	int ans=0;
	ans = xtime(poly);
	printf("ans = %d\n",ans);
	int i;
	for(i=0; i<8; i++) printf("%d",poly[i]);
	printf("\n\n");

	int poly2a[] = {1,0,1,1,1,1,0,1};
	int poly2b[] = {0,0,0,0,1,1,1,0};
	mul2(poly2a,poly2b);
	for(i=0; i<8; i++) printf("%d",poly2a[i]);
	printf("\n");

	int dividend[] = {0,0,0,0,1,1,0,0,1,1,0,0,1,1,0};
	//int dividend_size = 15;
	int size = 15;
	int byte[8]; clear8(byte);
	mod8(dividend,size,byte);

	printPoly(byte);
}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	//test_invsb();
	//test_invmc();
	test_cmgeneric();

}
