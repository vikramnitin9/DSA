#include <stdio.h>
#include <stdlib.h>

int main(){
	int *a;
	unsigned long long int n = 2;
	while(1){
		a = (int*) malloc(n*sizeof(int));
		if(a != NULL)
			printf("n = %d, Success\n",n);
		else{
			printf("Failed at n = %d\n",n);
			break;
		}
		free(a);
		n*=2;
	}
	return 0;
}

//Failed at n = 536870912

