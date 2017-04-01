#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node* next;
};

struct linkedList{
	struct node* first;
	int count;
};

void insertInFront(struct linkedList* list, int data);
void insertAtEnd(struct linkedList* list, int data);
struct node* deleteFromFront(struct linkedList* list);
struct node* deleteAtEnd(struct linkedList* list);
void traverse(struct linkedList* list);
