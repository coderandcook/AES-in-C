
LIB_SRC=SubBytes2.c ShiftRows2.c MixColumns.c AddRoundKey3.c KeyExpansion.c cipher.c InvShiftRows.c InvSubBytes.c InvMixColumns.c InvCipher.c shifter.c bit.c
TEST_SRC=aes_test.c AES.c
ALL_SRC=$(LIB_SRC) $(TEST_SRC)

LIB_OBJ=$(LIB_SRC:.c=.o)

LIB_BASENAME=aes
LIB=lib$(LIB_BASENAME).a
all: $(LIB)

CFLAGS+=-Wall -Wextra -O2 -g $(DEBUG)
LDFLAGS+=-L./ $(DEBUG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(@:.o=.d)

$(LIB): $(LIB_OBJ)
	ar r $@ $(LIB_OBJ)

aes_test: $(TEST_SRC:.c=.o) $(LIB)
	$(CC) $(LDFLAGS) $< -o $@ -l$(LIB_BASENAME)

test: ./aes_test
	./aes_test

clean:
	rm -rf $(LIB) *.o *.d aes_test
	
.PHONY: clean

-include $(ALL_SRC:.c=.d)
.SECONDARY: $(ALL_SRC:.c=.o)

