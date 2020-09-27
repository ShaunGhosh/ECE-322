#include <stdio.h>
#include "player.h"
#include "card.h"

//Add card adds a card to the player's hand
int add_card(struct player* target, struct card* new_card){
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand));
	if(temp == NULL){ return -1; }

	temp->top = *new_card;
	temp->next = target->card_list;

	target->card_list = temp;

	target->hand_size++;

	return 1;
}
//Removes a card from the players hand
int remove_card(struct player* target, struct card* old_card){
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;
	if(iterator == NULL) {return 0;}
	while(iterator->top.suit != old_card->suit && iterator->top.rank[0] != old_card->rank[0] 
		&& iterator->top.rank[1] != old_card->rank[1]){
		previous = iterator;
		iterator = iterator->next;
		if(iterator == NULL){
			return 0;
		}
	}

	if(previous != NULL){
		previous->next = iterator->next;
	}else{
		target->card_list = iterator->next;
	}

	free(iterator);

	return 1;
}
/*
//Helper function to check_add_book
//This will add the book to the player's book list, then it will check for gameover(Shaun)!
int add_to_book(struct player* target,char rank){
	int i;
	for(i=0; i <= 6; i++){
		if(target->book[i] == NULL){
			target->book[i] = rank; //Will be modified on print out!
		}
	}
}
*/

char check_add_book(struct player* target){
	struct hand* iterator = target->card_list;
	struct hand* temp = target->card_list;
	int count;
	if(iterator == NULL){ return 0; }
	while(iterator != NULL){
		char rank = iterator->top.rank[1];
		printf("%c\n",rank);
		count++;
		iterator = iterator->next;
		//Loop through the players hand to find all occurances of that rank!
		while(temp != NULL){
			if(temp->top.rank[1] == rank){
				count++;
			}
			if(count == 4){
				//Remove all cards of that rank from players hand!
				//while(remove_card(target,rank) > 0){}
				//Add rank to player's book
				//add_to _book(target,rank);
				return rank; //This will return the rank at the least significant position [if 0 outside main logic will produce book to be '10']
			}
			temp = temp->next;
		}
		temp = target->card_list;
		count=0;
	}
	return ' ';//Space char will indicate no books!
}

int search(struct player* target, char rank){
	struct hand* iterator = (*target).card_list;
	if(iterator == NULL) { return 0;}
	while ((*iterator).top.rank[1] != rank){
		iterator = (*iterator).next;
		if (iterator == NULL){return 0;}
		}
	free(iterator);	
	return 1;
	
}

int gameover(struct player* target){
	if((*target).book[6] != '\0'){
		return 1;
	}
	else{
		return 0;
	}
}
/*
void print_hand(struct player* target){
	struct hand* temp;
	int i = 1;

	temp = target->card_list;
	while(temp != NULL){
		printf("%c%c", temp->top.suit, temp->top.rank[1]);
		temp = temp->next;
		i++;
	}

}
*/

int main(int argc, char *argv[]){
	//These will be declared in an initialization function!
	//The parameters of these pointers need to be passed to the function prope

	//print_list();
/*
	struct card* new_card1;
	struct card new_card;
	new_card.suit='D';
	new_card.rank[1]='6';
	new_card1 = &new_card;
	struct player* user1 = &user;

	add_card(user1,new_card1);
	add_card(user1,new_card1);
	add_card(user1,new_card1);
	add_card(user1,new_card1);

	//printf("%d",remove_card(user1,new_card1));

	//print_list();

	printf("\n");

	char books_ = check_add_book(user1);

	if(' ' == books_){ 
		printf("No books!");
	}else{
		printf("%c",books_);
	}
*/
	struct player Paige;
	
	struct card PW;
	PW.suit = 'C';
	PW.rank[1] = '2';
	add_card(&Paige, &PW);
	printf("%d",search(&Paige,'3'));             
	

}

