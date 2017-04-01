#include <stdio.h>
#include <stdlib.h>

struct node{
	char data;
	struct node* next;
};

struct CharList{
	struct node* first;
	struct node* last;
};

struct word{
	struct CharList* data;
	struct word* next;
};

struct WordList{
	struct word* first;
	struct word* last;
};

void insertWordAtEnd(struct WordList* list, struct CharList* data);
void insertCharAtEnd(struct CharList* list, char data);
void printWord(struct CharList* list);
void printNthWord(struct WordList* list, int n);
void printAllWords(struct WordList* list);

void sortCharList(struct WordList* list, int n);
void insertSort(struct CharList* list);
void sortAllCharLists(struct WordList* list);
int compareCharLists(struct CharList* list1, struct CharList* list2);
void sortWordList(struct WordList* list);
