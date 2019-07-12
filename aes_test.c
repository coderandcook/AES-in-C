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
#include "InvCipher.h"
#include "shifter.h"

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


void test_cipher(){
	//int i,k;
	struct key *key = newKey();
	struct expKey *ekey = newekey();

	uint8_t keyarray[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	setKey(key,keyarray);
	//first four words must be the same as first four in key
	KeyExpansion(key, ekey);
	printekey(ekey,0,43);

	uint8_t in[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	//uint8_t in[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};

	uint8_t out[16]; //clear_generic(out,16);
	uint8_t out2[16];

	cipher(in,out,ekey);
	int i;
	for(i=0; i<16; i++) printf("%x ",out[i]);
	printf("\n");

	invCipher(out,out2,ekey);
	printf("inv: ");
	for(i=0; i<16; i++) printf("%x ",out2[i]);
	printf("\n");
}
void test_setpoly(){
	int poly[8];
	setPoly(8,poly);

	int i;
	for(i=0; i<8; i++) printf("%d",poly[i]);
	printf("\n");
}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	test_cipher();
	//test_setpoly();
}
