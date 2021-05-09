//
// Created by simerjan on 05.05.21.
//

#ifndef SEMESTRAL_HAND_H
#define SEMESTRAL_HAND_H

#include <stdexcept>
#include <utility>
#include <iostream>
#include <algorithm>
#include "cards.h"

using std::pair;
using std::sort;
using std::cout;
using std::flush;
using std::endl;
using std::make_pair;
using std::runtime_error;

class Hand {
public:
    int rankHand(const vector<AbstractCard *> &boardCards)
    {
        if (!resolveCards(boardCards)) {
            return -1;
        }

        uint8_t totalCount = 0;
        uint8_t clubsCount = 0;
        uint8_t diamondsCount = 0;
        uint8_t hearthsCount = 0;
        uint8_t spadesCount = 0;

        bool straight = false;
        uint8_t straightIndex = 0;
        for (uint8_t i = straightIndex; i < straightIndex + 4; i++) {
            countCardColor(i, totalCount, clubsCount, diamondsCount, hearthsCount, spadesCount);

            // the next card doesn't match current straight
            if ((int) cachedCards[i]->getValue() != (int) cachedCards[i + 1]->getValue() - 1
                || i != straightIndex + 3
                || cachedCards[i]->getValue() != CardValue::N2
                || cachedCards[i + 1]->getValue() != CardValue::A) {
                // reset sequence with next card or break
                if (straightIndex < 2) {
                    ++straightIndex;
                    i = straightIndex;
                    continue;
                } else {
                    break;
                }
            }

            // straight found
            if (i == straightIndex + 3) {
                straight = true;
            }
        }

        if (straight) {
            // straight flush / royal flush possible
            if (clubsCount >= 5 || diamondsCount >= 5 || hearthsCount >= 5 || spadesCount >= 5) {

                // validate
                bool isFlush = true;
                for (uint8_t i = straightIndex; i < straightIndex + 4; i++) {
                    if (cachedCards[i]->getColor() != cachedCards[i + 1]->getColor()) {
                        isFlush = false;
                        break;
                    }
                }

                // straight flush
                if (isFlush) {
                    return 1000000 + (int) cachedCards[straightIndex]->getValue() * 1000;
                }

                // basic straight
                return 900000 + (int) cachedCards[straightIndex]->getValue() * 1000;
            }
        }

        vector<uint8_t> fourOfAKinds;
        vector<uint8_t> threeOfAKinds;
        vector<uint8_t> twoOfAKinds;
        uint8_t startIndex = 0;

        for (int8_t i = 1; i < (int8_t) cachedCards.size(); i++) {
            if (i + 1 < (int8_t) cachedCards.size() && cachedCards[i - 1]->getValue() == cachedCards[i]->getValue()) {
                continue;;
            }

            uint8_t len = i - startIndex;
            if (len == 4) {
                fourOfAKinds.push_back(startIndex);
            } else if (len == 3) {
                if (threeOfAKinds.empty()) {
                    threeOfAKinds.push_back(startIndex);
                } else {
                    twoOfAKinds.push_back(startIndex);
                }
            } else if (len == 2 && twoOfAKinds.size() < 2) {
                twoOfAKinds.push_back(startIndex);
            }
            startIndex = i;
        }

        // four of a kind
        if (!fourOfAKinds.empty()) {
            return 800000
                   + (int) cachedCards[fourOfAKinds.front()]->getValue() * 1000
                   + (int) getHighCard(
                    cachedCards[fourOfAKinds.front()]->getValue(),
                    cachedCards[fourOfAKinds.front()]->getValue()
            );
        }

        // full house
        if (!threeOfAKinds.empty() && !twoOfAKinds.empty()) {
            return 700000
                   + (int) cachedCards[threeOfAKinds.front()]->getValue() * 1000
                   + (int) cachedCards[twoOfAKinds.front()]->getValue();
        }

        // check for flush
        for (uint8_t i = totalCount; i < cachedCards.size(); i++) {
            countCardColor(i, totalCount, clubsCount, diamondsCount, hearthsCount, spadesCount);
        }

        // flush
        if (clubsCount >= 5 || diamondsCount >= 5 || hearthsCount >= 5 || spadesCount >= 5) {

            int val = 400000;

            // resolve color
            CardColor color = CardColor::CLUBS;
            if (diamondsCount >= 5) {
                color = CardColor::DIAMONDS;
            } else if (hearthsCount >= 5) {
                color = CardColor::HEARTHS;
            } else if (spadesCount >= 5) {
                color = CardColor::SPADES;
            }

            int multiplier = 10000;
            bool highCardCounted = false;
            for (uint8_t i = 0; i < cachedCards.size() && (multiplier >= 10 || !highCardCounted); i++) {
                if (multiplier >= 10 && cachedCards[i]->getColor() == color) {
                    val += (int) cachedCards[i]->getValue() * multiplier;
                    multiplier /= 10;
                } else {
                    highCardCounted = true;
                    val += (int) cachedCards[i]->getValue();
                }
            }

            return val;
        }

        // three of a kind
        if (!threeOfAKinds.empty()) {

            CardValue threeOfAKindValue = cachedCards[threeOfAKinds.front()]->getValue();
            int val = 350000 + 1000 * (int) threeOfAKindValue;
            CardValue secondHighest = getHighCard(threeOfAKindValue, threeOfAKindValue);
            val += 100 * (int) secondHighest;
            CardValue thirdHighest = getHighCard(threeOfAKindValue, secondHighest);
            val += 10 * (int) thirdHighest;

            return val;
        }

        // two pairs
        if (twoOfAKinds.size() >= 2) {
            return 300000 + 1000 * (int) cachedCards[twoOfAKinds[0]]->getValue()
                   + 100 * (int) cachedCards[twoOfAKinds[1]]->getValue()
                   + (int) getHighCard(
                    cachedCards[twoOfAKinds[0]]->getValue(),
                    cachedCards[twoOfAKinds[1]]->getValue()
            );
        }

        // pair
        if(! twoOfAKinds.empty()){
            CardValue cardValue = cachedCards[twoOfAKinds.front()]->getValue();
            int val = 150000 + 10000 * (int) cardValue;
            int multiplier = 1000;
            for(uint8_t i = 0; i < cachedCards.size() && multiplier >= 10; i++){
                if(cachedCards[i]->getValue() != cardValue){
                    val += multiplier * (int) cachedCards[i]->getValue();
                    multiplier /= 10;
                }
            }

            return val;
        }

        // high value
        int val = 0;
        int multiplier = 10000;
        for(uint8_t i = 0; i < 5; i++){
            val += multiplier * (int) cachedCards[i]->getValue();
            multiplier /= 10;
        }

        return val;
    }

