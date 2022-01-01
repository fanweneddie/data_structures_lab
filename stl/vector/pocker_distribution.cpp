#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

vector<int> undistributedCard;

//showing the color of the card. 
// 1~13 fangpian
//14~26 meihua
//27~39 hongtao
//40~52 heitao
string get_color(int card)
{
    switch( (card-1)/13 )
    {
        case 0:
            return "fangpian";
        case 1:
            return "meihua";
        case 2:
            return "hongtao";
        case 3:
            return "heitao";
        default:
            return "none";
    }
}

//showing the value of the card
//just need to pay attention to J,Q,K,A
string get_value(int card)
{
    switch( card % 13 )
    {
        case 1:
            return "A";
        case 11:
            return "J";
        case 12:
            return "Q";
        case 0:
            return "K";
        default:
            return to_string(card % 13);
    }
}

int string_to_num_of_a_card(string cardValue,string cardColor)
{
    int cardVal = 0;//use number to describe all cards
    
    //firstly, transmitting the value
    if( cardValue == "A" )
        cardVal += 1;
    if(cardValue== "J")
        cardVal += 11;
    if( cardValue == "Q" )
        cardVal += 12;
    if( cardValue == "K" )
        cardVal += 13;
    else
    {
        cardVal += stoi(cardValue,0,10);
    }
    
    //secondly, transmitting the color
    if(cardColor == "meihua" )
        cardVal += 13;
    if(cardColor == "hongtao")
        cardVal += 26;
    if( cardColor == "heitao")
        cardVal += 39;

    return cardVal;
}

void show_card(vector<int> player)
{
    int cardNum = player.size();
    string cardContent;
    string color;
    cout << "the player" << "'s cards are " << endl;
    for (int i = 0; i < cardNum;i++)
    {
        cout << get_color(player[i]) << "  " << get_value(player[i]) << endl;
    }
}

void card_distribution(vector <int> player)
{
    int remainCardNum = undistributedCard.size();
    srand((unsigned)time(NULL));
    int orderOfCardOut = rand() % remainCardNum ;
    int valOfCardOut = undistributedCard[orderOfCardOut];
    undistributedCard.erase(undistributedCard.begin() + orderOfCardOut);
    player.push_back(valOfCardOut);
}


int main()
{
    for (int i = 1; i <= 52;i++)
        undistributedCard.push_back(i);
    vector<int> playerA, playerB, playerC, playerD;
    vector<vector<int>> players = {playerA, playerB, playerC, playerD};
    int round = 1;
    int whoseTurn = 0;
    while(round <= 13)
    {
        for (int j = 0; j <= 3;j++)
        {
            card_distribution(players[whoseTurn % 4]);
            whoseTurn++;
        }
    }

    for (int j = 0; j <= 3;j++)
        {
            show_card(players[whoseTurn % 4]);
            whoseTurn++;
        }
    return 0;
}