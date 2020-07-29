#include "gtest/gtest.h"
#include "Simulator.h"
#include "Team.h"
#include "Game.h"
#include <algorithm>


class SimulatorTest : public ::testing::Test {
protected:
  //runs only once
  static void SetUpTestCase()
  {
    createTeams("../data/TestSetTeams.txt");
    loadGames("../data/TestSetGames.txt",0,false);
  }
  //runs for every test case
  SimulatorTest() {
    teamMap = getTeamMap();
    it = teamMap.begin();
    gameMatrix = getGameMatrix();
  }
//can be used anywhere
std::map<int, Team*>::iterator it;
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> gameMatrix;
std::map<int, Team*> teamMap;
int totalTeams= getNumTeams();
};

//start create teams test
TEST_F(SimulatorTest, teamSize)
{
    EXPECT_EQ(totalTeams, 4);
}

TEST_F(SimulatorTest, createTeams)
{
    EXPECT_EQ("Beast Squares", it->second->getName());
    std::advance(it,1);
    EXPECT_EQ("Likelihood Loggers", it->second->getName());
    std::advance(it,1);
    EXPECT_EQ("Linear Aggressors", it->second->getName());
    std::advance(it,1);
    EXPECT_EQ("Gaussian Eliminators", it->second->getName());
}
//end create teams test

//start populate matrix test
TEST_F(SimulatorTest, populateMatrix)
{
	//checking n-1 diagonal entries because the last row is all ones which would throw off total
	int diagonal_sum = 0;
	for(int i = 0; i < 3; i++)
	{
		diagonal_sum += gameMatrix.coeff(i,i);
	}
	EXPECT_EQ(diagonal_sum, 7);
}

TEST_F(SimulatorTest, numGames)
{
	EXPECT_EQ(getNumGamesPlayed(),5);
}

///////////////////////////////////////////////////////////////////////////////////

class GameTest : public ::testing::Test {
protected:
  //runs only once
  void SetUp()
  {
  team0 = new Team("team0",0);
  team1 = new Team("team1",1);
  game = new Game(10,team0,team1,50,51);
  }

  void TearDown()
  {
    delete team0;
    delete team1;
    delete game;
  }
//can be used anywhere
Team* team0;
Team* team1;
Game* game;
};

TEST_F(GameTest, day)
{
    int day = game->getDay();

    EXPECT_EQ(day, 10);
}

TEST_F(GameTest, teams)
{
    Team* test_team0 = new Team("team0",0);
    Team* test_team1 = new Team("team1",1);

    std::vector<Team*> teams = game->getTeams();

    EXPECT_TRUE(std::find(teams.begin(), teams.end(), team0) != teams.end());
    EXPECT_TRUE(std::find(teams.begin(), teams.end(), team1) != teams.end());
    delete test_team0;
    delete test_team1;

}

TEST_F(GameTest, scores)
{
	int s1 = game->getScore1();
	int s2 = game->getScore2();
	EXPECT_EQ(s1,50);
	EXPECT_EQ(s2,51);
}

int main(int argc, char **argv) {

testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();

}