//
// Created by simerjan on 05.05.21.
//

#ifndef SEMESTRAL_TABLE_H
#define SEMESTRAL_TABLE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <map>
#include "player.h"
#include "cards.h"

using std::runtime_error;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;
using std::map;
using std::make_pair;
using std::string_literals::operator ""s;
using std::to_string;

enum class GameStage {
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER,
};

class Table {
public:

    Table() : deck(CardFactory::makeShuffledDeck())
    {
    }

    ~Table()
    {
        for (const auto player : players) {
            delete player;
        }
    }

    void addPlayer(const Player &player)
    {
        players.push_back(new Player(player));
    }

    void startGame()
    {
        for (int i = 0; i < (int) players.size(); i++) {
            if (players[i]->getBalance() < BIG_BLIND) {
                cout << "Kicking player " << players[i]->getName() << " as he doesn't have sufficient balance." << endl;
                i--;
            }
        }


        do {
            if (players.size() < 2 || players.size() > 10) {
                throw runtime_error("Invalid player count: "s + to_string(players.size()) + ".");
            }
            smallBlind = smallBlind % players.size();
            cout << "Player " << players[smallBlind]->getName() << " is small blind." << endl;
            cout << "Player " << players[(smallBlind + 1) % players.size()]->getName() << " is big blind." << endl;

            startRound();
            evaluateRound();
            smallBlind++;
        } while (shouldContinue());

    }

    void startRound()
    {
        tableCards = vector<AbstractCard *>{};
        foldedCount = 0;
        potAmount = SMALL_BLIND + BIG_BLIND;
        playerOnTurn = smallBlind;
        players[playerOnTurn]->bet(SMALL_BLIND);
        advancePlayer();    // move to big blind player
        playerRaised = playerOnTurn;
        betAmount = BIG_BLIND;
        players[playerOnTurn]->bet(BIG_BLIND);
        bets = map<Player *, unsigned int>{
                make_pair(players[playerOnTurn], BIG_BLIND),
                make_pair(players[smallBlind], SMALL_BLIND)
        };

        gameStage = GameStage::PRE_FLOP;
        deck = CardFactory::makeShuffledDeck();
        for (Player *player : players) {
            player->setCards(deck.back(), deck.at(deck.size() - 2));
            deck.pop_back();
            deck.pop_back();
        }
        requestBets();

        gameStage = GameStage::FLOP;
        for (uint8_t i = 0; i < 3; i++) {
            tableCards.push_back(deck.back());
            deck.pop_back();
        }
        requestBets();

        gameStage = GameStage::TURN;
        tableCards.push_back(deck.back());
        deck.pop_back();
        requestBets();

        gameStage = GameStage::RIVER;
        tableCards.push_back(deck.back());
        deck.pop_back();
        requestBets();
    }

    void requestBets()
    {
        if (foldedCount >= players.size() - 1) {
            return;
        }

        playerOnTurn = smallBlind;
        advancePlayer(2);
        bool noOneRaised = true;
        do {
            // skip folded/all in players
            if ((players[playerOnTurn]->getAtStake() == 0 || players[playerOnTurn]->getBalance()) == 0
                && gameStage != GameStage::PRE_FLOP) {
                continue;
            }

            printTable();
            auto prevBetAmount = betAmount;
            if (promptPlayer(betAmount, noOneRaised)) {
                auto iterator = bets.insert(make_pair(players[playerOnTurn], 0)).first;
                potAmount += players[playerOnTurn]->getAtStake() - iterator->second;
                iterator->second = players[playerOnTurn]->getAtStake();
            } else {
                // folded
                foldedCount++;
                if (foldedCount >= players.size() - 1) {
                    break;
                }
            }

            if (prevBetAmount < betAmount) {
                noOneRaised = false;
            }

            advancePlayer();

            if (playerOnTurn == playerRaised && noOneRaised && gameStage == GameStage::PRE_FLOP) {
                playerRaised = (playerRaised + 1) % players.size();
                noOneRaised = false;
            }

        } while (playerOnTurn != playerRaised);

    }


    bool shouldContinue()
    {
        assertBalances();
        if (players.size() < 2) {
            if (!players.empty()) {
                cout << "Player " << players.front()->getName() << " won." << endl;
            }
            cout << "Ending game." << endl;
            return false;
        }

        string response;
        do {
            cin.clear();
            cout << "Would you like to continue with another round? (y/n)" << endl;
        } while (!(cin >> response) || (response != "y" && response != "n"));

        return response == "y";
    }

