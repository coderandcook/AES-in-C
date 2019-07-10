#include <stdlib.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"

void AddRoundKey_generic(struct state *s, const struct expKey *ekey, int i);
