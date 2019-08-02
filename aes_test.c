#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
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
#include "bit.h"*/
#include "AES.h"

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

void test_assemble(){
	uint32_t a = 0x11223344;
	uint32_t a0 = a>>24;
	uint32_t a1 = a>>16;
	uint32_t a2 = a>>8;
	uint32_t a3 = a;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
	a = 0;
	a0 = a0<<24;
	a1 = a1<<16;
	a2 = a2<<8;
	//a3 = a3;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
	a = a0|a1|a2|a3;
	printf("a = %x   a0 = %x   a1 = %x   a2 = %x   a3 = %x\n",a,a0,a1,a2,a3);
}

void test_cipher32b(){
	struct key32 key; clearKey32(&key);

	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	struct expKey32 ekey;
	KeyExpansion(&key,&ekey);
	//printExpkey(&ekey);

	uint32_t in[] = {0x328831e0, 0x435a3137, 0xf6309807, 0xa88da234};

	uint32_t out[4];
	Cipher(in,out,&ekey);
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
}

void test_Cipher(){
	uint32_t out0[4];
	out0[0] = 0x3902dc19;
	out0[1] = 0x25dc116a;
	out0[2] = 0x8409850b;
	out0[3] = 0x1dfb9732;

	uint32_t in0[4];
	in0[0] = 0x328831e0;
	in0[1] = 0x435a3137;
	in0[2] = 0xf6309807;
	in0[3] = 0xa88da234;

	uint32_t in[4];
	uint32_t out[4];
	struct expKey32 ekey;
	int N = 100000;

	in[0] = 0x328831e0;
	in[1] = 0x435a3137;
	in[2] = 0xf6309807;
	in[3] = 0xa88da234;

	struct key32 key;
	key.block[0] = 0x2b7e1516;
	key.block[1] = 0x28aed2a6;
	key.block[2] = 0xabf71588;
	key.block[3] = 0x09cf4f3c;

	clock_t b = clock();
	for(int i=0; i<N; i++)KeyExpansion(&key,&ekey);
	clock_t e = clock();
	printf("\nKeyExpansion(): %f usec\n", (e-b)/(double)N/CLOCKS_PER_SEC*1e6);

	clock_t begin2 = clock();
	for(int i=0; i<N; i++)Cipher(in,out,&ekey);
	clock_t end2 = clock();

	printf("\nCipher(): %f usec\n", (end2-begin2)/(double)N/CLOCKS_PER_SEC*1e6);
	//compare s0 and out
	TEST_ASSERT(isEqualBlock(out0,out));

	clock_t b2 = clock();
	for(int i=0; i<N; i++)InvCipher(out,in,&ekey);
	clock_t e2 = clock();
	printf("\nInvCipher(): %f usec\n", (e2-b2)/(double)N/CLOCKS_PER_SEC*1e6);
	TEST_ASSERT(isEqualBlock(in0,in));
}
/*
void test_rot(){
	uint32_t t,t1,t2,t3;
	t = 0x11223344;
	t1 = rotR1(t);
	t2 = rotR2(t);
	t3 = rotR3(t);
	printf("t1 = %x   t2 = %x   t3 = %x\n",t1,t2,t3);
}*/

int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	printf("\n");
	test_Cipher();
	printf("\n");

}
