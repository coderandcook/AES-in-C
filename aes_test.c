#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "div_generic.h"
#include "SubBytes2.h"
//#include "ShiftRows2.h"
#include "MixColumns.h"
#include "AddRoundKey3.h"
#include "KeyExpansion.h"

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
void test_addroundkey(){
	struct state *s = newState();
	setState(0,0,0x32,s);
	setState(1,0,0x43,s);
	setState(2,0,0xf6,s);
	setState(3,0,0xa8,s);
	setState(0,1,0x88,s);
	setState(1,1,0x5a,s);
	setState(2,1,0x30,s);
	setState(3,1,0x8d,s);

	struct state *key = newState();
	setState(0,0,0x2b,key);
	setState(1,0,0x7e,key);
	setState(2,0,0x15,key);
	setState(3,0,0x16,key);
	setState(0,1,0x28,key);
	setState(1,1,0xae,key);
	setState(2,1,0xd2,key);
	setState(3,1,0xa6,key);

	AddRoundKey(s,key);

	struct state *exp = newState();
	setState(0,0,0x19,exp);
	setState(1,0,0x3d,exp);
	setState(2,0,0xe3,exp);
	setState(3,0,0xbe,exp);
	setState(0,1,0xa0,exp);
	setState(1,1,0xf4,exp);
	setState(2,1,0xe2,exp);
	setState(3,1,0x2b,exp);

	TEST_ASSERT(isEqualState(s,exp));
}

void test_setstate(){
	struct state *s1 = newState();
	int row = 3;
	int col = 3;
	uint8_t new = 0xff;
	setState(row, col, new, s1);
	setState(0,0,0x01, s1);
	clearState(s1);
	printState(s1);
}
void test_colmultiply(){
	uint8_t col[] = {0xd4, 0xbf, 0x5d, 0x30};
	uint8_t mul[] = {0x01, 0x02, 0x03, 0x01};
	uint8_t res;
	res = colMultiply(col, mul);
	printf("res: %d\n", res);

	//TEST_ASSERT(isEqualCol(newCol, exp));
}

void test_mixcolumns(){
	struct state *s = newState();
	setState(0,0,0xd4,s);
	setState(1,0,0xbf,s);
	setState(2,0,0x5d,s);
	setState(3,0,0x30,s);

	setState(0,1,0xe0,s);
	setState(1,1,0xb4, s);
	setState(2,1,0x52, s);
	setState(3,1,0xae,s);

	MixColumns(s);

	struct state *s2 = newState();
	setState(0,0,0x04,s2);
	setState(1,0,0x66,s2);
	setState(2,0,0x81,s2);
	setState(3,0,0xe5,s2);

	setState(0,1,0xe0,s2);
	setState(1,1,0xcb,s2);
	setState(2,1,0x19,s2);
	setState(3,1,0x9a,s2);

	TEST_ASSERT(isEqualState(s,s2));
}

void test_shiftrows(){

	struct state* s1 = newState();
	s1->block[0][0] = 0x00;
	s1->block[0][1] = 0x02;
	s1->block[0][2] = 0x04;
	s1->block[0][3] = 0x06;

	s1->block[1][0] = 0x02;
	s1->block[1][1] = 0x04;
	s1->block[1][2] = 0x06;
	s1->block[1][3] = 0x00;

	s1->block[2][0] = 0x04;
	s1->block[2][1] = 0x06;
	s1->block[2][2] = 0x00;
	s1->block[2][3] = 0x02;

	s1->block[3][0] = 0x06;
	s1->block[3][1] = 0x00;
	s1->block[3][2] = 0x02;
	s1->block[3][3] = 0x04;

	struct state* s2 = newState();
	s2->block[0][0] = 0x00;
	s2->block[0][1] = 0x02;
	s2->block[0][2] = 0x04;
	s2->block[0][3] = 0x06;

	s2->block[1][0] = 0x00;
	s2->block[1][1] = 0x02;
	s2->block[1][2] = 0x04;
	s2->block[1][3] = 0x06;

	s2->block[2][0] = 0x00;
	s2->block[2][1] = 0x02;
	s2->block[2][2] = 0x04;
	s2->block[2][3] = 0x06;

	s2->block[3][0] = 0x00;
	s2->block[3][1] = 0x02;
	s2->block[3][2] = 0x04;
	s2->block[3][3] = 0x06;

	ShiftRows(s2);

	TEST_ASSERT(isEqualState(s1, s2));
}

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
void test_mul(){
	int exp[] = {1,1,0,0,1,0,0,1};
	int poly1[] = {0,0,1,1,1,1,0,1};
	int poly2[] = {0,0,0,0,0,1,0,1};
	mulPoly(poly1, poly2);
	TEST_ASSERT(isEqualPoly(poly1, exp));
}
void test_addPoly(){
	int poly1[] = {0,0,0,1,0,1,0,0};
	int poly2[] = {0,0,1,0,1,0,0,0};
	int expected[] = {0,0,1,1,1,1,0,0};
	addPoly(poly1, poly2);
	TEST_ASSERT(isEqualPoly(poly1, expected));
	clear8(poly1);
}
*/
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
}
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

	for(i=0; i<44; i++){
		for(k=0; k<4; k++) printf("%x ", ekey->wordList[i][k]);
		printf("\n");
	}

}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);
	//test_shiftrows();
	//test_keyexpansion();
	test_keyexpansion();
}
