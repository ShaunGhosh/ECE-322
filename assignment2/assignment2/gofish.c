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
	printf("Shuffling deck...\n\n"); //1) print Shuffling deck...

	shuffle();//2) shuffle the deck initialize deck and shuffle the deck

	deal_player_cards(&user);//3) Deal user cards

	deal_player_cards(&computer);//4) Deal computer cards

	//Scenario #1 : Player has to draw a card

	//5) print Player 1's Hand - ...
	//6) print Player 1's Book - ...
	//7) print Player 2's Book - ...
	//8) print Player x's turn, enter a Rank: (2,3,4,5,6,7,8,9,10,J,Q,K,A)
	//9) print   -Player (1-x) has no Rank's
	//10)print   -Go Fish, Player x draws blah
	//11)print   -Player (1-x)'s turn

	//Scenario #2 : Player claims cards from opponent

	//5) print Player 1's Hand - ...
	//6) print Player 1's Book - ...
	//7) print Player 2's Book - ...
	//8) print Player x's turn, enter a Rank: (2,3,4,5,6,7,8,9,10,J,Q,K,A)
	//9) print   -Player (1-x) has (*Rank cards)
	//10)print   -Player x has (*Rank cards)
	//11)print   -Player x has books Rank
	//12)print   -Player x gets another turn

	//Scenario #3 : Player does not have at least one card from Rank to play
	//print Player x's turn, enter a Rank: (2,3,4,5,6,7,8,9,10,J,Q,K,A)
	//print Error - must have at least one card from rank to play

	//Scenario #4 : Player has won the game!
	//5) print Player 1's Hand - (Blank)  These must have been reset on gameover
	//6) print Player 1's Book - 3 2 J A 6 Q 8
	//7) print Player 2's Book - 9 5 10 4 5 K
	//8) print Player 1 Wins! 7-6         (Number for winner (always 7)  -  Loser (less than 7) )
	//9) print 
	//10)print Do you want to play again [Y/N]:N
	//11)print Exiting.

	//All of these scenarios will be broken up into two functions: user_play and computer_play
	//Their format will be similar to that of above print scenarios

	//Joe Mitchell [END]
	//call user play function
}
