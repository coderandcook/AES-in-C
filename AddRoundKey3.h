#pragma once
#include <stdlib.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"

void AddRoundKey32(struct state2 *s, const struct expKey32 *ekey, int i);
