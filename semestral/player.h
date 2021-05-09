//
// Created by simerjan on 05.05.21.
//

#ifndef SEMESTRAL_PLAYER_H
#define SEMESTRAL_PLAYER_H


#include <string>
#include <utility>
#include <iostream>
#include "hand.h"

using std::string;
using std::move;
using std::cin;
using std::cout;
using std::endl;

class Player {
public:
    Player(string name, unsigned int money): name(move(name)), balance(money)
    {
    }

    const string &getName() const
    {
        return name;
    }

    unsigned int getBalance() const
    {
        return balance;
    }

    unsigned int getAtStake() const
    {
        return atStake;
    }

    void setAtStake(unsigned int value)
    {
        atStake = value;
    }

    unsigned int promptForBet(unsigned int currBet, bool canCheck, bool canRaise)
    {
        cout << getName() << "'s turn: " << endl;
        printHand();
        cout << "The bet is " << currBet << ". You have " << getAtStake() << " coins at stake. Your balance is " << getBalance() << " coins." << endl;


        string response;
        do{
            cout << "You can: " << endl;

            cout << "f) Fold" << endl;
            if(canCheck){
               cout << "c) Check" << endl;
            }
            if(currBet > getAtStake()){
                cout << "a) Call" << endl;
            }

            if(canRaise){
                cout << "r) Raise" << endl;
            }

        }while(!(cin >> response)
        || (response != "f"
        && (response != "c"|| !canCheck)
        && (response != "a" || currBet <= getAtStake())
        && (response != "r" || !canRaise)));
        cin.clear();

        if(response == "f"){
            atStake = 0;
            return 0;
        }

        if(response == "c"){
            return currBet;
        }

        if(response == "a"){
            if(balance + atStake >= currBet){
                unsigned int diff = currBet - atStake;
                atStake += diff;
                balance -= diff;
                return currBet;
            }

            // all in
            atStake += balance;
            balance = 0;
            return atStake;
        }

        // raise
        unsigned int raisedTo = promptRange(currBet + 1, currBet + getBalance());
        balance -= raisedTo - getAtStake();
        atStake = raisedTo;
        return raisedTo;
    }

    void setCards(AbstractCard *card1, AbstractCard *card2)
    {
        hand.setCards(card1, card2);
    }

    void printHand()
    {
        hand.print();
    }

    int rankHand(const vector<AbstractCard *> &boardCards)
    {
        return hand.rankHand(boardCards);
    }

    void addBalance(unsigned int amount)
    {
        balance += amount;
    }

    void bet(unsigned int amount)
    {
        balance -= amount;
        atStake += amount;
    }


private:
    static unsigned int promptRange(unsigned int from, unsigned int to)
    {
        unsigned int response;
        do{
            cout << "Please enter an integer between " << from << " and " << to << ":" << endl;

            cin.clear();
        }while(!(cin >> response) || response < from || response > to);

        return response;
    }

    string name;
    Hand hand;
    unsigned int balance = 0;
    unsigned int atStake = 0;
};


#endif //SEMESTRAL_PLAYER_H
