#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void constructCircular(struct linkedList* list){
	struct node* n[5];
	for(int i=0; i<5; ++i){
		n[i] = (struct node*) malloc(sizeof(struct node));
	}
	list -> first = n[0];

	n[0] -> next = n[1];
	n[1] -> next = n[2];
	n[2] -> next = n[3];
	n[3] -> next = n[4];
	n[4] -> next = n[2];
}

int main(int argc, char *argv[]){
	struct linkedList* list = (struct linkedList*) malloc(sizeof(struct linkedList));
	struct node *hare, *tortoise;
	
	struct node* n[1000];

	int i = 0;
	int curr_index,prev_index,data;

	while(true){
		scanf("%d %d",&index,&data);

		n[i] = (struct node*) malloc(sizeof(struct node));
		
		

	hare = tortoise = list -> first;
	
	hare = hare->next->next;
	tortoise = tortoise->next;

	int flag = 0;

	for(i=0; i<1000; ++i){
		if(hare == tortoise){
			flag = 1;
			break;
		}
		if(hare->next == NULL) break;
		
		hare = hare->next->next;
		tortoise = tortoise->next;		
	}
	if(flag == 1)
		printf("The list has a cycle\n");
	else
		printf("The list doesn't have a cycle\n");
	
	return 0;
}

