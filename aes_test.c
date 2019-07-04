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
//#include "KeyExpansion.h"

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

	for(i=0; i<44; i++){
		for(k=0; k<4; k++) printf("%x ", ekey->wordList[i][k]);
		printf("\n");
	}
}
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
	/*
	CopyWord(w,s->block[0]);
	CopyWord(w2,s->block[1]);
	CopyWord(w3,s->block[2]);
	CopyWord(w4,s->block[3]);
	*/
	AddRoundKey_generic(s,ekey,i);//data from ekey is copied to s
	i=0; int k;
	for(i=0; i<4; i++){
		for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
		printf("\n");
	}

}






int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);
	test_addroundkeyG();


}
