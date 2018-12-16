#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int valid_input(char *txt, char *patt)
{
	char * emptystr = "";
	if (txt == NULL || patt == NULL)
		return 0;

	if (!strcmp(txt, emptystr) || !strcmp(patt, emptystr))
		return 0;

	if (strlen(patt) > strlen(txt))
		return 0;

	return 1;
}

int naive_match(char text[], char patt[])
{
	if (!valid_input(text, patt)){
		printf(" %s Invalid input", __FUNCTION__);
		return EXIT_FAILURE;
	}

	for (int tidx = 0; tidx < strlen(text) - strlen(patt) + 1; tidx++) {
		int pidx = 0;
		for (; pidx < strlen(patt); pidx++) {
			if (text[tidx + pidx] != patt[pidx])
				break;
		}
		if (pidx == strlen(patt)) {
			printf(" Match found at %s %d ", __FUNCTION__,  tidx);
			return tidx;
		}
		printf("\n");
	}

	return EXIT_FAILURE;
}

static int hash(char* str, int n)
{
	int alphabet_size = 256;
	int prime = 2147483647;

	int hash = 0;
	for (int i = 0; i < n; i++)
		hash = (hash * alphabet_size + str[i]) % prime;
	return hash;
}
/* T={1234567} d = 10 q  = 11 P={34}
 * i = 0 T=12 P=34
 * i=1 (12,1,3) = (12 - 10)*10 + 3 = 23
 */
static int reshash(int curr_hash, char text_first_char, char text_next_char, int patt_size){
	int q = 2147483647;
	int d = 256;
	int h  = pow(d, patt_size-1);
	int new_hash = ((curr_hash - (text_first_char * h)) * d + text_next_char) % q;
	return new_hash;
}

int robin_carp_match(char text[], char patt[])
{
	if (!valid_input(text, patt))
		return -1;

	int phash = hash(patt, strlen(patt));
	int thash = hash(text, strlen(patt));

	for (int tidx = 0; tidx < strlen(text) - strlen(patt) + 1; tidx++) {
		if (phash == thash) {
			if (strncmp(patt, text+tidx, strlen(patt)) == 0) {
				printf("\n %s Match Found at index: %d",__FUNCTION__, tidx);
				return tidx;
			}
		}
		thash = reshash(thash, text[tidx], text[tidx+strlen(patt)], strlen(patt));
	}
	return 0;
}

int* computeLastOccup(char * patt, int num_char)
{
	int i, *LO;
	LO = (int*) malloc(sizeof(int) * num_char);
	for (i = 0; i < num_char; i++) {
		LO[i] = -1;
	}
	for (i = 0; i < strlen(patt); i++) {
		LO[(int) patt[i]] = i;
	}

	return LO;
}

void BMMatch(char *text, char *patt)
{
	int j, m, n;
	n = strlen(text);
	m = strlen(patt);
	int  NumChar = 256;
	int* LO = computeLastOccup(patt, NumChar);

	int i = 0;
	while (i < strlen(text) - strlen(patt)+1) {

		j = m - 1;
		printf("\n i:%d j:%d ", i, j);

		while (text[i + j] == patt[j] && j >= 0) {
			printf("\n Matching: i:%d j:%d", i, j);
			j--;
		}
		/* Mismatch occur then we need to align the pattern such that
		 Bad char cause mismatch. We find where in the pattern the char last occur
		 we minus the bad char position from  current position(j) or m
		 */
		if (j < 0) {
			printf("\n pattern occurs at shift = %d curr:%d Shift:%d", i, i + j, m - LO[text[i + m]]);
			printf("\n i:%d j:%d", i, j);
			i += (i + m < n) ? m - LO[text[i + m]] : 1;
		}else {
			printf("\n NO Match i:%d j:%d Shift:%d", i, j, LO[text[i + j]]);
			i +=  j - LO[text[i + j]] > 1 ?j - LO[text[i + j]] :1;
		}

	}
	free(LO);

}


int main()
{
	char* str1 ="abcdabcd";
	char*str2 = "abcd";
	naive_match(str1,str2);
	robin_carp_match(str1, str2);
	BMMatch(str1, str2);
}