    void setCards(AbstractCard *card1, AbstractCard *card2)
    {
        cards = make_pair(card1, card2);
    }

    void print() const
    {
        vector<string> cardsStr{cards.first->toString(), cards.second->toString()};
        size_t len = cardsStr.front().size();
        size_t currI = 0;

        for(uint8_t n = 0; n < 2 && currI < len; n = (n + 1) % 2){
            for(size_t i = currI; i < len; i++){

                if(cardsStr[n][i] == '\n'){
                    if(n + 1 < 2){
                        cout << "   ";
                    }else{
                        cout << endl;
                        currI = i + 1;
                    }
                    break;
                }
                cout << cardsStr[n][i];
            }

        }

        cout << endl;
    }

private:

    bool resolveCards(const vector<AbstractCard *> &boardCards)
    {
        cachedCards = boardCards;
        cachedCards.push_back(cards.first);
        cachedCards.push_back(cards.second);

        if (cachedCards.size() >= 7) {
            sort(cachedCards.begin(), cachedCards.end(), [](const AbstractCard *a, const AbstractCard *b) {
                return a->getValue() < b->getValue();
            });
            return true;
        }

        return false;
    }

    void countCardColor(
            uint8_t index,
            uint8_t &totalCount,
            uint8_t &clubsCount,
            uint8_t &diamondsCount,
            uint8_t &hearthsCount,
            uint8_t &spadesCount
    )
    {
        if (totalCount > index) {
            return;
        }
        ++totalCount;

        auto color = cachedCards[index]->getColor();
        switch (color) {
            case CardColor::CLUBS:
                ++clubsCount;
                return;
            case CardColor::DIAMONDS:
                ++diamondsCount;
                return;
            case CardColor::HEARTHS:
                ++hearthsCount;
                return;
            case CardColor::SPADES:
                ++spadesCount;
                return;
        }
    }

    CardValue getHighCard(CardValue excluding1, CardValue excluding2)
    {
        for (const AbstractCard *card : cachedCards) {
            if (card->getValue() != excluding1 && card->getValue() != excluding2) {
                return card->getValue();
            }
        }
        throw runtime_error("Black magic.");
    }

    vector<AbstractCard *> cachedCards;
    pair<AbstractCard *, AbstractCard *> cards;
};


#endif //SEMESTRAL_HAND_H
