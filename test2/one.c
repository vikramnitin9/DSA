#include <stdio.h>
#include <stdlib.h>

void copy(char* A, char* B, int low, int high){
	int i;
	for(i=low; i<high; ++i)
		A[i] = B[i];
}

void keyIndex(char** A, int low, int high, int d, int W, int rewrite_flag){
	int freq[26];
	int i;

	char **B = (char**) malloc((high-low)*sizeof(char*));

	for(i=0; i<26; ++i)
		freq[i] = 0;

	for(i=low; i<high; ++i){
		int index = (int)(A[i][d] - 'a');
		freq[index] ++;
		B[i-low] = (char*)malloc(W*sizeof(char));
	}

	int cum[26];
	int count = 0;

	for(i=0; i<26; ++i){
		cum[i] = count;
		count += freq[i];
	}

	for(i=0; i<26; ++i)
		freq[i] = 0;

	for(i=low; i<high; ++i){
		int index = (int)(A[i][d] - 'a');
		copy(B[cum[index]+freq[index]], A[i], 0, W);
		freq[index]++;
	}

	if(rewrite_flag == 1){
		for(i=low; i<high; ++i){
			copy(A[i], B[i-low], 0, W);
		}
	}
	else{
		for(i=low; i<high; ++i){
			printf("%c\n", B[i-low][d]);
		}
	}
}

void lsdRadixSort(char** A, int low, int high, int W){
	int i;
	for(i=W-1; i>=0; --i){
		keyIndex(A, low, high, i, W, 1);
	}
	for(i=low; i<high; ++i){
		printf("%s\n", A[i]);
	}
}

int main(){
	int choice, exit_flag=0;
	int N, W;
	int i;

	char **A;

	while(exit_flag != 1){
		scanf("%d", &choice);

		if(choice == 1){
			scanf("%d %d", &N, &W);
			A = (char**)malloc(N*sizeof(char*));

			for(i=0; i<N; ++i){
				A[i] = (char*)malloc(W*sizeof(char));
				scanf("%s", A[i]);
			}
		}

		if(choice == 2){
			int d;
			scanf("%d", &d);

			keyIndex(A, 0, N, d, W, 0);
		}

		if(choice == 3){
			lsdRadixSort(A, 0, N, W);
		}

		if(choice == -1){
			exit_flag = 1;
		}
	}
	return 0;
}