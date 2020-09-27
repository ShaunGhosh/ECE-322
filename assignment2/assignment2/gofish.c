#include <stdio.h>
#include "deck.h"
#include "player.h"
#include "card.h"


void print_hand(struct player* target){
	struct hand* temp;
	int i = 1;

	temp = target->card_list;
	while(temp != NULL){
		printf("%c%c%c ", temp->top.suit, temp->top.rank[1], temp->top.rank[0]);
		temp = temp->next;
		i++;
	}
}


int main(int args, char* argv[]) 
{
	//Joe Mitchell [START]
	printf("Shuffling deck...\n\n");

	shuffle();//initialize deck and shuffle the deck

	printf("Deck card number: %d", deck_instance.top_card);


	struct player* user1 = &user;
	struct player* computer1 = &computer;


	deal_player_cards(user1);
	deal_player_cards(computer1);

	printf("Players hand: ");
	print_hand(user1);
	printf("\n\nComputer's hand: ");
	print_hand(computer1);
	//Joe Mitchell [END]
	//call user play function
}
