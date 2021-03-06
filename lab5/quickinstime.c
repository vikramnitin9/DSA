#include <stdio.h>
#include <time.h>

struct Student{
	char name[20];
	double marks1;
	double marks2;
};

typedef struct Student Data;

void display(Data* A, int low, int high){
	int i;
	for(i=low; i<=high; ++i)
		printf("%s %lf %lf\n", A[i].name, A[i].marks1, A[i].marks2);
}

int less(Data x, Data y){
	double tot1 = x.marks1 + x.marks2;
	double tot2 = y.marks1 + y.marks2;
	return (tot1 < tot2);
}

void swap(Data* A, int i, int j){
	Data temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int pivot(Data* A, int low, int high){
	return high;
}

int part(Data* A, int low, int high, int pivot){
	//printf("Partition procedure called\n");
	int left = low;
	int i;
	
	for(i=low; i<=high; ++i){
		if(less(A[i],A[pivot])){
			swap(A,i,left);
			left++;
		}
	}
	swap(A,pivot,left);
	return left;
}

void quicksort(Data* A, int low, int high){
	//printf("Quicksort procedure called\n");

	if(low < high){
		int p = part(A, low, high, pivot(A, low, high));
		quicksort(A, low, p-1);
		quicksort(A, p+1, high);
	}
}

void InsertSort(Data* A, int low, int high){
	int i,j;

	for(i=low; i<=high; ++i){
		j = i;
		while(j>low && less(A[j],A[j-1])){
			swap(A,j,j-1);
			j--;
		}
	}
}

void QuickIns(Data* A, int low, int high, int t){
	if((high-low+1) >= t){
		int p = part(A, low, high, pivot(A, low, high));
		QuickIns(A, low, p-1, t);
		QuickIns(A, p+1, high, t);
	}
	//else if (low < high){
		//InsertSort(A, low, high);
	//}
}

int main(){
	static Data s[1000000], s_backup[1000000];
	
	int exit_flag = 0;
	int choice;
	int i, N=0, t;

	FILE* fileptr = fopen("generated.txt","r");

	if(fileptr == NULL){
		printf("Error opening file\n");
		return 0;
	}

	while(!feof(fileptr)){
		fscanf(fileptr, "%s ",s[N].name);
		fscanf(fileptr, "%lf",&s[N].marks1);
		fscanf(fileptr, "%lf",&s[N].marks2);
		N++;
	}
	
	for(i=0; i<N; ++i){
		s_backup[i] = s[i];
	}

	t = 10;

	double t1,t2;
	struct timespec timer;
	clock_gettime(CLOCK_REALTIME, &timer);
	t1 = timer.tv_nsec;

	QuickIns(s, 0, N-1, t);

	clock_gettime(CLOCK_REALTIME, &timer);
	t2 = timer.tv_nsec;
				
	printf("QuickIns took %lf\n",t2-t1);
	
	for(i=0; i<N; ++i){
		s[i] = s_backup[i];
	}

	clock_gettime(CLOCK_REALTIME, &timer);
	t1 = timer.tv_nsec;

	quicksort(s, 0, N-1);

	clock_gettime(CLOCK_REALTIME, &timer);
	t2 = timer.tv_nsec;
	
	printf("QuickSort  took %lf\n",t2-t1);

	return 0;
}
