#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int blackjack = 21;

int startMenu();
int dealerCards(int *faceCard);
int playerCards(int faceCard);
int drawCard();
int game;

int main()
{
	int choice;
	int player, dealer, faceCard, win = 3, playerBust, dealerBust;
	int money = 100;
	int bet = 10;
	srand(time(NULL));
	printf("Welcome to CLI_Blackjack! Dealer must draw to 16, and stand on all 17s.\n");
	choice = startMenu();
	faceCard = 0;
	player = 0;
	dealer = 0;
	while (choice != 0 && money > 0)
	{
		if (bet > money) bet = money;
		printf("You have %d coins.\n", money);
		printf("The current bet is %d.\n", bet);
		if (choice == 1)
		{
			dealer = dealerCards(&faceCard);
			player = playerCards(faceCard);
			dealerBust = dealer > 21;
			playerBust = player > 21;
			printf("Player: %d, Dealer: %d \n", player, dealer);
			if (player > dealer) {
				win = (playerBust ? 0 : 1);
			}
			if (player < dealer) {
				win = (dealerBust && !playerBust ? 1 : 0);
			}
			if (player == dealer)
			{
				win = (playerBust ? 0 : 3);
			}
		}
		if (win == 3) {
			printf("Tie.\n");
		}
		if (win == 1) {
			printf("You won.\n");
			money += bet;
		}
		if (win == 0) {
			printf("You lost.\n");
			money -= bet;
		}
		choice = startMenu();
	}
	return 0;
}

int startMenu()
{
	int choice;
	printf("Do you want to play? 1=yes 0=no\n");
	scanf("%d", &choice);
	return choice;
}

int drawCard()
{
	int card;

	card = rand() % 10;
	card++;
	return card;
}

int dealerCards(int *faceCard)
{
	int cardTot, cardDrawn;
	*faceCard = drawCard();
	cardTot = *faceCard;
	while (cardTot <= 17)
	{
		cardDrawn = drawCard();
		cardTot = cardTot + cardDrawn;
	}
	return cardTot;
}

int playerCards(int faceCard)
{
	int card1, card2, cardDrawn, cardTot, choice;
	card1 = drawCard();
	card2 = drawCard();
	cardTot = card1 + card2;
	if (card1 == 1)
	{
		card1 = 11;
		cardTot = cardTot + 10;
	} else if (card2 == 1)
	{
		card2 = 11;
		cardTot = cardTot + 10;
	}
	if (cardTot > blackjack)
		return cardTot;
	printf("The dealer's face card is %d.\n", faceCard);
	printf("Your first card is %d, your second card is %d, your hand total is %d.\n Do you want to hit (1) or stand(0)?\n", card1, card2, cardTot);
	scanf("%d", &choice);
	while (choice != 0)
	{
		cardDrawn = drawCard();
		cardTot = cardTot + cardDrawn;
		if (cardTot <= blackjack)
		{
			printf("Your hand total is %d, do you want to hit or stand?\n", cardTot);
			scanf("%d", &choice);
		}
		else
		{
			printf("Busted!\n");
			choice = 0;
		}
	}
	return cardTot;
}
