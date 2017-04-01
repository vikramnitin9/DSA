#include <stdio.h>
#include <math.h>
#include <string.h>

const long int BATCH_SIZE = 1024;

void split(FILE* fileptr){
	int count = 0;
	
	FILE* temp_ptr;

	while(!feof(fileptr)){
		count++;
		int curr_batch = ceil(count/BATCH_SIZE);
		//printf("Batch %d\n",curr_batch);

		char fname[] = "./intermediate/";
		char str[10]; //no_of_batches should not have more than 10 digits
		sprintf(str,"%d",curr_batch);

		strcat(fname,str);
		strcat(fname,".txt");

		temp_ptr = fopen(fname,"a");

		if(temp_ptr == NULL){
			printf("Error opening intermediate file\n");
			break;
		}
	
		int temp;
		fscanf(fileptr,"%d ",&temp);
		fprintf(temp_ptr,"%d\n",temp);
		fclose(temp_ptr);
	}
}

void merge(FILE* ptr1, FILE* ptr2, FILE* temp){
	if(ptr1 == NULL || ptr2 == NULL){
		printf("File not opened properly\n");
	}

	if(feof(ptr1) && feof(ptr2)){
		fclose(temp);
		return;
	}
	
	int inp1,inp2;

	if(feof(ptr1)){
		fscanf(ptr2,"%d ",&inp2);
		fprintf(temp,"%d\n",inp2);
		merge(ptr1,ptr2,temp);
	}
	if(feof(ptr2)){
		fscanf(ptr1,"%d ",&inp1);
		fprintf(temp,"%d\n",inp1);
		merge(ptr1,ptr2,temp);
	}
	
	printf("Here!\n");

	fscanf(ptr1,"%d ",&inp1);
	fscanf(ptr2,"%d ",&inp2);
	
	if(inp1 <= inp2){
		fprintf(temp,"%d\n",inp1);
		fseek(ptr2,-1,SEEK_CUR);
		merge(ptr1,ptr2,temp);
	}
	else{
		fprintf(temp,"%d\n",inp2);
		fseek(ptr1,-1,SEEK_CUR);
		merge(ptr1,ptr2,temp);
	}
}

void sort(char* fname){
	FILE* fileptr = fopen(fname,"r");

	long int arr[10000];
	long int count = 0;
	long int i,j;
	long int temp;
	
	printf("Sorting started\n");

	while(!feof(fileptr)){
		fscanf(fileptr,"%d ",&arr[count++]);
	}
	
/*	for(i=1; i<count; ++i){
		j = i;
		while(j>0 && (arr[j] < arr[j-1])){
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			j--;
		}
	}
*/
	printf("Count : %d\n",count);

	for(i=0; i<count; ++i){
		for(j=i+1; j<count; ++j){
			if(arr[i]>arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	fclose(fileptr);
	remove(fname);
	fileptr = fopen(fname,"w");

	for(i=0; i<count; ++i){
		fprintf(fileptr,"%d\n",arr[i]);
	}
	
	fclose(fileptr);
}

void sort_all(int num_of_batches){
	int i;
	for(i=1; i<=num_of_batches; ++i){
		char fname[] = "./intermediate/";
		char str[10]; //no_of_batches should not have more than 10 digits
		sprintf(str,"%d",i);

		strcat(fname,str);
		strcat(fname,".txt");
		
		sort(fname);
	}
	printf("Sorted\n");
}

void combine(int num_of_batches){
	int i;
	for(i=1; i<=num_of_batches; i++){
		char fname1[] = "./intermediate/";
		char fname2[] = "./intermediate/";

		char str[10]; //no_of_batches should not have more than 10 digits
		sprintf(str,"%d",(2*i)-1);

		strcat(fname1,str);
		strcat(fname1,".txt");

		sprintf(str,"%d",2*i);
		strcat(fname2,str);
		strcat(fname2,".txt");

		FILE* ptr1 = fopen(fname1,"r");
		FILE* ptr2 = fopen(fname2,"r");
		FILE* temp = fopen("./intermediate/temp.txt","w");
		
		merge(ptr1,ptr2,temp);
		printf("Merge done\n");
		fclose(ptr1); fclose(ptr2); fclose(temp);
		rename("./intermediate/temp.txt",fname1);
	}
	printf("Combined once");
	combine(num_of_batches/2);
}

int main(int argc, char* argv[]){
	FILE* fileptr = fopen(argv[1],"r");
	
	if(fileptr == NULL){
		printf("Error opening file\n");
		return 0;
	}

	int count = 0;

	while(!feof(fileptr)){
		int temp;
		fscanf(fileptr,"%d ",&temp);
		count ++;
	}
	
	double log2 = log(count)/log(2);
	int num_batches = ceil(count/BATCH_SIZE);

	printf("The number of records is %d\n",count);
	printf("Log base 2 = %lf\n",log2);
	printf("Selected batch size = %d\n",BATCH_SIZE);
	printf("Number of batches = %d\n",num_batches);
	
	rewind(fileptr);

	if(fileptr == NULL){
		printf("Error opening file\n");
		return 0;
	}

	//split(fileptr);
	fclose(fileptr);

	sort_all(num_batches);
	combine(num_batches);

	return 0;
}

