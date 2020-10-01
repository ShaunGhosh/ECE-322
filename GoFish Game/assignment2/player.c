#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"



//Add card adds a card to the player's hand
//Joseph Mitchell
int add_card(struct player* target, struct card* new_card){
	
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand));//Allocate memory to add to the Linked List
	if(temp == NULL){ return -1; }

	temp->top = *new_card; //Prepend card to the top of the hand!
	temp->next = target->card_list;//Make the head of the hand be the next node of the
										//Linked List
	target->card_list = temp;//Reassign the players hand to the modified list

	target->hand_size++;//Increase the player's hand by 1
	
	check_add_book(target); // Check to make sure the player has a book.
	
	
	return 1;
}
//Removes a card from the players hand
//Joseph Mitchell
int remove_card(struct player* target, struct card* old_card){
	
	struct hand* iterator = target->card_list; //iterator points to head of linked list
	struct hand* previous = NULL;//Previous node points to null

	if(iterator == NULL) {return 0;}
	while( ! ( (iterator->top.suit == old_card->suit)   &&   (iterator->top.rank[0] == old_card->rank[0]) ) ){
		previous = iterator;//If element is not the desired element to remove
		iterator = iterator->next;//Change its pointers so that they sift through the 
		if(iterator == NULL){//Linked List
			return 0;
		}
	}
	//We have found the item to remove
	if(previous != NULL){
		previous->next = iterator->next; //Point Previous to next in the case where it is
	}else{									//not null
		target->card_list = iterator->next; //Reassign the list to the new head in the case where the 
	}										//item to remove is the head of the list
	
	target->hand_size--; // Decrement the size of the target player's hand (usefull for random implementation later)
	
	free(iterator); // Free the pointer from unused memory.
	
	return 1;
}
//Joseph Mitchell
void print_books(struct player* target){
	int i;
	for(i=0;i<=6;i++){
		printf(" %c ",target->book[i]); //Print each target player book
	}
}

//Helper function to check_add_book
//Joseph Mitchell
int add_to_book(struct player* target,char rank){
	int i;
	for(i=0; i <= 6; i++){
		if(target->book[i] == '\0'){
			target->book[i] = rank; //Will be modified on print out!
			return 1;
		}
	}
}
//Joseph Mitchell
int count_rank_cards(struct player* target,char rank){
	int i=0;
	struct hand* iterator = target->card_list;
	//Iterate through linked list counting all of the rank cards for target player
	while(iterator != NULL){//While iterator still has nodes to sift through
		if(iterator->top.rank[0] == rank){//if the rank is equal to desired rank increment count.
			i++;
		}
		iterator = iterator->next;
	}

	return i;
}
//Joseph Mitchell
char check_add_book(struct player* target){
	struct hand* iterator = target->card_list;
	int count;
	if(iterator == NULL){ return 0; }
	while(iterator != NULL){
		char rank = iterator->top.rank[0];
		int count = count_rank_cards(target,rank); //count the total number of rank cards in target players hand
		if(count == 4){
			//remove all 4 suits from player's hand
			//printf("I have made it here!");
			//remove_all_rank(target,rank);

			struct card card1,card2,card3,card4;
			card1.suit='C';
			card1.rank[0]=rank;
			card2.suit='H';
			card2.rank[0]=rank;
			card3.suit='D';
			card3.rank[0]=rank;
			card4.suit='S';
			card4.rank[0]=rank;
			
			remove_card(target,&card1);
			remove_card(target,&card2);
			remove_card(target,&card3);
			remove_card(target,&card4);

			//remove_all_rank(target,rank);
			add_to_book(target,rank);
			return rank;
		}

		count=0;
		iterator = iterator->next;
	}
	return '\0';//null char will indicate no books!
}

int remove_single_rank(struct player* target,struct player* dest, char rank){
	struct hand* iterator = target->card_list;
	char match;
	while(iterator != NULL){
		if(iterator->top.rank[0] == rank){//Find the card of particular rank in linked list
			add_card(dest,&(iterator->top));//have to add the card first
			remove_card(target,&(iterator->top) );//Then we remove the card!
			return 1;
		}
		iterator = iterator->next;
	}
}

//Shaun Ghosh
int transfer_cards(struct player* src, struct player* dest, char rank){
	
	//What if we designed a function to remove a single rank card?
	int count = 0;
	while(search(src,rank)){//Does a card of that rank appear in the linked list?
		count += remove_single_rank(src,dest,rank);//Remove that card from the src's hand
	}
	return count;//Return the number of cards that were removed from the user's hand
}

//Shaun Ghosh
int gameover(struct player* target){
	if((*target).book[6] != '\0'){//Index used to be 6
		return 1;//Return true if the player has 7 books!
	}
	else{
		return 0;//Return false if the player does not have 7 books!
	}
}
//Shaun Ghosh
int search(struct player* target,char rank){
	struct hand* list = target->card_list;
	if(list == NULL){return 0;}
	while(list->top.rank[0] != rank){//Check the target players hand for a card of rank
		list = list->next; //Next item
		if(list == NULL){
			return 0;
		}
	}

	return 1;
}
//Shaun Ghosh
int reset_player(struct player* target){
	//1) Empty the player's hand
	target->card_list = NULL; //This resets the players hand period.
	//2) Empty the player's book
	int i;
	for(i=0;i<=6;i++){
		target->book[i] = '\0';//This reinitializes the book array to null characters
	}
	//3) Set hand_size to 0
	target->hand_size = 0;//Returns target hand size to 0.

	return 0;
}

//Shaun Ghosh
char computer_play(struct player* target){
	srand(time(0));
	int num = rand() % target->hand_size;//Random number from 0 - (handsize-1)
	int i;
	struct hand* iterator = (*target).card_list;
	for(i=0; i<num; i++){//Find the random card from the computer's hand
		iterator = (*iterator).next;
	}
	return (*iterator).top.rank[0];//Select the rank of that random card from computer's 
}										//hand to return

//Shaun Ghosh
char user_play(struct player* target){
	char input;
	scanf("%c", &input);//User enters the rank they want to take
	while(search(target, input) != 1){
		printf("\nError - must have at least one card from rank to play \n");
		scanf("%c", &input);//This is supposed to print only when the user enters a rank they don't have
	}//There was a slight logical issue with this we did not have time to fix unfortunately (This does not make our game unplayable :) )
	return input;
}

/*
int main(){
	Was used for testing...

	return 0;

}
*/
