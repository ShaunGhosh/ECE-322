#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"


void init(){
	//Use integer arrays to represent chars
	deck_instance.top_card = 0; //Make sure the top card of the deck is the 0th element!
	int suit[] = {67,83,72,68}; //Ascii values for 'C' 'H' 'S' 'D' [Not in that order]
	int rank[] = {50,51,52,53,54,55,56,57,74,81,75,65}; //Ascii values for 2-9 and 'J' 'Q' 'K' 'A'  10 is added at the end!

	int size = (sizeof(deck_instance.list) / sizeof(deck_instance.list[0]) ); //Find size of the deck
	int deck_size = 0; 
	int i,j;
	for(i = 0; i <= 3; i++){//Loop through the suits
		for(j = 0; j <= (size/4)-1; j++){//Loop through the ranks
			deck_instance.list[deck_size].suit=suit[i]; //Access the deck using deck_instance header file attribute
			deck_instance.list[deck_size].rank[1]=' ';
			if(j==12){//Rank needs to be 10
				deck_instance.list[deck_size].rank[0]=48;
				deck_instance.list[deck_size].rank[1]=49;
			}
			else{
				deck_instance.list[deck_size].rank[0]=rank[j];
			}
			deck_size++;
		}
	}
}

void display_deck(){
	int size = (sizeof(deck_instance.list) / sizeof(deck_instance.list[0]) );
	int i;
	for(i = deck_instance.top_card; i <= size; i++){
		printf("%c%c%c\n",deck_instance.list[i].suit,deck_instance.list[i].rank[1],deck_instance.list[i].rank[0]);
	}
}

int shuffle(){
	init();//initialize the deck's 52 cards
	srand(time(0)); //Set random seed based on current time

	int deck_size = ( sizeof(deck_instance.list) / sizeof(deck_instance.list[0]) );

	int i;
	for(i=0; i<=deck_size; i++){//Loop for shuffle
		int s1 = (rand() % deck_size ); //random number from 0 to 52 for first slot
		int s2 = (rand() % deck_size ); //random number from 0 to 52 for second slot

		struct card temp1 = deck_instance.list[s1], temp2 = deck_instance.list[s2];

		deck_instance.list[s2] = temp1; //Swap the cards in the deck for s1 vs s2 randomly!
		deck_instance.list[s1] = temp2;
	}
	return 1;
}

int deal_player_cards(struct player* player){
	//Use linked list techniques
	int i;
	for(i = 0; i <= 6; i++){
		if(deck_instance.top_card == 51){ return -1; } //If deck is empty return -1
		add_card(player,next_card()); //add_card is a player function
	}
}

size_t deck_size(){
	return 52-deck_instance.top_card;
}

struct card* next_card(){
	struct deck* top_card = &deck_instance;

	struct card* top = &(top_card->list[deck_instance.top_card]);

	deck_instance.top_card++;
	return top;
}

void display_hand(){
	struct hand* users_hand = user.card_list;
	int i = 1;

	while(users_hand != NULL){
		printf("%c%c%c ",users_hand->top.suit,users_hand->top.rank[0],users_hand->top.rank[1]);
		users_hand = users_hand->next;
		i++;
	}
}

/*
int main(){

	init();
	printf("Display Deck: \n");
	display_deck();

	//shuffle();

	//printf("After deck shuffle\n");

	//display_deck();

	//printf("%d",deck_size());

	//struct player* player = &user;

	//deal_player_cards(player);

	struct player* user1 = &user;

	//struct card* next = next_card();

	//printf("%c%c\n",next->suit,next->rank[0]);
	//printf("%d",deck_instance.top_card);

	deal_player_cards(user1);

	printf("\n\n%c\n\n",check_add_book(user1));

	printf("Display hand: \n");
	display_hand();


	return 0;
}
*/
