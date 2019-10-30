//
// Created by wilmo on 10/6/2019.
//

#ifndef MARCH_MADNESS_SIMULATOR_SIMULATOR_H
#define MARCH_MADNESS_SIMULATOR_SIMULATOR_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "./eigen/Eigen/Core"
#include "./eigen/Eigen/Dense"
#include "Team.h"

class Team;
class Game;
using namespace std;
using namespace Eigen;

/**
 * Collection holding all teams.
 */
vector<Team*> teamCollection;


vector<Team> resultVector;

map<int, Team*> teamMap;

Matrix<double, Dynamic, Dynamic> gameMatrix;

VectorXd scores;

VectorXd solutionVector;

/**
 * Method responsible for converting team text file into team objests
 * @param teamData
 */
void createTeams(string teamData);

int numGamesPlayed;
int numTeams;


void loadGames(string gameData);
#endif //MARCH_MADNESS_SIMULATOR_SIMULATOR_H
