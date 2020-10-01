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
				deck_instance.list[deck_size].rank[0]=48;//Initializes rank[0] to 0
				deck_instance.list[deck_size].rank[1]=49;//Initializes rank[1] to 1
			}
			else{
				deck_instance.list[deck_size].rank[0]=rank[j];//Non 10 rank
			}
			deck_size++;//Increase deck size (will be 52)
		}
	}
}

void display_deck(){
	int size = (sizeof(deck_instance.list) / sizeof(deck_instance.list[0]) );
	int i;
	for(i = deck_instance.top_card; i <= size; i++){//For each card display all 3 characters
		printf("%c%c%c\n",deck_instance.list[i].suit,deck_instance.list[i].rank[1],deck_instance.list[i].rank[0]);
	}//Used to test deck
}

int shuffle(){
	init();//initialize the deck's 52 cards
	srand(time(0)); //Set random seed based on current time

	int deck_size = ( sizeof(deck_instance.list) / sizeof(deck_instance.list[0]) );//52

	int i;
	for(i=0; i<=deck_size; i++){//Loop for shuffle
		int s1 = (rand() % deck_size ); //random number from 0 to 52 for first slot
		int s2 = (rand() % deck_size ); //random number from 0 to 52 for second slot

		struct card temp1 = deck_instance.list[s1], temp2 = deck_instance.list[s2];
		//initialize 2 cards to swap positions in the deck (This is called shuffling)
		deck_instance.list[s2] = temp1; //Swap the cards in the deck for s1 vs s2 randomly!
		deck_instance.list[s1] = temp2;
	}
	return 1;//It has shuffled correctly
}

int deal_player_cards(struct player* player){
	//Use linked list techniques
	int i;
	for(i = 0; i <= 6; i++){//Each target player will be dealt 7 cards
		if(deck_instance.top_card == 52){ return -1; } //If deck is empty return -1
		add_card(player,next_card()); //add_card is a player function
	}
}

size_t deck_size(){
	return 52-deck_instance.top_card;//top_card is an index to the first card in the deck
}//Therefore 52 - index of the deck yeilds the decks current size

struct card* next_card(){
	struct deck* top_card = &deck_instance;//Make a deck pointer

	struct card* top = &(top_card->list[deck_instance.top_card]);//Pop off the top card of the deck [Nothing is removed from the deck!]  

	deck_instance.top_card++;//Increase the deck top card index
	return top;//Return the top card pointer.
}

void display_hand(){
	struct hand* users_hand = user.card_list;//Grab the hand of target player by the pointer

	while(users_hand != NULL){//If hand is not null print each character from each of their cards in order of Suit, Tens, Ones
		printf("%c%c%c ",users_hand->top.suit,users_hand->top.rank[0],users_hand->top.rank[1]);
		users_hand = users_hand->next;//Move to the next card in hand
	}
}

/*
int main(){

	Was used to test deck functions...


	return 0;
}
*/
