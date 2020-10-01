#include <stdio.h>
#include "deck.h"
#include "player.h"
#include "card.h"

//In order for user or computer to signify rank 10, they type '0'
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

void interface(){
	printf("\n\nPlayer 1's Hand - ");
	print_hand(&user);
	printf("\nPlayer 1's Book - ");
	print_books(&user);
	//For testing purposes
	printf("\nPlayer 2's Hand - ");
	print_hand(&computer);
	//For Testing purposes
	printf("\nPlayer 2's Book - ");
	print_books(&computer);
}

void user_hit(char rank){
	printf("\n\nPlayer 2 has");
	print_rank_cards(&computer,rank);
	printf("\nPlayer 1 has");
	print_rank_cards(&user,rank);
	//Transfer the cards from computer to user
	transfer_cards(&computer,&user,rank);
	printf("\nPlayer 1 has books ");
	print_books(&user);
	printf("\nPlayer 1 gets another turn");
	//Gameover condition check
	if(gameover(&user)){
		int i=0;
		while(computer.book[i] != '\0'){
				i++;
		}
		printf("\nPlayer 1 wins 7-%d",i);
		printf("\nDo you want to play again? [Y/N] : ");
		char input;
		scanf("%c",&input);
		while(input != 'N' && input != 'Y'){
			printf("\nInvalid input must be 'N' or 'Y': ");
			scanf("%c",&input);
		}
		if(input == 'N'){
			printf("\nExiting...");
			exit(0);
		}else{
			//printf("%c",input);
			printf("\n\n");
			reset_player(&user);
			reset_player(&computer);
			deal_player_cards(&user);
			deal_player_cards(&computer);
			shuffle();
			deck_instance.top_card = 0; //Bring top card back to deck!
			user_turn();
		}
	}
	user_turn();
}

void computer_gofish(char rank){
	interface();
	printf("\n\nPlayer 1 has no %c's",rank);
	struct card* new_card = next_card();
	add_card(&computer,new_card); //Computer draws off the top of the deck!
	printf("\nPlayer 2 draws %c%c%c",new_card->suit,new_card->rank[0],new_card->rank[1]);
	printf("\nPlayer 1's turn");
	//Gameover condition check
	if(gameover(&computer)){
		int i=0;
		while(user.book[i] != '\0'){
				i++;
		}
		printf("\nPlayer 2 wins 7-%d",i);
		printf("\nDo you want to play again? [Y/N] : ");
		char input;
		scanf("%c",&input);
		while(input != 'N' && input != 'Y'){
			printf("\nInvalid input must be 'N' or 'Y': ");
			scanf("%c",&input);
		}
		if(input == 'N'){
			printf("\nExiting...");
			exit(0);
		}else{
			printf("\n\n");
			reset_player(&user);
			reset_player(&computer);
			deal_player_cards(&user);
			deal_player_cards(&computer);
			shuffle();
			deck_instance.top_card = 0; //Bring top card back to deck!
			user_turn();
		}
	}
	//exit(0); //For Debugging purposes
	user_turn();
}

void user_turn(){
	interface();
	printf("\n\nPlayer 1's turn, enter a Rank: "); //User's turn
	char rank = user_play(&user);
	if(search(&computer,rank)){
		user_hit(rank);
	}else{
		//User Draws a card and Computer's turn
		user_gofish(rank);
	}
}

void computer_hit(char rank){
	interface();
	printf("\n\nPlayer 2 has");
	print_rank_cards(&computer,rank);
	printf("\nPlayer 1 has");
	print_rank_cards(&user,rank);
	//Transfer the cards from computer to user
	transfer_cards(&user,&computer,rank);
	printf("\nPlayer 2 has books ");
	print_books(&computer);
	printf("\nPlayer 2 gets another turn");
	//exit(0); //For Debugging Puroses
	//Gameover condition check
	if(gameover(&computer)){
		int i=0;
		while(user.book[i] != '\0'){
				i++;
		}
		printf("\nPlayer 2 wins 7-%d",i);
		printf("\nDo you want to play again? [Y/N] : ");
		char input;
		scanf("%c",&input);
		while(input != 'N' && input != 'Y'){
			printf("\nInvalid input must be 'N' or 'Y': ");
			scanf("%c",&input);
		}
		if(input == 'N'){
			printf("\nExiting...");
			exit(0);
		}else{
			printf("\n\n");
			reset_player(&user);
			reset_player(&computer);
			deal_player_cards(&user);
			deal_player_cards(&computer);
			shuffle();
			deck_instance.top_card = 0; //Bring top card back to deck!
			user_turn();
		}
	}
	computer_turn();
}

