#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"

//Add card adds a card to the player's hand
//Joseph Mitchell
int add_card(struct player* target, struct card* new_card){
	//Should only add card if the card doesn't already exist in their hand!
	/*
	struct hand* target_hand = target->card_list;
	while(target_hand != NULL){
		if((target_hand->top.suit == new_card->suit)
			&& (target_hand->top.rank[1] == new_card->rank[1])
			&& (target_hand->top.rank[0] == new_card->rank[0]) ){
			return 0; // Player already has this card!
		}
		target_hand = target_hand->next;
	}
	*/
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand));
	if(temp == NULL){ return -1; }

	temp->top = *new_card;
	temp->next = target->card_list;

	target->card_list = temp;

	target->hand_size++;
	
	check_add_book(target);
	
	return 1;
}
//Removes a card from the players hand
//Joseph Mitchell
int remove_card(struct player* target, struct card* old_card){
	
	struct hand* iterator = target->card_list;
	struct hand* previous = NULL;



	if(iterator == NULL) {return 0;}
	while( ! ( (iterator->top.suit == old_card->suit)   &&   (iterator->top.rank[0] == old_card->rank[0]) ) ){
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
	

	target->hand_size--;
	
	

	return 1;
}
//Joseph Mitchell
void print_books(struct player* target){
	int i;
	for(i=0;i<=6;i++){
		printf("%c",target->book[i]);
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

	while(iterator != NULL){
		if(iterator->top.rank[0] == rank){
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
		int count = count_rank_cards(target,rank);
		//printf("%d\n",count);
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
		if(iterator->top.rank[0] == rank){
			//match = &(iterator->top);
			//remove_card(target,&(iterator->top));
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
	while(search(src,rank)){
		count += remove_single_rank(src,dest,rank);
	}
	//printf("%d",count);
	return count;
}

//Shaun Ghosh
int gameover(struct player* target){
	if((*target).book[6] != '\0'){
		return 1;
	}
	else{
		return 0;
	}
}
//Shaun Ghosh
int search(struct player* target,char rank){
	struct hand* list = target->card_list;
	if(list == NULL){return 0;}
	while(list->top.rank[0] != rank){
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
	target->card_list = NULL;
	free(target->card_list);
	//2) Empty the player's book
	int i;
	for(i=0;i<=6;i++){
		target->book[i] = '\0';
	}
	//3) Set hand_size to 0
	target->hand_size = 0;

/*
	int *ptr = &((*target).book);
	while(ptr != NULL){
		*ptr = '\0';
		ptr++;
	}
	//free memory of the item
	free((*target).card_list);
	//change direction of the pointer to an empty space
 	(*target).card_list = NULL;
 	//verify if pointer points to NULL
*/ 
	return 0;
}

//Shaun Ghosh
char computer_play(struct player* target){
	srand(time(0));
	struct hand* iterator1 = (*target).card_list;
	int count = 0;
	while (iterator1 != NULL){
		count++;
		iterator1 = (*iterator1).next;
	}
	int num = rand() % count;
	int i;
	struct hand* iterator2 = (*target).card_list;
	for(i=0; i<num; i++){
		iterator2 = (*iterator2).next;
	}
	return (*iterator2).top.rank[0];
}

//Shaun Ghosh
char user_play(struct player* target){
	char input;
	scanf("%c", &input);
	while(search(target, input) != 1){
		printf("\nError - must have at least one card from rank to play \n");
		scanf("%c", &input);
	}
	return input;
}

/*
void clear_player_hand(struct player* target){
	target->card_list = NULL;//This is the reset of the player's hand
	free(target->card_list);//This is freeing the reset of the player's hand
}
*/
/*
int main(){
	//These will be declared in an initialization function!
	//The parameters of these pointers need to be passed to the function properly

	struct card new_card,new_card1,new_card2,new_card3,new_card4;
	//Should remove all four of these cards!!!
	new_card.suit='D';
	new_card.rank[1]='6';
	new_card1.suit='H';
	new_card1.rank[1]='6';
	new_card2.suit='C';
	new_card2.rank[1]='6';
	new_card3.suit='S';
	new_card3.rank[1]='6';

	new_card4.suit='C';
	new_card4.rank[1]='9';

	add_card(&user,&new_card);
	add_card(&user,&new_card1);
	add_card(&user,&new_card2);
	add_card(&user,&new_card3);

	add_card(&user,&new_card4);

	struct card cardz;
	cardz.suit='S';
	cardz.rank[1]='6';

	printf("Player's Hand: ");
	print_hand(&user);

	printf("\nPlayer's Books: \n");

	print_books(&user);

	return 0;

}
*/
