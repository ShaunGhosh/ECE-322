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

	struct card card1,card2,card3,card4,card5;

	char rank = '5';

	card1.suit='C';
	card1.rank[0]=rank;
	card2.suit='H';
	card2.rank[0]=rank;
	card3.suit='D';
	card3.rank[0]=rank;
	card4.suit='S';
	card4.rank[0]=rank;

	card5.suit='D';
	card5.rank[0]='7';

	add_card(&user,&card1);
	//add_card(&user,&card2);
	//add_card(&user,&card5);
	//add_card(&user,&card3);
	//add_card(&user,&card4);

	printf("\nUser hand (%d cards) : ",user.hand_size);
	print_hand(&user); //Should not have any cards of the book!
	printf("\nUser Books: ");
	print_books(&user);


	printf("Search?: %d",search(&user,'2'));

	//Joe Mitchell [END]
	//call user play function

	printf("resetting player: %d", reset_player(&user));
	printf("new user's hand after resetting: ");
	print_hand(&user);
	printf("\nUser Books after resetting: ");
	print_books(&user);

}
