//
// Created by simerjan on 05.05.21.
//

#ifndef SEMESTRAL_PLAYER_H
#define SEMESTRAL_PLAYER_H


#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include "hand.h"
#include "agent.h"

using std::string;
using std::move;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

class Player {
public:
    Player(string name, unsigned int money, Agent *agent = nullptr)
            : name(move(name)), startingBalance(money), balance(money), agent(agent)
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

    unsigned int promptForBet(GameStage stage, unsigned int currBet, bool canCheck, bool canRaise, double prob,
                              unsigned int potAmount)
    {
        cout << getName() << "'s turn: " << endl;
        printHand();
        cout << "The bet is " << currBet << ". You have " << getAtStake() << " coins at stake. Your balance is "
             << getBalance() << " coins." << endl;
        cout << "Your probability to win is " << fixed << setprecision(2) << prob * 100 << "%." << endl;

        if (agent != nullptr) {

            unsigned int predictedBet = agent->makeBet(
                    stage,
                    startingBalance,
                    balance,
                    atStake,
                    currBet,
                    potAmount,
                    prob
            );
            cout << "Predicted bet is " << predictedBet << " coins." << endl;

            // fold
            if(predictedBet < currBet){
                cout << "Player folded." << endl;
                atStake = 0;
                return 0;
            }

            // check or raise
            if(balance + atStake >= predictedBet){
                if(predictedBet == currBet){
                    if(atStake < currBet){
                        cout << "Player called." << endl;
                    }else{
                        cout << "Player checked." << endl;
                    }
                }else{
                    cout << "Player raised to " << predictedBet << "." << endl;
                }

                unsigned int diff = currBet - atStake;
                atStake += diff;
                balance -= diff;
                return currBet;
            }
            // all in

            cout << "Player is all in." << endl;
            atStake += balance;
            balance = 0;
            return atStake;
        }

        string response;
        do {
            cout << "You can: " << endl;

            cout << "f) Fold" << endl;
            if (canCheck) {
                cout << "c) Check" << endl;
            }
            if (currBet > getAtStake()) {
                cout << "a) Call" << endl;
            }

            if (canRaise) {
                cout << "r) Raise" << endl;
            }

        } while (!(cin >> response)
                 || (response != "f"
                     && (response != "c" || !canCheck)
                     && (response != "a" || currBet <= getAtStake())
                     && (response != "r" || !canRaise)));
        cin.clear();

        if (response == "f") {
            atStake = 0;
            return 0;
        }

        if (response == "c") {
            return currBet;
        }

        if (response == "a") {
            if (balance + atStake >= currBet) {
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

    double monteCarloSimulation(const vector<AbstractCard *> &tableCards, uint8_t numberOfOpponents)
    {
        unsigned int simulations = (numberOfOpponents + 1) * SIMULATIONS_PER_PLAYER;
        unsigned int wins = 0;
        vector<AbstractCard *> dummyDeck = CardFactory::makeDeck();

        // remove already used
        for (int i = 0; i < (int) dummyDeck.size(); i++) {
            bool equal = false;
            for (AbstractCard *tableCard : tableCards) {
                if (dummyDeck[i]->equal(tableCard)) {
                    equal = true;
                    break;
                }
            }

            if (equal || dummyDeck[i]->equal(hand.getCards().first) || dummyDeck[i]->equal(hand.getCards().second)) {
                dummyDeck.erase(dummyDeck.begin() + i);
                i--;
            }
        }

        for (size_t i = 0; i < simulations; i++) {
            CardFactory::shuffleDeck(dummyDeck);
            size_t deckIndex = 0;

            // complete table cards
            vector<AbstractCard *> tableCardsCopy(tableCards);
            while (tableCardsCopy.size() < 5) {
                tableCardsCopy.push_back(dummyDeck[deckIndex++]);
            }

            int myRanking = hand.rankHand(tableCardsCopy);
            bool lost = false;

            // make opponent hands
            vector<Hand> opponents;
            opponents.resize(numberOfOpponents);
            for (Hand &opponent : opponents) {
                AbstractCard *card1 = dummyDeck[deckIndex++];
                AbstractCard *card2 = dummyDeck[deckIndex++];
                opponent.setCards(card1, card2);
                if (opponent.rankHand(tableCardsCopy) > myRanking) {
                    lost = true;
                    break;
                }
            }

            if (!lost) {
                wins++;
            }
        }

        return wins / (double) simulations;
    }


private:
    static unsigned int promptRange(unsigned int from, unsigned int to)
    {
        unsigned int response;
        do {
            cout << "Please enter an integer between " << from << " and " << to << ":" << endl;

            cin.clear();
        } while (!(cin >> response) || response < from || response > to);

        return response;
    }

    string name;
    Hand hand;
    unsigned int startingBalance = 0;
    unsigned int balance = 0;
    Agent *agent = nullptr;
    unsigned int atStake = 0;

    static const unsigned int SIMULATIONS_PER_PLAYER;
};

const unsigned int Player::SIMULATIONS_PER_PLAYER = 2000;

#endif //SEMESTRAL_PLAYER_H
