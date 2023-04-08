#include <stdio.h>
#include <string.h>
#define MAX_string 10000000
#define MAX_pattern 3000

char string[MAX_string];
char pattern[MAX_pattern];
int position[MAX_string];

int main(void) {
	FILE *fp_string, *fp_pattern;
	FILE *fp_result;
	
	fp_string = fopen("string.txt", "r");
	fp_pattern = fopen("pattern.txt", "r");

	if(fp_string == NULL || fp_pattern == NULL) {
		printf("The string file does not exist\n");
		return 1;
	}
	
	fp_result = fopen("result_naive.txt", "w");
	fgets(string, MAX_string, fp_string);
	fgets(pattern, MAX_pattern, fp_pattern);

	int count_index = 0;
	int position_index = 0;
	int i, j, start = 0;
	int last_string = strlen(string) - 2;
	int last_pattern = strlen(pattern) - 2;
	int end_match = last_pattern;

	for(i = 0; end_match <= last_string; end_match++, start++) {
		if(string[end_match] == pattern[last_pattern])
			for(j = 0, i = start; j < last_pattern && string[i] == pattern[j]; i++, j++);
		if(j == last_pattern) {
			count_index++;
			position[position_index++] = start;
			
			j = 0;
		}
	}
	fprintf(fp_result, "%d\n", count_index);
	for(i = 0; i < position_index; i++) fprintf(fp_result, "%d ", position[i]);
	printf("Program complete. Result saved to result_naive.txt\n");
	
	fclose(fp_string);
	fclose(fp_pattern);
	fclose(fp_result);
}
