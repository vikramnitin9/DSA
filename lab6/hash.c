#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 20

int numSymbols = 0;
int numQueries = 0;

struct symbol{
	char key[LEN];
	char type[LEN];
};

struct symbol* symbolList;
struct symbol* queryList;

struct node{
	struct symbol* data;
	struct node* next;	
};

struct linkedList{
	struct node* first;
	int len;
};

int insertAtEnd(struct linkedList* list, struct symbol* data){
	if(list == NULL) return 0;

	int count=0;

	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;

	if(list->first == NULL){
		list->first = new_node;
		return 0;
	}

	struct node* curr = list->first;
	count = 1;

	while(curr->next != NULL){
		curr = curr->next;
		count++;
	}

	curr->next = new_node;
	return count;
}

int findSymbol(struct linkedList* list, struct symbol* data){
	if(list == NULL) return 0;
	if(list->first == NULL) return 0;

	struct node* curr = list->first;
	int count = 1;

	while(curr != NULL){
		if(strcmp(curr->data->key, data->key)==0) break;
		curr = curr->next;
		count++;
	}
	return count;
}

int calc_sum(struct symbol* S){
	int sum = 0;
	int i;

	for(i=0; i<strlen(S->key); ++i)
		sum += (int)S->key[i];

	// sum = sum & (0x00001111);
	return sum;
}

struct hashTable{
	int entries;
	int size;
	double loadFactor;
	int freeSlots;
	int insertionTime;
	int queryingTime;

	struct linkedList* buckets;
};

void readSymbols(){
	int N;
	int i;
	scanf("%d", &N);

	numSymbols = N;

	symbolList = (struct symbol*)malloc(N*sizeof(struct symbol));

	for(i=0; i<N; ++i){
		scanf("%s %s", symbolList[i].key, symbolList[i].type);
	}
}

void readQueries(){
	int N;
	int i;
	scanf("%d", &N);

	numQueries = N;

	queryList = (struct symbol*)malloc(N*sizeof(struct symbol));

	for(i=0; i<N; ++i){
		scanf("%s %s", queryList[i].key, queryList[i].type);
	}
}

void insert(struct hashTable* H, struct symbol* S){
	int index = calc_sum(S) % H->size;

	if(H->buckets[index].first == NULL) H->freeSlots--;

	int t = insertAtEnd(&(H->buckets[index]), S);
	H -> entries++;
	H -> insertionTime += t;
	H -> loadFactor = (double)H->entries / (double)H->size;
}

void transfer(struct hashTable* Hnew, struct hashTable* H){
	int i;

	for(i=0; i < H->size; ++i){
		struct node* curr = H->buckets[i].first;

		while(curr != NULL){
			insert(Hnew, curr->data);
			curr = curr->next;
		}
	}
}

void print(struct hashTable* H){
	int i;

	for(i=0; i < H->size; ++i){
		struct node* curr = H->buckets[i].first;

		while(curr != NULL){
			printf("%s %s\t", curr->data->key, curr->data->type);
			curr = curr->next;
		}
		printf("\n");
	}
}

struct hashTable* createEmptyHashTable(int size){
	struct hashTable* H = (struct hashTable*) malloc(sizeof(struct hashTable));
	H->buckets = (struct linkedList*) malloc(size*sizeof(struct hashTable));
	H->size = size;
	H->freeSlots = size;
}

struct hashTable* createHashTable(){
	int size;
	double minLoad, maxLoad, resizeFactor;
	int i;
	scanf("%d %lf %lf %lf", &size, &minLoad, &maxLoad, &resizeFactor);

	struct hashTable* H = createEmptyHashTable(size);

	for(i=0; i<numSymbols; ++i){
		insert(H, &symbolList[i]);

		if(H->loadFactor > maxLoad){
			int newSize = (int)((double)H->size * (double)resizeFactor);
			struct hashTable* Hnew = createEmptyHashTable(newSize);
			Hnew -> insertionTime = H -> insertionTime;

			transfer(Hnew, H);
			free(H);
			H = Hnew;
		}
		if(H->loadFactor < minLoad){
			int newSize = (int)((double)H->size / (double)resizeFactor);
			struct hashTable* Hnew = createEmptyHashTable(newSize);
			Hnew -> insertionTime = H -> insertionTime;

			transfer(Hnew, H);
			free(H);
			H = Hnew;
		}
	}

	printf("%d\t%d\t%lf\t%d\t%d\n", H->entries, H->size, H->loadFactor, H->freeSlots, H->insertionTime);
	// print(H);
	return H;
}

void lookupQueries(struct hashTable* H){
	int i;
	for(i=0; i<numQueries; ++i){
		int index = calc_sum(&queryList[i]) % H->size;

		int t = findSymbol(&(H->buckets[index]), &queryList[i]);
		H->queryingTime += t;
	}

	printf("%d\t%d\n", numQueries, H->queryingTime);
}

int main(){
	int choice;
	int i,j;
	int exit_flag = 0;

	struct hashTable* H;

	while(exit_flag != 1){
		scanf("%d", &choice);

		if(choice==0) readSymbols();

		if(choice==1) readQueries();

		if(choice==2) H = createHashTable();

		if(choice==3) lookupQueries(H);

		if(choice==-1) exit_flag = 1;
	}

	return 0;
}