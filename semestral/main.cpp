
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <functional>
#include "table.h"

using namespace std;

const unsigned int STARTING_BALANCE = 500;

int initAgent(const string &filename)
{
    Agent agent = Agent::makeRandom();
    try{
        agent.saveToFile(filename);
    }catch (const exception& e){
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}

int play(const vector<Player> &players)
{
    Table table;
    for(const Player &player : players){
        table.addPlayer(player);
    }

    table.startGame();
    return 0;
}

void crossbreed(vector<Agent> &population, unsigned int populationSize)
{
    Agent firstParent = population[0];
    Agent secondParent = population[1];

    while(population.size() < populationSize){
        population.push_back(Agent::crossbreed(firstParent, secondParent));
    }

    firstParent.incrementGeneration();
    secondParent.incrementGeneration();
}

Agent train(vector<Agent> &opponents, unsigned int populationSize, unsigned int generations)
{
    vector<Agent> population{opponents.front()};
    opponents.erase(opponents.begin());
    while(population.size() < populationSize){
        population.push_back(Agent::makeRandom());
    }

    size_t generationNumber = population.front().getGeneration();
    for(size_t g = 0; g < generations; g++){
        cout << "Training generation number " << generationNumber++ << "." << endl;

        unsigned int fitnessSum = 0;
        vector<pair<reference_wrapper<Agent>, unsigned int>> fitness;
        for(unsigned int i = 0; i < populationSize; i++){

            Table table;
            table.addPlayer(Player("", STARTING_BALANCE, &population[i]));
            for(Agent &opponent : opponents){
                table.addPlayer(Player("", STARTING_BALANCE, &opponent));
            }

            fitness.emplace_back(ref(population[i]), table.train(30));
            fitnessSum += fitness.back().second;
            cout << "Individual no. " << i << " fitness: " << fitness.back().second << endl;
        }

        double averageFitness = (double) fitnessSum / populationSize;

        sort(fitness.begin(), fitness.end(), [](
                const pair<reference_wrapper<Agent>,unsigned int> &a,
                const pair<reference_wrapper<Agent>, unsigned int> &b){
            return a.second < b.second;
        });
        auto medianFitness = (double) fitness[populationSize / 2].second;
        if((populationSize % 2) == 1){
            medianFitness = (medianFitness + fitness[(populationSize / 2) + 1].second) / 2;
        }
        size_t minFitness = fitness.front().second;
        size_t maxFitness = fitness.back().second;

        reference_wrapper<Agent> firstParent = fitness[populationSize - 1].first;
        reference_wrapper<Agent> secondParent = fitness[populationSize - 2].first;

        cout << "Minimum fitness: " << minFitness << endl;
        cout << "Maximum fitness: " << maxFitness << endl;
        cout << "Average fitness: " << setprecision(2) << fixed << averageFitness << endl;
        cout << "Median fitness: " << medianFitness << endl;

        population = vector<Agent>{firstParent, secondParent};
        crossbreed(population, populationSize);
    }

    return population.front();
}


int main(int argc, char **argv)
{
    if(argc < 3){
        cout << "Too few arguments." << endl;
        cout << "Usage: (play OR init OR train) [arguments]" << endl;
        cout << "Use \"play player1 human player2 models/agent.ag player3 human ...\" to play a game." << endl;
        cout << "For each player you have to enter name and path to stored agent or keyword \"human\" for interactive player." << endl << endl;
        cout << "Use \"init models/agent.ag\" to initialize random agent and store it to provided path." << endl << endl;
        cout << "Use \"train models/agent.ag models/opponent1.ag models/opponent2.ag models/opponent3.ag"
        << "models/opponent4.ag models/opponent5.ag (pop-size) (generations)\" to train given agent (first argument) against provided opponents." << endl;
        cout << "Only the first agent will be trained - opponent agents are used only as reference." << endl;
        cout << "Population size means how many times will the agent be copied and then trained independently and crossbred." << endl;
        cout << "Number of generations means how many times should be the fittest agents crossbred." << endl;
        return 5;
    }

    if(argv[1] == "play"s){
        if((argc % 2) != 0){
            cout << "Wrong number of arguments" << endl;
        }
        int ret;
        try{
            vector<Agent*> agents;
            vector<Player> players;
            for(unsigned int i = 1; i < (unsigned int) argc / 2; i++){
                Agent *agentPtr = nullptr;
                if(argv[2 * i + 1] != "human"s){
                    agents.push_back(new Agent(Agent::loadFromFile(argv[ 2 * i + 1])));
                    agentPtr = agents.back();
                }

                players.emplace_back(argv[i * 2], STARTING_BALANCE, agentPtr);
            }

            ret = play(players);
        }catch (const exception& e){
            cout << "Error: " << e.what() << endl;
            return 3;
        }
        return ret;
    }

    if(argv[1] == "init"s){
        int ret;
        try{
            ret = initAgent(argv[2]);
        }catch (const exception& e){
            cout << "Error: " << e.what() << endl;
            return 4;
        }

        return ret;
    }

    if(argv[1] == "train"s){
        int ret;
        try{

            vector<Agent> agents;
            for(unsigned int i = 2; i < (unsigned int) argc - 2; i++){
                agents.push_back(Agent::loadFromFile(argv[i]));
            }
            unsigned int populationSize = atoi(argv[argc - 2]);
            unsigned int numberOfGenerations = atoi(argv[argc - 1]);

            if(populationSize < 2 || numberOfGenerations < 1) {
                cout << "Wrong arguments." << endl;
                return 6;
            }

            train(agents, populationSize, numberOfGenerations).saveToFile(argv[2]);
            ret = 0;
        }catch (const exception& e){
            cout << "Error: " << e.what() << endl;
            return 7;
        }

        return ret;
    }

    cout << "Wrong command \"" << argv[1] << "\".";
    return 2;
}

