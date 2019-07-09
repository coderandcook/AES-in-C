#include <stdlib.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"

void AddRoundKey_generic(struct state *s, struct expKey *ekey, int i);
