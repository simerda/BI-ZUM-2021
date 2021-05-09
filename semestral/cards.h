//
// Created by simerjan on 03.05.21.
//

#ifndef SEMESTRAL_CARDS_H
#define SEMESTRAL_CARDS_H

#include <random>
#include<string>
#include<vector>
#include<stdexcept>
#include <chrono>

using std::string;
using std::vector;
using std::invalid_argument;
using std::string_literals::operator ""s;
using std::default_random_engine;


enum class CardColor {
    CLUBS,
    DIAMONDS,
    HEARTHS,
    SPADES,
};

enum class CardValue {
    N2 = 2,
    N3 = 3,
    N4 = 4,
    N5 = 5,
    N6 = 6,
    N7 = 7,
    N8 = 8,
    N9 = 9,
    N10 = 10,
    J = 11,
    Q = 12,
    K = 13,
    A = 14,
};

class AbstractCard {
public:

    virtual ~AbstractCard() = default;

    virtual CardColor getColor() const
    {
        return color;
    }

    virtual CardValue getValue() const
    {
        return value;
    }

    virtual string toString() const
    {
        string valueStr = AbstractCard::valueToString(value);
        string colorStr = AbstractCard::colorToString(color);

        string str;
        str += "+---------+\n";
        str += "|" + valueStr + (valueStr.length() == 1 ? " " : "") + "       |\n";
        str += "|         |\n";
        str += "|         |\n";
        str += "|    " + colorStr + "    |\n";
        str += "|         |\n";
        str += "|         |\n";
        str += "|       "s + (valueStr.length() == 1 ? " " : "") + valueStr + "|\n";
        str += "+---------+\n";
        return str;
    }

protected:
    CardColor color = CardColor::CLUBS;
    CardValue value = CardValue::N2;

private:
    static string colorToString(CardColor color)
    {
        switch (color) {
            case CardColor::CLUBS:
                return "♣";
            case CardColor::DIAMONDS:
                return "♦";
            case CardColor::HEARTHS:
                return "♥";
            case CardColor::SPADES:
                return "♠";
        }
        throw invalid_argument("Unknown color.");
    }

    static string valueToString(CardValue value)
    {
        switch (value) {
            case CardValue::N2:
                return "2";
            case CardValue::N3:
                return "3";
            case CardValue::N4:
                return "4";
            case CardValue::N5:
                return "5";
            case CardValue::N6:
                return "6";
            case CardValue::N7:
                return "7";
            case CardValue::N8:
                return "8";
            case CardValue::N9:
                return "9";
            case CardValue::N10:
                return "10";
            case CardValue::J:
                return "J";
            case CardValue::Q:
                return "Q";
            case CardValue::K:
                return "K";
            case CardValue::A:
                return "A";
        }
        throw invalid_argument("Unknown value.");
    }
};

class TwoOfClubs : public AbstractCard {
public:
    TwoOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N2;
    }
};

class ThreeOfClubs : public AbstractCard {
public:
    ThreeOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N3;
    }
};

class FourOfClubs : public AbstractCard {
public:
    FourOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N4;
    }
};

class FiveOfClubs : public AbstractCard {
public:
    FiveOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N5;
    }
};

class SixOfClubs : public AbstractCard {
public:
    SixOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N6;
    }
};

class SevenOfClubs : public AbstractCard {
public:
    SevenOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N7;
    }
};

class EightOfClubs : public AbstractCard {
public:
    EightOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N8;
    }
};

class NineOfClubs : public AbstractCard {
public:
    NineOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N9;
    }
};

class TenOfClubs : public AbstractCard {
public:
    TenOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::N10;
    }
};

class JackOfClubs : public AbstractCard {
public:
    JackOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::J;
    }
};

class QueenOfClubs : public AbstractCard {
public:
    QueenOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::Q;
    }
};

class KingOfClubs : public AbstractCard {
public:
    KingOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::K;
    }
};

class AceOfClubs : public AbstractCard {
public:
    AceOfClubs()
    {
        color = CardColor::CLUBS;
        value = CardValue::A;
    }
};

class TwoOfDiamonds : public AbstractCard {
public:
    TwoOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N2;
    }
};

class ThreeOfDiamonds : public AbstractCard {
public:
    ThreeOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N3;
    }
};

class FourOfDiamonds : public AbstractCard {
public:
    FourOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N4;
    }
};

class FiveOfDiamonds : public AbstractCard {
public:
    FiveOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N5;
    }
};

class SixOfDiamonds : public AbstractCard {
public:
    SixOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N6;
    }
};

class SevenOfDiamonds : public AbstractCard {
public:
    SevenOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N7;
    }
};

class EightOfDiamonds : public AbstractCard {
public:
    EightOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N8;
    }
};

class NineOfDiamonds : public AbstractCard {
public:
    NineOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N9;
    }
};

class TenOfDiamonds : public AbstractCard {
public:
    TenOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::N10;
    }
};

class JackOfDiamonds : public AbstractCard {
public:
    JackOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::J;
    }
};

