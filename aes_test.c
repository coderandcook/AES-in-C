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
#include "bit.h"

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

void test_cipher2(){
	uint8_t keyarray1[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	uint8_t input1[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	uint8_t output1[16]; uint8_t temp_output1[16];

	uint8_t keyarray2[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	uint8_t input2[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	uint8_t output2[16]; uint8_t temp_output2[16];

	struct key *key1 = newKey(); setKey(key1,keyarray1);
	struct expKey *ekey1 = newekey(); KeyExpansion(key1,ekey1);
	cipher(input1,temp_output1,ekey1);
	uint8_t exp1[] = {0x39,0x25,0x84,0x1d,0x02,0xdc,0x09,0xfb,0xdc,0x11,0x85,0x97,0x19,0x6a,0x0b,0x32};

	TEST_ASSERT(isEqualMessage(exp1,temp_output1));
	/*
	int i;
	for(i=0; i<16; i++) printf("%x ",temp_output1[i]);
	printf("\n");*/
	invCipher(temp_output1,output1,ekey1);
	uint8_t exp2[] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};
	TEST_ASSERT(isEqualMessage(exp2,output1));
	/*
	for(i=0; i<16; i++) printf("%x ",output1[i]);
	printf("\n");*/

	struct key *key2 = newKey(); setKey(key2,keyarray2);
	struct expKey *ekey2 = newekey(); KeyExpansion(key2,ekey2);
	cipher(input2,temp_output2,ekey2);
	uint8_t exp3[] = {0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a};
	TEST_ASSERT(isEqualMessage(exp3,temp_output2));
	/*
	for(i=0; i<16; i++) printf("%x ",temp_output2[i]);
	printf("\n");*/
	invCipher(temp_output2,output2,ekey2);
	uint8_t exp4[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
	TEST_ASSERT(isEqualMessage(exp4,output2));
	/*
	for(i=0; i<16; i++) printf("%x ",output2[i]);
	printf("\n");*/
}

void test_mulpoly(){
	int poly1[] = {1,1,1,1,1,1,1,1};
	int poly2[] = {1,1,1,1,1,1,1,1};
	mulPoly(poly1,poly2);

	printf("mulPoly res:");
	for(int i=0; i<8; i++) printf("%d",poly1[i]);
	printf("\n");
	uint8_t x = 0xff, y = 0xff;
	uint8_t result = 0;
	result = mul_bit(x,y);
	printf("bit result: %x\n\n",result);

	int poly3[] = {1,1,1,1,0,0,0,1};
	int poly4[] = {1,1,1,0,0,0,0,1};
	mulPoly(poly3, poly4);
	printf("mulPoly res:");
	for(int i=0; i<8; i++) printf("%d",poly3[i]);
	printf("\n");

	x = 0xf1, y = 0xe1;
	result=0;
	result = mul_bit(x,y);
	printf("bit result: %x\n",result);

}
void test_subbit(){
	uint16_t result=0;
	uint16_t x = 0x7fff;
	uint16_t y = 0x46c0;
	result = sub_bit(x,y);
	printf("result = %x\n",result);

	result = mod_bit(x);
	printf("mod result = %x\n",result);

	x = 0x5555;
	result = mod_bit(x);
	printf("mod result 2 = %x\n",result);
}


void test_mod(){
	int poly2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int res[8]; clear8(res);
	mod(poly2,15,res);
	for(int i=0; i<8; i++) printf("%d",res[i]);
	printf("\n");

	uint16_t x = 0x7fff;
	uint8_t result=0;
	result = mod_bit(x);
	printf("result = %x\n",result);
}

void test_finddeg(){
	int deg = 0;
	deg = find_deg(0x40);
	printf("deg = %x\n",deg);
}

int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	//test_cipher2();
	//test_subbit();
	printf("\n");
	test_mulpoly();

	test_mod();
}
