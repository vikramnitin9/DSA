#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main(int argc, char *argv[]){
	struct linkedList* list = (struct linkedList*) malloc(sizeof(struct linkedList));
	list -> first = NULL;
	list -> count = 0;
	
	int choice, data;

	while(choice!=-1){
		scanf("%d", &choice);

		switch(choice){
			case 0:
				scanf("%d", &data);
				insertInFront(list, data);
				break;
			case 1:
				scanf("%d", &data);
				insertAtEnd(list, data);
				break;
			case 2:
				deleteFromFront(list);
				break;
			case 3:
				deleteAtEnd(list);
				break;
			case 4:
				traverse(list);
				break;
			case -1:
				break;
		}
	}

	return 0;
}