    void assertBalances()
    {
        for (int i = 0; i < (int) players.size(); i++) {
            if (players[i]->getBalance() < BIG_BLIND) {
                cout << "Kicking player " << players[i]->getName()
                     << " as he doesn't sufficient balance." << endl;
                players.erase(players.begin() + i);
                i--;
            }
        }
    }

    void advancePlayer(uint8_t positions = 1)
    {
        playerOnTurn = (playerOnTurn + positions) % players.size();
    }

    bool promptPlayer(unsigned int &bet, bool noOneRaised)
    {
        bool canCheck = players[playerOnTurn]->getAtStake() >= bet;
        bool canRaise = players[playerOnTurn]->getBalance() > 0
                        && players[playerOnTurn]->getAtStake() + players[playerOnTurn]->getBalance() > bet
                        && (playerRaised != playerOnTurn || noOneRaised);

        unsigned int response = players[playerOnTurn]->promptForBet(
                bet,
                canCheck,
                canRaise,
                players[playerOnTurn]->monteCarloSimulation(
                        tableCards,
                        players.size() - 1 - foldedCount
                )
        );
        if (response > bet) {
            playerRaised = playerOnTurn;
            bet = response;
            return true;
        }

        return response != 0;
    }

    void printTable() const
    {
        if (tableCards.empty()) {
            return;
        }
        vector<string> cards;
        cards.reserve(tableCards.size());
        for (const AbstractCard *card : tableCards) {
            cards.push_back(card->toString());
        }
        cout << "-----------------------------------------------" << endl;

        size_t len = cards.empty() ? 0 : cards.front().length();
        size_t currI = 0;

        for (uint8_t n = 0; n < cards.size() && currI < len; n = (n + 1) % cards.size()) {
            for (size_t i = currI; i < len; i++) {

                if (cards[n][i] == '\n') {
                    if (n + 1 < (int) cards.size()) {
                        cout << "   ";
                    } else {
                        cout << endl;
                        currI = i + 1;
                    }
                    break;
                }
                cout << cards[n][i];
            }
        }
        cout << endl;

        cout << "-----------------------------------------------" << endl;
    }

    void evaluateRound()
    {
        vector<pair<Player *, unsigned int>> ranking;
        for (Player *player : players) {
            // folded
            if (player->getAtStake() == 0) {
                continue;
            }
            ranking.emplace_back(player, player->rankHand(tableCards));
        }

        sort(ranking.begin(), ranking.end(),
             [](const pair<Player *, unsigned int> &a, const pair<Player *, unsigned int> &b) {
                 return b.second < a.second;
             });

        uint8_t nextWinner = 0;
        while (potAmount > 0) {
            vector<Player *> winners;
            unsigned int rank = ranking[nextWinner].second;
            while (nextWinner < ranking.size() && ranking[nextWinner].second == rank) {
                winners.push_back(ranking[nextWinner++].first);
            }

            unsigned int won = 0;
            for (Player *player : winners) {
                unsigned int playerBetAmount = bets.find(player)->second;

                for (auto &betPair : bets) {
                    unsigned int applicableAmount =
                            playerBetAmount >= betPair.second ? betPair.second : playerBetAmount;
                    betPair.second -= applicableAmount;
                    won += applicableAmount;
                    potAmount -= applicableAmount;
                }
            }

            for (Player *player : winners) {
                unsigned int playerWon = won / winners.size();
                cout << "Player " << player->getName() << " won " << playerWon - player->getAtStake() << " coins."
                     << endl;
                player->addBalance(playerWon);
            }

        }

        for (Player *player : players) {
            player->setAtStake(0);
        }
    }


private:
    static const unsigned int SMALL_BLIND;
    static const unsigned int BIG_BLIND;

    vector<Player *> players;
    uint8_t playerOnTurn = 0;
    uint8_t smallBlind = 0;
    uint8_t playerRaised = 0;
    GameStage gameStage = GameStage::PRE_FLOP;
    vector<AbstractCard *> deck;
    vector<AbstractCard *> tableCards;
    map<Player *, unsigned int> bets;
    unsigned int potAmount = 0;
    unsigned int betAmount = 0;
    uint8_t foldedCount = 0;
};

const unsigned int Table::SMALL_BLIND = 5;
const unsigned int Table::BIG_BLIND = 10;


#endif //SEMESTRAL_TABLE_H
