/* random_generator.c */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void rand_str(char *dest, size_t length) {
	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (length-- > 0) {
		size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
		*dest++ = charset[index];
	}
	*dest = '\0';
}

double rand_double(double min, double max){
	return (double)rand()/(double)RAND_MAX * (max - min) + min;
}

int main(int argc, char *argv[]){
	int N = 10;
	assert(argc == 2);
	int i = atoi(argv[1]);
	char *str = (char*) malloc (sizeof(char) * N);
	assert(str != NULL);
	//rand_str(str, N);
	
	FILE* fileptr = fopen("generated.txt","w");
	
	while(i--){
		rand_str(str, N);
		fprintf(fileptr, "%s\t%lf\t%lf\n", str, rand_double(0,100), rand_double(0,100));
	}

	fclose(fileptr);
	return 0;
}
/* End of random_generator.c */