class QueenOfDiamonds : public AbstractCard {
public:
    QueenOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::Q;
    }
};

class KingOfDiamonds : public AbstractCard {
public:
    KingOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::K;
    }
};

class AceOfDiamonds : public AbstractCard {
public:
    AceOfDiamonds()
    {
        color = CardColor::DIAMONDS;
        value = CardValue::A;
    }
};

class TwoOfHearths : public AbstractCard {
public:
    TwoOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N2;
    }
};

class ThreeOfHearths : public AbstractCard {
public:
    ThreeOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N3;
    }
};

class FourOfHearths : public AbstractCard {
public:
    FourOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N4;
    }
};

class FiveOfHearths : public AbstractCard {
public:
    FiveOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N5;
    }
};

class SixOfHearths : public AbstractCard {
public:
    SixOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N6;
    }
};

class SevenOfHearths : public AbstractCard {
public:
    SevenOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N7;
    }
};

class EightOfHearths : public AbstractCard {
public:
    EightOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N8;
    }
};

class NineOfHearths : public AbstractCard {
public:
    NineOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N9;
    }
};

class TenOfHearths : public AbstractCard {
public:
    TenOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::N10;
    }
};

class JackOfHearths : public AbstractCard {
public:
    JackOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::J;
    }
};

class QueenOfHearths : public AbstractCard {
public:
    QueenOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::Q;
    }
};

class KingOfHearths : public AbstractCard {
public:
    KingOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::K;
    }
};

class AceOfHearths : public AbstractCard {
public:
    AceOfHearths()
    {
        color = CardColor::HEARTHS;
        value = CardValue::A;
    }
};

class TwoOfSpades : public AbstractCard {
public:
    TwoOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N2;
    }
};

class ThreeOfSpades : public AbstractCard {
public:
    ThreeOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N3;
    }
};

class FourOfSpades : public AbstractCard {
public:
    FourOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N4;
    }
};

class FiveOfSpades : public AbstractCard {
public:
    FiveOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N5;
    }
};

class SixOfSpades : public AbstractCard {
public:
    SixOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N6;
    }
};

class SevenOfSpades : public AbstractCard {
public:
    SevenOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N7;
    }
};

class EightOfSpades : public AbstractCard {
public:
    EightOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N8;
    }
};

class NineOfSpades : public AbstractCard {
public:
    NineOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N9;
    }
};

class TenOfSpades : public AbstractCard {
public:
    TenOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::N10;
    }
};

class JackOfSpades : public AbstractCard {
public:
    JackOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::J;
    }
};

class QueenOfSpades : public AbstractCard {
public:
    QueenOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::Q;
    }
};

class KingOfSpades : public AbstractCard {
public:
    KingOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::K;
    }
};

class AceOfSpades : public AbstractCard {
public:
    AceOfSpades()
    {
        color = CardColor::SPADES;
        value = CardValue::A;
    }
};

class CardFactory {
public:
    static vector<AbstractCard *> makeDeck()
    {
        return vector<AbstractCard *>{
                new TwoOfClubs(),
                new ThreeOfClubs(),
                new FourOfClubs(),
                new FiveOfClubs(),
                new SixOfClubs(),
                new SevenOfClubs(),
                new EightOfClubs(),
                new NineOfClubs(),
                new TenOfClubs(),
                new JackOfClubs(),
                new QueenOfClubs(),
                new KingOfClubs(),
                new AceOfClubs(),
                new TwoOfDiamonds(),
                new ThreeOfDiamonds(),
                new FourOfDiamonds(),
                new FiveOfDiamonds(),
                new SixOfDiamonds(),
                new SevenOfDiamonds(),
                new EightOfDiamonds(),
                new NineOfDiamonds(),
                new TenOfDiamonds(),
                new JackOfDiamonds(),
                new QueenOfDiamonds(),
                new KingOfDiamonds(),
                new AceOfDiamonds(),
                new TwoOfHearths(),
                new ThreeOfHearths(),
                new FourOfHearths(),
                new FiveOfHearths(),
                new SixOfHearths(),
                new SevenOfHearths(),
                new EightOfHearths(),
                new NineOfHearths(),
                new TenOfHearths(),
                new JackOfHearths(),
                new QueenOfHearths(),
                new KingOfHearths(),
                new AceOfHearths(),
                new TwoOfSpades(),
                new ThreeOfSpades(),
                new FourOfSpades(),
                new FiveOfSpades(),
                new SixOfSpades(),
                new SevenOfSpades(),
                new EightOfSpades(),
                new NineOfSpades(),
                new TenOfSpades(),
                new JackOfSpades(),
                new QueenOfSpades(),
                new KingOfSpades(),
                new AceOfSpades(),
        };
    }

    static vector<AbstractCard *> makeShuffledDeck()
    {
        auto deck = makeDeck();
        shuffle(
                deck.begin(),
                deck.end(),
                std::default_random_engine(
                        std::chrono::system_clock::now().time_since_epoch().count()
                )
        );
        return deck;
    }
};


#endif //SEMESTRAL_CARDS_H
