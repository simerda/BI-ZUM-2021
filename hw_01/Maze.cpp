//
// Created by simerjan on 09.03.21.
//
#ifdef _WIN32
#define CLEAR_CALL "cls"
#endif

#ifdef linux
#define CLEAR_CALL "clear"
#endif

#include "Tile.h"
#include "Maze.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <regex>
#include <vector>
#include <istream>
#include <iostream>
#include <functional>

using std::ifstream;
using std::string;
using std::runtime_error;
using std::regex;
using std::regex_search;
using std::vector;
using std::istringstream;
using std::endl;
using std::cout;
using std::cin;
using std::ref;

Maze::Maze(const string &path)
{
    ifstream input;
    input.open(path);
    if (!input.good()) {
        throw runtime_error("Cannot open provided file.");
    }

    string line;

    unsigned int width = 0;

    bool firstLine = true;
    while (getline(input, line)) {

        if (firstLine) {
            for (const char &character : line) {
                width++;
                if (character != 'X') {
                    throw runtime_error("Wrong format");
                }
            }

            if (width < 3) {
                throw runtime_error("Wrong format");
            }
        }

        if (line.length() != width) {
            throw runtime_error("Wrong format");
        }

        regex lineRegex("^X[X ]+X$");

        if (!regex_search(line, lineRegex)) {
            throw runtime_error("Wrong format");
        }

        bool lastLine = !firstLine;
        firstLine = false;
        for (const char &character : line) {
            if (character != 'X') {
                lastLine = false;
                break;
            }
        }

        vector<Tile> row;
        row.reserve(width);

        for (unsigned int i = 0; i < width; i++) {
            row.push_back(Tile::fromChar(line.at(i)));
        }
        field.push_back(row);

        if (lastLine) {
            break;
        }
    }

    regex startRegex("^start [1-9][0-9]*, *[1-9][0-9]*?$");
    regex endRegex("^end [1-9][0-9]*, *[1-9][0-9]*?$");

    if (!getline(input, line) || !regex_search(line, startRegex)) {
        throw runtime_error("Wrong format");
    }

    char c;
    line = line.substr(6);
    istringstream stringStream;
    stringStream.str(line);
    stringStream >> startX >> c >> startY;

    if (!getline(input, line) || !regex_search(line, endRegex)) {
        throw runtime_error("Wrong format");
    }
    line = line.substr(4);
    stringStream.clear();
    stringStream.str(line);
    stringStream >> endX >> c >> endY;

    if (field[startY][startX].getState() == TileEnum::WALL || field[endY][endX].getState() == TileEnum::WALL
        || (startX == endX && startY == endY)) {
        throw runtime_error("Wrong format");
    }

    field[startY][startX].setState(TileEnum::START);
    field[endY][endX].setState(TileEnum::END);

    // add tile neighbours
    for (unsigned int y = 0; y < field.size(); y++) {

        for (unsigned int x = 0; x < width; x++) {

            for (int vX = -1; vX <= 1; vX++) {
                for (int vY = -1; vY <= 1; vY++) {
                    int proposedX = (int) x + vX;
                    int proposedY = (int) y + vY;
                    // check if valid move
                    if (abs(vX) != abs(vY) && proposedX > 0 && (unsigned int) proposedX < width && proposedY > 0
                        && (unsigned int) proposedY < field.size()
                        && (field[proposedY][proposedX].getState() == TileEnum::FRESH
                        || field[proposedY][proposedX].getState() == TileEnum::END)) {
                        field[y][x].addNeighbour(field[proposedY][proposedX]);
                    }
                }
            }
        }
    }
}

void Maze::print()
{
    // clears console
    system(CLEAR_CALL);
    for (const vector<Tile> &row : field) {

        for (const Tile &tile : row) {
            cout << tile.toString();
        }
        cout << endl;
    }
    cout << endl << endl << "Legend:" << endl;
    cout << "S: Start" << endl;
    cout << "E: End" << endl;
    cout << "#: Opened node" << endl;
    cout << "◈: Closed node" << endl;
    cout << "o: Path" << endl;
    cout << "X: Wall" << endl;
    cout << "space: Fresh node" << endl;
    cout << endl;
}

void Maze::solve(SearchAlgorithmInterface &searchAlgorithm)
{
    reference_wrapper<Tile> current = field[startY][startX];

    string s;
    while(current.get().getState() != TileEnum::END){
        print();
        cout << "Press enter to continue..." << endl;
        getline(cin, s);

        searchAlgorithm.expand(current);
        try{
            current = searchAlgorithm.next();
        } catch (const runtime_error &e) {
            cout << "Path from start to finish doesn't exist." << endl;
            return;
        }
    }

    print();
    buildPath(current);
    cout << "Press enter to continue..." << endl;
    getline(cin, s);
    print();
}

void Maze::buildPath(Tile &endTile) const
{
    Tile * tilePtr = endTile.getExpandedBy();

    while (tilePtr->getState() != TileEnum::START){
        tilePtr->setState(TileEnum::PATH);
        tilePtr = tilePtr->getExpandedBy();
    }
}
