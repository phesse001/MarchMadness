#include "Simulator.h"

void populateMatrix(int team1Index, int team2Index, int score1Int, int score2Int);

int main() {
    //createTeams(string("D:\\Wilmot\\Documents\\Personal\\Workspace\\March Madness Simulator\\Data\\NCAA Mens BasketBall 2019\\TestSetTeams.txt"));
    //loadGames(string("D:\\Wilmot\\Documents\\Personal\\Workspace\\March Madness Simulator\\Data\\NCAA Mens BasketBall 2019\\TestSetGames.txt"));
    createTeams(string("D:\\Wilmot\\Documents\\Personal\\Workspace\\March Madness Simulator\\Data\\NCAA Mens BasketBall 2019\\NCAABasketballTeams.txt"));
    loadGames(string("D:\\Wilmot\\Documents\\Personal\\Workspace\\March Madness Simulator\\Data\\NCAA Mens BasketBall 2019\\NCAABasketballGames.txt"));

    solutionVector = gameMatrix.lu().solve(scores);



    map<int, Team*>::iterator itr;
    for(itr = teamMap.begin(); itr != teamMap.end(); ++itr){
        itr->second->addRank(solutionVector.row(itr->second->getId() -1).value());
        resultVector.push_back(*(itr->second));
    }

    //sort Teams by rank

    sort(resultVector.begin(), resultVector.end());
    vector<Team>::iterator itr2;
    for(itr2 = resultVector.end() - 1; itr2 != resultVector.begin() - 1 ; --itr2){
        cout << itr2->getName() << endl;
    }

}


void createTeams(string teamData) {
    string id, name;
    ifstream teams (teamData);
    if(teams.is_open()){
        while (getline(teams, id, ',')){
            getline(teams, name, '\n');
            int idNum = stoi(id);
            remove(name.begin(), name.end(),' ');
            Team* tempTeam = new Team(name, idNum);
            teamCollection.push_back(tempTeam);
            teamMap.insert(pair<int, Team*>(idNum, tempTeam));
            numTeams++;
        }
        teams.close();
    }
    else cout << "Unable to open file";
}

void loadGames(string gameData){
    gameMatrix = Matrix<double, Dynamic, Dynamic>::Zero(numTeams , numTeams);
    scores = VectorXd::Zero(numTeams);

    string days, date, team1, field1, score1, team2, field2, score2;
    fstream games(gameData);
    if(games.is_open()){
        while(getline(games, days, ',')){
            getline(games, date, ',');
            getline(games, team1, ',');
            getline(games, field1, ',');
            getline(games, score1, ',');
            getline(games, team2, ',');
            getline(games, field2, ',');
            getline(games, score2, ' ');
            getline(games, score2, ' ');

            int daysInt = stoi(days);
            int team1Index = stoi(team1);
            int team2Index = stoi(team2);
            int score1Int = stoi(score1);
            int score2Int = stoi(score2);
            Game tempGame(daysInt, teamMap.at(team1Index), teamMap.at(team2Index), score1Int, score2Int);
            teamMap.at(team1Index)->addGame(&tempGame);
            teamMap.at(team2Index)->addGame(&tempGame);
            //gameCollection.push_back(&tempGame);
            numGamesPlayed++;


            populateMatrix(team1Index, team2Index, score1Int, score2Int);
            for(int i = 0; i < numTeams; i++){
                gameMatrix.row(numTeams - 1).col(i) << 1;
            }
            scores.row(numTeams - 1) << 0;
        }
    }
    else cout << "Unable to open file";
}

void populateMatrix(int team1Index, int team2Index, int score1Int, int score2Int) {
    gameMatrix.row(team1Index - 1 ).col(team2Index - 1) << -1;
    gameMatrix.row(team2Index -1 ).col(team1Index -1) <<  -1;
    gameMatrix.row(team1Index -1 ).col(team1Index -1) <<  teamMap.at(team1Index)->getNumGamesPlayed();
    gameMatrix.row(team2Index -1 ).col(team2Index -1) <<  teamMap.at(team2Index)->getNumGamesPlayed();
    if(score1Int > score2Int){
        int temp = scores.row(team1Index - 1).value();
        scores.row(team1Index - 1 ) << temp + (score1Int - score2Int);
        temp = scores.row(team2Index - 1).value();
        scores.row(team2Index - 1 ) << temp + (score2Int - score1Int);
    }
    else{
        int temp = scores.row(team2Index - 1).value();
        scores.row(team2Index - 1 ) << temp + (score1Int - score2Int);
        temp = scores.row(team1Index - 1).value();
        scores.row(team1Index - 1 ) << temp + (score2Int - score1Int);
    }
}

