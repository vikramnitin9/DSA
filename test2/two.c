#include <stdio.h>
#include <stdlib.h>

void copy(char* A, char* B, int low, int high){
	int i;
	for(i=low; i<high; ++i)
		A[i] = B[i];
}

void swap(char** A, int i, int j, int low, int high){
	char* temp = (char*)malloc((high-low)*sizeof(char));
	copy(temp, A[i], low, high);
	copy(A[i], A[j], low, high);
	copy(A[j], temp, low, high);
}

void part3way3keys(char** A, int low, int high, int d, int W, int rewrite_flag){
	char pivot = 'Y';
	int eq1=low, less=low, more=high-1, eq2=high-1;
	int i;

	char **B = (char**) malloc((high-low)*sizeof(char*));

	for(i=low; i<high; ++i){
		B[i-low] = (char*)malloc(W*sizeof(char));
		copy(B[i-low], A[i], 0, W);
	}

	while(less <= more){
		if(B[less][d] == pivot){
			swap(B, less, eq1, 0, W);
			eq1++;
			less++;
			continue;
		}
		if(B[more][d] == pivot){
			swap(B, more, eq2, 0, W);
			eq2--;
			more--;
			continue;
		}
		if(B[less][d] > pivot){
			swap(B, less, more, 0, W);
			more--;
		}
		else{
			less++;
		}

		if(less > more) break;

		if(B[more][d] < pivot){
			swap(B, more, less, 0, W);
			less++;
		}
		else{
			more--;
		}
	}
	// less --;
	// more ++;

	// for(i=0; i<eq1; ++i){
	// 	swap(B, i, eq1+i, 0, W);
	// }
	// for(i=high-low-1; i>more; ++i){
	// 	swap(B, i, eq2-i, 0, W);
	// }

	if(rewrite_flag == 1){
		for(i=low; i<high; ++i){
			copy(A[i], B[i-low], 0, W);
		}
	}
	else{
		for(i=low; i<high; ++i){
			printf("%c\n", B[i][d]);
		}
	}
	// if(less = more+1){ //Some termination problem
	// 	if(A[less][d] == pivot)
	// 		swap(A, less, eq1, 0, W);
	// 	if(A[more][d] == pivot)
	// 		swap(A, more, eq2, 0, W);
	// }

}

void radixPart3waySort(char** A, int low, int high, int W){
	int i;
	for(i=W-1; i>=0; --i){
		part3way3keys(A, low, high, i, W, 1);
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

			part3way3keys(A, 0, N, d, W, 0);
		}

		if(choice == 3){
			radixPart3waySort(A, 0, N, W);
		}

		if(choice == -1){
			exit_flag = 1;
		}
	}
	return 0;
}