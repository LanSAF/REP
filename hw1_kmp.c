#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_string 10000000
#define MAX_pattern 3000

char string[MAX_string];
char pattern[MAX_pattern];
int position[MAX_string];
int* failure_table;

int main(void) {
        FILE *fp_string, *fp_pattern;
        FILE *fp_result;

        fp_string = fopen("string.txt", "r");
        fp_pattern = fopen("pattern.txt", "r");

        if(fp_string == NULL || fp_pattern == NULL) {
                printf("The string file does not exist\n");
                return 1;
        }

        fp_result = fopen("result_kmp.txt", "w");
        fgets(string, MAX_string, fp_string);
        fgets(pattern, MAX_pattern, fp_pattern);

	int i, j, start = 0;
	int len_string = strlen(string) - 1;
	int len_pattern = strlen(pattern) - 1;
	int count_index = 0;
	int position_index = 0;
	
	failure_table = (int*)calloc(strlen(pattern), sizeof(int));
	failure_table[0] = -1;
	for(j = 1; j < len_pattern; j++) {
		i = failure_table[j - 1];
		while((pattern[j] != pattern[i + 1]) && (i >= 0)) i = failure_table[i];
		if(pattern[j] == pattern[i + 1]) failure_table[j] = i + 1;
		else failure_table[j] = -1;
	}

	i = 0;
	j = 0;
	while(i < len_string) {
		if(string[i] == pattern[j]) {
			i++;
			j++;
		}
		else if(j == 0) i++;
		else j = failure_table[j - 1] + 1;

		if(j > len_pattern - 1) {
			count_index++;
			position[position_index++] = i - j;
			j = failure_table[j - 1] + 1;
		}
	}
	fprintf(fp_result, "%d\n", count_index);
	for(i = 0; i < position_index; i++) fprintf(fp_result, "%d ", position[i]);
	printf("Program completes. Result saved to result_kmp.txt\n");

	fclose(fp_string);
	fclose(fp_pattern);
	fclose(fp_result);
	free(failure_table);
}
