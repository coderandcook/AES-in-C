#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	KeyExpansion32(&key,&ekey);
	//printExpkey32(&ekey);

	uint32_t in[] = {0x328831e0, 0x435a3137, 0xf6309807, 0xa88da234};

	uint32_t out[4];
	cipher32(in,out,&ekey);
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
}

void test_cipher32(){
	uint32_t in[4];
	uint32_t out[4];

	struct expKey32 ekey;

	int N = 1000;

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
	for(int i=0; i<N; i++)KeyExpansion32(&key,&ekey);
	clock_t e = clock();
	printf("\nKeyExpansion(): %f usec\n", (e-b)/(double)N/CLOCKS_PER_SEC*1e6);

	clock_t begin2 = clock();
	for(int i=0; i<N; i++)cipher32(in,out,&ekey);
	clock_t end2 = clock();

	printf("\ncipher32(): %f usec\n", (end2-begin2)/(double)N/CLOCKS_PER_SEC*1e6);
	printf("out:\n");
	for(int i=0; i<4; i++)printf("%x\n",out[i]);
	printf("\n");

	invCipher32(out,in,&ekey);
	for(int i=0; i<4; i++)printf("%x\n",in[i]);



	printf("\n");
	out[0] = 0x696ad870;
	out[1] = 0xc47bcdb4;
	out[2] = 0xe004b7c5;
	out[3] = 0xd830805a;

	key.block[0] = 0x00010203;
	key.block[1] = 0x04050607;
	key.block[2] = 0x08090a0b;
	key.block[3] = 0x0c0d0e0f;

	KeyExpansion32(&key,&ekey);

	clock_t b2 = clock();
	for(int i=0; i<N; i++)invCipher32(out,in,&ekey);
	clock_t e2 = clock();
	printf("\ninvCipher32(): %f usec\n", (e2-b2)/(double)N/CLOCKS_PER_SEC*1e6);

	for(int i=0; i<4; i++)printf("%x\n",in[i]);
}

void test_equal(){
	struct state2 s1;
	s1.block[0] = 0x00112233;
	s1.block[1] = 0x44556677;
	s1.block[2] = 0x8899aabb;
	s1.block[3] = 0xccddeeff;

	struct state2 s2;
	s2.block[0] = 0x00112233;
	s2.block[1] = 0x44556677;
	s2.block[2] = 0x8899aabb;
	s2.block[3] = 0xccddeeff;

	TEST_ASSERT(isEqualState(&s1,&s2));


	struct key32 key1;
	struct key32 key2;
	key1.block[0] = 0x00010203;
	key1.block[1] = 0x04050607;
	key1.block[2] = 0x08090a0b;
	key1.block[3] = 0x0c0d0e0f;

	key2.block[0] = 0x00010203;
	key2.block[1] = 0x04050607;
	key2.block[2] = 0x08090a0b;
	key2.block[3] = 0x0c0d0e0e;

	struct expKey32 ekey1;
	struct expKey32 ekey2;
	KeyExpansion32(&key1,&ekey1);
	KeyExpansion32(&key2,&ekey2);

	TEST_ASSERT(isEqualEkey(&ekey1,&ekey2));
}


int main()
{
	//TEST_EQUAL(add(3, 5), 3 + 5);
	//TEST_EQUAL(sub(3, 5), 3 - 5);

	printf("\n");
	test_cipher32();
	printf("\n");
	test_equal();
}
