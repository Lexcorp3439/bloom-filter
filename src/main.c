#include "bloom.h"
#include <stdio.h>

#define ERROR_OPEN_FILE 3
#define ERROR_ARG_LEN 4

bool readFile(FILE *file, SBloom *bloom);
int checkArgs(int argc, char* argv[]);
bool readFile(FILE *file, SBloom *bloom);

int main(int argc ,char* argv[]) 
{	
	checkArgs(argc, argv);

	int par1 = atoi(argv[2]);
	int par2 = atoi(argv[4]);

	FILE *file = fopen(argv[6], "r");

	SBloom *bloom = create_bloom(par1, par2);

	readFile(file, bloom);
	fclose(file);

	write_mask(bloom, argv[8]);

	delete_bloom(bloom);
	return 0;
}

int checkArgs(int argc, char* argv[]) {
	if (argc > 9) {
		printf("Error args length");
		exit(ERROR_ARG_LEN);
	}
	int opt1 = atoi(argv[1]);
	int par1 = atoi(argv[2]);
	printf("%d\n", par1);

	int opt2 = atoi(argv[3]);
	int par2 = atoi(argv[4]);
	printf("%d\n", par2);

	int opt3 = atoi(argv[5]);
	printf("file= %s\n", argv[6]);

	FILE *file = fopen(argv[6], "r");
	if (file == NULL) {
		printf("Error opening file");
		exit(ERROR_ARG_LEN);
	}
	fclose(file);
	return 0;
}

bool readFile(FILE *file, SBloom *bloom) {
	char ch;
	char *string = NULL; 
	int len = 0;
	while (!feof(file)) {
		ch = getc(file);
		if ((ch == ' ' || ch == '\n' || ch == EOF) && len != 0) {
			add(string, len, bloom);
			free(string);
			string = NULL;
			len = 0;
		}
		else {
			if (string == NULL) {
				string = (char *)calloc(++len, sizeof(char));
			} else {
				string = (char*)realloc(string, ++len);
			}
			string[len - 1] = ch;
		}
	}
	return true;
}