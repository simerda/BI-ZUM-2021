//
// Created by simerjan on 10.05.21.
//

#ifndef SEMESTRAL_AGENT_H
#define SEMESTRAL_AGENT_H

#include <stdexcept>
#include <map>
#include <utility>
#include <random>
#include <chrono>
#include <fstream>
#include "table.h"

using std::map;
using std::move;
using std::ios;
using std::ofstream;
using std::ifstream;
using std::runtime_error;

struct Params{
    double probWeight;
    double balanceWeight;
    double threshold;
};

enum class GameStage {
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER,
};
class Agent {
public:
    static Agent makeRandom()
    {
        map<GameStage, Params> params;
        vector<GameStage> stages{GameStage::PRE_FLOP, GameStage::FLOP, GameStage::TURN, GameStage::RIVER};

        for(GameStage stage : stages){
            params.insert(make_pair(stage, Params{randomNumber(), randomNumber(), randomNumber()}));
        }

        return Agent(params);
    }

    static Agent loadFromFile(const string &filename)
    {
        ifstream file;
        file.open(filename, ios::binary | ios::in);

        size_t generation;
        file.read(reinterpret_cast<char *>(&generation), sizeof(generation));

        map<GameStage, Params> allParams;
        vector<GameStage> stages{GameStage::PRE_FLOP, GameStage::FLOP, GameStage::TURN, GameStage::RIVER};
        for(GameStage stage : stages)
        {
            Params params{};
            file.read(reinterpret_cast<char *>(&params.probWeight), sizeof(params.probWeight));
            file.read(reinterpret_cast<char *>(&params.balanceWeight), sizeof(params.balanceWeight));
            file.read(reinterpret_cast<char *>(&params.threshold), sizeof(params.threshold));
            allParams.insert(make_pair(stage, params));
        }

        if(! file.good()){
            throw runtime_error("Failed to load agent from file.");
        }

        return Agent(allParams, generation);
    }

    void saveToFile(const string &filename) const
    {
        ofstream file;
        file.open(filename, ios::binary | ios::out);
        file.write(reinterpret_cast<const char *>(&generation), sizeof(generation));

        vector<GameStage> stages{GameStage::PRE_FLOP, GameStage::FLOP, GameStage::TURN, GameStage::RIVER};
        for(GameStage stage : stages)
        {
            auto found = stageToParams.find(stage);
            file.write(reinterpret_cast<const char *>(&found->second.probWeight), sizeof(found->second.probWeight));
            file.write(reinterpret_cast<const char *>(&found->second.balanceWeight), sizeof(found->second.balanceWeight));
            file.write(reinterpret_cast<const char *>(&found->second.threshold), sizeof(found->second.threshold));
        }

        if(! file.good()){
            throw runtime_error("Failed to save agent to file.");
        }
    }

    unsigned int makeBet(
            GameStage stage,
            unsigned int startingBalance,
            unsigned int balance,
            unsigned int atStake,
            unsigned int bet,
            unsigned int potAmount,
            double winningProb
            )
    {
        // probable winning relative to coins at stake
        double probWinningAmountRel = (winningProb * potAmount) / atStake;
        double balanceRel = balance / (double) startingBalance;

        const Params &params = stageToParams.find(stage)->second;
        double predictedBetRel = probWinningAmountRel * params.probWeight * balanceRel * params.balanceWeight;

        // threshold not exceeded
        if(predictedBetRel > 1 - params.threshold && predictedBetRel < 1 + params.threshold){
            return bet;
        }

        unsigned int predictedBet = (unsigned int) predictedBetRel * bet;
        // raise over available balance
        if(predictedBet > bet && balance + atStake < predictedBet){
            return bet;
        }
        return predictedBet;
    }


private:
    explicit Agent(map<GameStage, Params> params, size_t generationParam = 0)
    : generation(generationParam), stageToParams(move(params))
    {
    }

    static double randomNumber()
    {
        return dis(engine);
    }

    size_t generation = 0;
    map<GameStage, Params> stageToParams;
    static std::default_random_engine engine;
    static std::uniform_real_distribution<> dis;
};

std::default_random_engine Agent::engine(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<> Agent::dis(0, 1);


#endif //SEMESTRAL_AGENT_H
