#include "test.h"
#include "bloom.h"

void test() {
	int par1 = 560000;
	int par2 = 1500;
	SBloom *bloom = create_bloom(par1, par2);

	int six = 6;
	int seven = 7;
	int eight = 8;
	int nine = 9;
	int ten = 10;
	double dten = 76888.8;
	add(&six, sizeof(int), bloom);
	add(&seven, sizeof(int), bloom);
	add(&eight, sizeof(int), bloom);
	add(&nine, sizeof(int), bloom);
	bool test1 = possibly_contains(&six, sizeof(int), bloom);
	bool test2 = possibly_contains(&seven, sizeof(int), bloom);
	bool test3 = possibly_contains(&eight, sizeof(int), bloom);
	bool test4 = possibly_contains(&nine, sizeof(int), bloom);
	bool test5 = possibly_contains(&ten, sizeof(int), bloom);
	bool test6 = possibly_contains(&dten, sizeof(double), bloom);

	assert_equals_int(1, test1);
	assert_equals_int(1, test2);
	assert_equals_int(1, test3);
	assert_equals_int(1, test4);
	assert_equals_int(0, test5);
	assert_equals_int(0, test6);

	delete_bloom(bloom);
}