#include "bloom.h"
#include <stdio.h>


uint64_t* hash(const uint8_t *data, size_t len);
uint64_t hash_index(uint8_t k, uint64_t hashA, uint64_t hashB, uint64_t size);

struct Bloom {
	bool * mask;
	int size;
	int hash_num;
};

SBloom * create_bloom(int size, int possibly_len) {
	bool d = true;
	SBloom * bloom = (SBloom *)calloc(1, sizeof(SBloom));
	bloom->mask = (bool *)calloc(size, sizeof(bool));

	printf("%s\n", "here");

	bloom->size = size;
	printf("%d\n", size);

	bloom->hash_num = (int)(log(2) * size / possibly_len);
	printf("%d\n", bloom->hash_num);

	return bloom;
}

void delete_bloom(struct Bloom * bloom) {
	if (bloom->mask != NULL) {
		free(bloom->mask);
	} 
	free(bloom);
}

int get_size(SBloom * bloom) {
	return bloom->size;
}

void add(const void *data, size_t len, SBloom * bloom) {
	const uint8_t * dt = (const uint8_t*)data;
	uint64_t * _hash = hash(dt, len);
	for (int i = 0; i < bloom->hash_num; i++) {
		bloom->mask[hash_index(i, _hash[0], _hash[1], bloom->size)] = true;
	}
	free(_hash);
}


bool possibly_contains(const void *data, size_t len, SBloom * bloom) {
	const uint8_t * dt = (const uint8_t*)data;
	uint64_t * _hash = hash(dt, len);
	for (int i = 0; i < bloom->hash_num; i++) {
		if (bloom->mask[hash_index(i, _hash[0], _hash[1], bloom->size)] != true) {
			free(_hash);
			return false;
		}
	}
	free(_hash);
	return true;
}

uint64_t* hash(const uint8_t *data, size_t len) {
	uint64_t* hash_ = (uint64_t*)calloc(2, sizeof(uint64_t));
	MurmurHash3_x64_128(data, len, 0, hash_);

	return hash_;
}

uint64_t hash_index(uint8_t k,
	uint64_t hashA,
	uint64_t hashB,
	uint64_t size) {
	return (hashA + k * hashB) % size;
}

void write_mask(SBloom * bloom, char* outf) {
	FILE * out = fopen(&outf, "w");
	int count = 0;
	for (int i = 0; i < bloom->size; i++) {
		int t = 48;
		if (bloom->mask[i] == true) {
			count++;
			t = 49;
		}
		fputc(t, out);
	}
	fclose(out);
}