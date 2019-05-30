#ifndef PRIVATE_VAR
#define PRIVATE_VAR

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "murmur3.h"
#include <math.h> 

struct Bloom;
typedef struct Bloom SBloom;

SBloom * create_bloom(int size, int possibly_len);
void delete_bloom(struct Bloom * bloom);
int get_size(SBloom * bloom);
void add(const void *data, size_t len, SBloom * bloom);
bool possibly_contains(const void *data, size_t len, SBloom * bloom);
void write_mask(SBloom * bloom, char* out);

#endif
