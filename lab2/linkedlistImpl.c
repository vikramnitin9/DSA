#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void insertInFront(struct linkedList* list, int data){
	if(list == NULL) return;

	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node -> data = data;
	new_node -> next = list -> first;
	list->first = new_node;
	traverse(list);
}

void insertAtEnd(struct linkedList* list, int data){
	if(list == NULL) return;

	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node -> data = data;
	new_node -> next = NULL;
	
	if(list->first == NULL){
		list->first = new_node;
		traverse(list);
		return;
	}

	struct node* curr = list->first;

	while(curr->next != NULL){
		curr = curr->next;
	}
	curr -> next = new_node;

	traverse(list);
}

struct node* deleteFromFront(struct linkedList* list){
	if(list == NULL || list -> first == NULL){
		printf("-2\n");
		return NULL;
	}
	struct node* deleted_node;
	deleted_node = list -> first;
	list -> first = list -> first -> next;
	deleted_node -> next = NULL;

	printf("%d\n",deleted_node -> data);
	return deleted_node;
}

struct node* deleteAtEnd(struct linkedList* list){
	if(list == NULL || list -> first == NULL){
		printf("-2\n");
		return NULL;
	}
		
	struct node* curr = list->first;
	struct node* prev = list->first;
		
	if(list->first->next == NULL){ //if there's only one element
		curr = list->first;
		list->first = NULL;
	}

	while(curr->next != NULL){
		prev = curr;
		curr = curr->next;
	}

	prev -> next = NULL;

	printf("%d\n",curr -> data);
	return curr;
}

void traverse(struct linkedList* list){
	if(list == NULL) return;

	struct node* curr = list->first;

	while(curr != NULL){
		printf("%d\t",curr -> data);
		curr = curr->next;
	}
	printf("\n");
}