void user_gofish(char rank){
	printf("\n\nPlayer 2 has no %c's",rank);
	struct card* new_card = next_card();
	add_card(&user,new_card); //User draws off the top of the deck!
	printf("\nPlayer 1 draws %c%c%c",new_card->suit,new_card->rank[1],new_card->rank[0]);
	printf("\nPlayer 2's turn");
	//Gameover condition check
	if(gameover(&user)){
		int i=0;
		while(computer.book[i] != '\0'){
				i++;
		}
		printf("\nPlayer 1 wins 7-%d",i);
		printf("\nDo you want to play again? [Y/N] : ");
		char input;
		scanf("%c",&input);
		while(input != 'N' && input != 'Y'){
			printf("\nInvalid input must be 'N' or 'Y': ");
			scanf("%c",&input);
		}
		if(input == 'N'){
			printf("\nExiting...");
			exit(0);
		}else{
			printf("\n\n");
			reset_player(&user);//reset player's hand, book, and hand size
			reset_player(&computer);//reset player's hand,book, and hand size
			deal_player_cards(&user);//deal player cards
			deal_player_cards(&computer);//deal player cards
			shuffle();//shuffle the deck
			deck_instance.top_card = 0; //Bring top card back to deck!
			user_turn();//User always starts!
		}
	}
	//exit(0); //Debugging purposes
	computer_turn();
}

void computer_turn(){
	interface();
	printf("\n\nPlayer 2's turn, enter a Rank: "); //User's turn
	char rank = computer_play(&computer);
	
	printf("%c",rank);
	//exit(0); //For Debugging purposes
	if(search(&user,rank)){
		computer_hit(rank);//After rank given, if user has a card of that rank, claim all of them and take another turn
	}else{
		//User Draws a card and Computer's turn
		computer_gofish(rank);//User didn't have a card of that rank
	}
}



void print_rank_cards(struct player* target,char rank){
	struct hand* list = target->card_list;
	while(list != NULL){//While node is not null check for rank and print rank card Suit,Tens,Ones
		if(list->top.rank[0] == rank){
			printf(" %c%c%c ", list->top.suit, list->top.rank[1], list->top.rank[0]);//Print rank cards that target player has
		}
		list = list->next;//Next card
	}
}


int main(int args, char* argv[]) 
{
	
	//Joe Mitchell [START]
	
	printf("Shuffling deck...\n\n"); //1) print Shuffling deck...

	shuffle();//2) shuffle the deck initialize deck and shuffle the deck

	deal_player_cards(&user);
	deal_player_cards(&computer);

	//User go first?
	
	while(1){
		//user_turn();
		interface();
		printf("\nPlayer 1's turn, enter a Rank: "); //User's turn
		char rank = user_play(&user);
		if(search(&computer,rank)){
			user_hit(rank);
		}else{
			user_gofish(rank);
		}
	}

	
	
	/*
	user.book[0] = '5';
	computer.book[1] = '6';
	
	printf("\nUsers Hand: ");
	print_hand(&user);
	printf("\nUsers Book: ");
	print_books(&user);
	printf("\nComputers Hand: ");
	print_hand(&computer);
	printf("\nComputers Book: ");
	print_books(&computer);
	
	
	
	reset_player(&user);
	reset_player(&computer);
	deal_player_cards(&user);
	deal_player_cards(&computer);
	shuffle();
	deck_instance.top_card = 0; //Bring top card back to deck!

	printf("\nAfter Reset! : ");
	printf("\nUsers Hand: ");
	print_hand(&user);
	printf("\nUsers Book: ");
	print_books(&user);
	printf("\nComputers Hand: ");
	print_hand(&computer);
	printf("\nComputers Book: ");
	print_books(&computer);
	*/
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
	return 0;
}
