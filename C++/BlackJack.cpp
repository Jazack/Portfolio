#include <iostream>
#include <functional>
#include <ostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <vector>

class Cards{
    /*
    this will need value, suit, color, name
    */
    int val;
    char suit;
    char color;
    char name[3];
    public: Cards(int val, char suit, char color, char name[]){
        this->val = val;
        this->suit = suit;
        this->color = color;
        this->name[0] = name[0];
        this->name[1] = name[1];
        return;
    }
    public: char* getName(){
        return this-> name;
    }
    public: int getVal(){
        return this->val;
    }
    public: char getSuit(){
        return this->suit;
    }
    public: char getColor(){
        return this->color;
    }
};
class BlackJack{
    std::vector<Cards> deck;
    std::vector<int> discard;
    std::vector<int> held;
    std::vector<std::vector<int>> hands;
    int reset;
    public: BlackJack(char choice){
        int quant = 1;
        if (choice == 'Y'){
            /*
            need to generate six decks
            */
            quant = 6;
        }
        // this is the deck that I'll be using, it will keep all of my cards
        // there is one extra card location because there is a black card to signify when
        // to reshuffle the deck
        // name of each card
        char ten[2] = {'1', '0'};
        char nine[2] = {'9'};
        char eight[2] = {'8'};
        char seven[2] = {'7'};
        char six[2] = {'6'};
        char five[2] = {'5'};
        char four[2] = {'4'};
        char three[2] = {'3'};
        char two[2] = {'2'};
        char ace[2] = {'A'};
        char jack[2] = {'J'};
        char queen[2] = {'Q'};
        char king[2] = {'K'};
        char* names[13] = {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
        // the suits
        char clubs = 'C';
        char hearts = 'H';
        char spades = 'S';
        char diamonds = 'D';
        char suits[4] = {clubs, hearts, spades, diamonds};
        // the colors
        char red = 'R';
        char black = 'B';
        char colors[2] = {red, black};
        this->reset = std::round((quant * 52) * (2/3));
        while(quant > 0){
            int color = 1;
            for (int i = 0; i < 4; i++){// the suit
                for(int j = 0; j < 13; j++){ // the value and name
                    this->deck.push_back(Cards(j, suits[i], colors[color], names[j]));
                }
                // adjust the color
                if (color > 0) color--;
                else color++;
            }
            quant--;
        }
    }
    public: void runGame(int players = 3){
        int risk = 14;
        bool keepPlaying = true;
        while (keepPlaying){
            gameStart(players);
            system("clear");
            displayCards(players);
            // drawing cards:
            bool keepDrawing = true;
            bool playerDrawing = true;
            while (keepDrawing){
                char response = '0';
                if (!playerDrawing){
                    response = 'N';
                }
                while (response != 'Y' && response != 'N' && playerDrawing){
                    std::cout << "DO YOU WISH TO DRAW ANOTHER CARD? Y/N:" << std::endl;
                    std::cin >> response;
                    response = std::toupper(response);
                }
                if (response == 'Y'){
                    this->hands[1].push_back(drawCard());
                }
                else if (response == 'N'){
                    keepDrawing = false;
                    playerDrawing = false;
                }
                // each other player gets to draw a card or not
                for(int i = 0; i <= players; i++){
                    if (i <= 1){}
                    else{
                        // determine value of the cards that the player has
                        int val = 0;
                        int aces = 0;
                        for (int j : this->hands[i]){
                            int temp = this->deck[j].getVal();
                            // dealing with aces
                            if (temp == 1){
                                if (val + 11 <= 21){
                                    temp == 11;
                                    aces++;
                                }
                            }
                            val += temp;
                            if (val > 21 && aces){
                                val -= 10;
                                aces--;
                            }
                        }
                        if (val < risk){
                            sleep(1);
                            std::cout << "PLAYER " << i << " IS DRAWING A CARD\n";
                            int temp = drawCard();
                            this->hands[i].push_back(temp);
                            keepDrawing = true;
                        }
                    }
                } // end of ai players
                if (keepDrawing){
                    sleep(2);
                    system("clear");
                    displayCards(players);
                    sleep(1);
                }
                else{
                    sleep(2);
                    system("clear");
                }
            } // end of drawing
            // determine winner
            int dealer = 0;
            int winning = 0;
            for (int i = 0; i <= players; i++){
                // tally up points
                int aces = 0;
                int val = 0;
                for (int j : this->hands[i]){
                    int temp = this->deck[j].getVal();
                    // dealing with aces
                    if (temp == 1){
                        if (val + 11 <= 21){
                        temp == 11;
                            aces++;
                        }
                    }
                    val += temp;
                    if (val > 21 && aces){
                        val -= 10;
                    aces--;
                    }
                }
                if (i == 0){
                    dealer = val;
                    std::cout << "DEALER HAS " << val << " POINTS" << std::endl;
                }
                else if (i == 1) {
                    if (val > dealer && val <= 21){
                        winning = 1;
                        dealer = val;
                    }
                    std::cout << "YOU HAVE " << val << " POINTS\n";
                }
                else{
                    if (val > dealer && val <= 21){
                        winning = i;
                        dealer = val;
                    }
                    std::cout << "PLAYER " << i <<" HAS " << val << " POINTS\n";
                }
            }
            switch(winning){
                case 0:
                    std::cout << "THE DEALER WON" << std::endl;
                    break;
                case 1:
                    std::cout << "YOU WON" << std::endl;
                    break;
                default:
                    std::cout << "PLAYER " << winning << " WON" << std::endl;
            }
            // see if the player wants to play again
            char response = '0';
            while (response != 'Y' && response != 'N'){
                std::cout << "DO YOU WISH TO PLAY AGAIN? Y/N:" << std::endl;
                std::cin >> response;
                response = std::toupper(response);
            }
            if (response == 'N'){
                keepPlaying = false;
            }
            else{
                for (int i: this->held){
                    this->discard.push_back(i);
                }
                this->held.clear();
            }
        }
    }
    /*
    function gameStart
    
    params:
    int players ----- the quantity of players in the game, defaults to single player
    */
    private: void gameStart(int players = 1){
        this->hands.clear();
        for (int i = 0; i < players; i++){
            std::vector<int> temp;
            this->hands.push_back(temp);
        }
        std::vector<int> temp;
        this->hands.push_back(temp);; // this is because the dealer also has a hand
        int plays = this->hands.size();
        int drawed;
        // dealing
        for (int i = 0; i < plays * 2; i++){ // everyone starts with two cards
            drawed = drawCard();
            // a random card has been selected, give it to a player
            int player = i % plays; // this selects the player
            this->hands[player].push_back(drawed);
        } // end of dealing
    }
    private: void displayCards(int players = 1){
        // display Cards
        for (int i = 0; i < (players + 1); i++){
            switch(i){
                case 0:
                    std::cout << "DEALER: ";
                    break;
                case 1:
                    std::cout << "YOU: ";
                    break;
                default:
                    std::cout << "PLAYER " << i << ": ";
                    break;
            }
            for (int j = 0; j < this->hands[i].size(); j++){
                if (i == 1 || j < 2){
                    // displays the Cards
                    std::cout << this->deck[this->hands[i][j]].getName() << ", ";
                }
                else{
                    std::cout << "X, ";
                }
            }
            std::cout << std::endl;
        }
        
    }
    public: void printAll(){
        for (Cards c : this->deck){
            std::cout << c.getName() << std::endl;
        }
    }
    /*
    function drawCard
    returns an int
    parameters:
    none
    
    it will choose a number that has not been chosen yet
    */
    public: int drawCard(){
        // pick a random card that has not been chosen yet
        bool looking = true;
        int rounds = 0;
        int check;
        std::srand(time(0));
        while (looking){
            if (rounds > 3){ // if it has tried to find a random, unused, card four times, add in the discard pile
                this->discard.clear();
            }
            check = std::rand() % this->deck.size(); // get a size of it
            if (std::count(this->held.begin(), this->held.end(), check) || std::count(this->discard.begin(), this->discard.end(), check)){
                rounds++;
            }
            else{
                looking = false;
                rounds = 0;
            }
        }
        this->held.push_back(check);
        return check;
    }
    
};


int main()
{
    char response = '0';
    while (response != 'Y' && response != 'N'){
        std::cout << "DO YOU WISH TO PLAY WITH SIX DECKS? (Y/N):" << std::endl;
        std::cin >> response;
        response = std::toupper(response);
    }
    BlackJack game = BlackJack(response);
    int players = 0;
    while (players < 1 || players > 7){
        std::cout << "CHOOSE QUANTITY OF PLAYERS (1-7):" << std::endl;
        std::cin >> players;
    }
    game.runGame(players);
    return 0;
}
