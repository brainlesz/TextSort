#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

int comp(const void* a, const void* b) {
	char* pa = *(char**)a;
	char* pb = *(char**)b;
	return strlen(pa) - strlen(pb);
}

void TextSort(FILE *IN) {
	if (IN == NULL)
	{
		printf("ERROR opening file");
		exit(EXIT_FAILURE);
	}
	char buf[5] = { 0 };
	fgets(buf, 5, IN);
	if (buf[0] == '\0')
	{
		printf("ERROR File is empty!");
		exit(EXIT_FAILURE);
	}
	fseek(IN, 0, SEEK_SET);
	char** text = NULL;gi
	int size=0;
	int c;
	setlocale(LC_ALL, "Rus");
	while (!feof(IN)) {
		c = fgetc(IN);
		if (c == '\n') {
			size++;
		}
	}
	size++;
	text = (char**)malloc(size * (sizeof(char*)));
	fseek(IN, 0, SEEK_SET);
	int j = 0;
	c = fgetc(IN);
	while (!feof(IN)) {
		int size_str = 0;
		while (c!='\n'&& c!=EOF)
		{
			size_str++;
			c = fgetc(IN);
			if (c == '\r') {
				c = fgetc(IN);
				continue;
			}
			if (feof(IN)) {
				break;
			}
		}
		text[j] = (char*)malloc((size_str+1) * (sizeof(char)));
		text[j][size_str] = '\0';
		j++;
		c = fgetc(IN);
	}
	fseek(IN, 0, SEEK_SET);
	int stolb = 0;
	c = fgetc(IN);
	while (!feof(IN)) {
		int str = 0;
		while (c != '\n' && c != EOF)
		{
			text[stolb][str] = c;
			c = fgetc(IN);
			str++;
			if (c == '\r') {
				c = fgetc(IN);
				continue;
			}
			if (feof(IN)) {
				break;
			}
		}
		printf("[%d] - %s\n", stolb, text[stolb]);
		stolb++;
		c = fgetc(IN);
	}
	qsort(text, size, sizeof(char**), comp);
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("[%d] - %s\n", i,text[i]);
	}
	for (int i = 0; i < size; i++) {
		free(text[i]);
	}
	free(text);
}


int main(int argc, char* argv[]) {
	FILE* IN = NULL;
	char filename[100] = {0};
	char n;
	while (1) {
		printf("Enter where we get text\n[1] - command line\n[2] - console\n[3] - from file\n[4] - exit\n");
		n = fgetc(stdin);
		while ((getchar()) != '\n');
		int k = 1;
		switch (n)
		{
		case 49:
			if (argc == 1)
			{
				printf("You didn't specify a file\n");
			}
			while (k < argc) {
				for (int i = 0; i < 100; i++) {
					filename[i] = argv[k][i];
					if (argv[k][i] == '\0') {
						break;
					}
				}
				printf("\n\n%s\n\n", filename);
				fopen_s(&IN, filename, "rb");
				TextSort(IN);
				fclose(IN);
				k++;
			}
			break;
		case 50:
			printf("Enter filename: \n");
			scanf_s("%99s", filename, 99u);
			fopen_s(&IN, filename, "rb");
			TextSort(IN);
			fclose(IN);
			printf("\n");
			break;
		case 51:
			printf("\n");
			FILE* Names = NULL;
			fopen_s(&Names, "filenames.txt", "rb");
			if (Names==NULL)
			{
				printf("filenames.txt not found\n");
				break;
			}
			char buf[5] = { 0 };
			fgets(buf, 5, Names);
			if (buf[0] == '\0')
			{
				printf("ERROR File is empty!");
				break;
			}
			fseek(Names, 0, SEEK_SET);
			char c = fgetc(Names);
			while (c != EOF)
			{
				int l = 0;
				while (c != '\n')
				{
					filename[l] = c;
					l++;
					c = fgetc(Names);
					if (c == '\r') {
						c = fgetc(Names);
						continue;
					}
					if (feof(Names)) {
						break;
					}
				}
				filename[l] = '\0';
				printf("\n\n%s\n\n",filename);
				fopen_s(&IN, filename, "rb");
				TextSort(IN);
				fclose(IN);
				c = fgetc(Names);
			}
			break;
		case 52:
			exit(EXIT_FAILURE);
		default:
			printf("WRONG number. Please enter the correct number:\n\n");
			break;
		}
		printf("\n");
		while ((getchar()) != '\n');
	}
	return 0;
}