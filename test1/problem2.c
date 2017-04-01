#include "linkedList.h"
#include <string.h>

int main(){
	struct WordList* sentence = (struct WordList*) malloc(sizeof(struct WordList));
	
	int flag = 0; //exit flag
	int i,j;
	int inp;
	int num_words;
	int n;
	
	while(flag == 0){
		scanf("%d", &inp);
		switch(inp){
			case 1:
				scanf("%d", &num_words);
				char str[1000];
				for(i=0; i<num_words; ++i){
					struct CharList* curr_word = (struct CharList*) malloc(sizeof(struct CharList));
					scanf("%s", str);
					for(j=0; j<strlen(str); ++j)
						insertCharAtEnd(curr_word, str[j]);

					insertWordAtEnd(sentence,curr_word);
				}
				break;

			case 2:
				scanf("%d", &n);
				printNthWord(sentence,n);
				break;

			case 3:
				printAllWords(sentence);
				break;

			case 4:
				scanf("%d", &n);
				sortCharList(sentence, n);
				printNthWord(sentence, n);
				break;
			
			case 5:
				sortAllCharLists(sentence);
				printAllWords(sentence);
				break;

			case 6:
				sortWordList(sentence);
				printAllWords(sentence);
				break;

			case -1:
				flag = 1;
				break;
		}
	}
							
	return 0;
}


