
LIB_SRC=poly.c div_poly.c div_generic.c mod3.c SubBytes2.c ShiftRows2.c MixColumns.c
TEST_SRC=aes_test.c
ALL_SRC=$(LIB_SRC) $(TEST_SRC)

LIB_OBJ=$(LIB_SRC:.c=.o)

LIB_BASENAME=aes
LIB=lib$(LIB_BASENAME).a
all: $(LIB)

CFLAGS=-Wall -Wextra -O2
LDFLAGS=-L./

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

.SECONDARY: $(ALL_SRC:.c=.o)

