#include "linkedList.h"

void insertWordAtEnd(struct WordList* list, struct CharList* data){
	if(list == NULL) return;
	struct word* new_word = (struct word*) malloc(sizeof(struct word));
	new_word -> data = data;
	new_word -> next = NULL;

	if(list -> last == NULL){
		list -> first = new_word;
		list -> last = new_word;
		return;
	}
	
	list -> last -> next = new_word;
	list -> last = new_word;
}

void insertCharAtEnd(struct CharList* list, char data){
	if(list == NULL) return;
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node -> data = data;
	new_node -> next = NULL;

	if(list -> last == NULL){	
		list -> first = new_node;
		list -> last = new_node;
		return;
	}
	
	list -> last -> next = new_node;
	list -> last = new_node;
}

void printWord(struct CharList* list){
	if(list == NULL) return;
	struct node* curr = list -> first;
	while(curr != NULL){
		printf("%c ", curr->data);
		curr = curr -> next;
	}
	printf("\n");
}

void printAllWords(struct WordList* list){
	if(list == NULL) return;
	if(list -> first == NULL) return;
	
	struct word* curr = list -> first;
	
	while(curr != NULL){
		printWord(curr -> data);
		curr = curr -> next;
	}
}

void printNthWord(struct WordList* list, int n){
	if(list == NULL) return;
	if(list -> first == NULL) return;

	struct word* curr = list -> first;
	int i;
	for(i=1; i<n; ++i){
		curr = curr -> next;
	}
	printWord(curr -> data);
}

void sortCharList(struct WordList* list, int n){
	if(list == NULL) return;
	if(list -> first == NULL) return;

	struct word* curr = list -> first;
	int i;
	for(i=1; i<n; ++i){
		curr = curr -> next;
	}
	insertSort(curr -> data);
}

void insertSort(struct CharList* list){
	if(list == NULL) return;
	if(list -> first == NULL) return;
	if(list -> first -> next == NULL) return;
	
	struct node* curr = list -> first -> next;
	struct node* prev = list -> first;

	while(curr != NULL){
		//No insertion required
		if((curr -> data) >= (prev -> data)){
			prev = curr;
			curr = curr -> next;
			continue;
		}
		//Insert in Order procedure begins
		struct node* next = curr -> next;

		struct node* temp = list -> first;
		struct node* prev_temp = list -> first;

		while(temp != curr && temp!=NULL){
			if((temp -> data) >= (curr -> data)){
				if(temp == list -> first){ //Insert at beginning
					list -> first = curr;
					curr -> next = temp;
				}
				else{
					prev_temp -> next = curr;
					curr -> next = temp;
				}
				break;
			}

			prev_temp = temp;
			temp = temp -> next;
		}
		//Insert in Order procedure ends
		prev -> next = next; //Filling the gap left
		curr = next;
	}
}

void sortAllCharLists(struct WordList* list){
	if(list == NULL) return;
	if(list -> first == NULL) return;

	struct word* curr = list -> first;
	int i;
	while(curr != NULL){
		insertSort(curr -> data);
		curr = curr -> next;
	}
}

int compareCharLists(struct CharList* list1, struct CharList* list2){
	if(list1 == NULL) return 0;
	if(list2 == NULL) return 1;

	struct node* ptr1 = list1 -> first;
	struct node* ptr2 = list2 -> first;
	
	while(ptr1 != NULL && ptr2 != NULL){
		if((ptr1 -> data) > (ptr2 -> data)) return 1;
		if((ptr1 -> data) < (ptr2 -> data)) return 0;
		ptr1 = ptr1 -> next;
		ptr2 = ptr2 -> next;
	}
	//If control comes here, one word is a prefix of another
	if(ptr1 == NULL) return 0;
	else return 1;
}

void sortWordList(struct WordList* list){
	if(list == NULL) return;
	if(list -> first == NULL) return;
	if(list -> first -> next == NULL) return;
	
	struct word* curr = list -> first -> next;
	struct word* prev = list -> first;

	while(curr != NULL){
		//No insertion required
		if(compareCharLists(curr->data, prev->data)){
			prev = curr;
			curr = curr -> next;
			continue;
		}
		//Insert in Order procedure begins
		struct word* next = curr -> next;

		struct word* temp = list -> first;
		struct word* prev_temp = list -> first;

		while(temp != curr){
			if(compareCharLists(temp->data, curr->data)){
				if(temp == list -> first){ //Insert at beginning
					list -> first = curr;
					curr -> next = temp;
				}
				else{
					prev_temp -> next = curr;
					curr -> next = temp;
				}
				break;
			}

			prev_temp = temp;
			temp = temp -> next;
		}
		//Insert in Order procedure ends
		prev -> next = next; //Filling the gap left
		curr = next;
	}
}
