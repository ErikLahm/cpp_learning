#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class GameParser {
private:
  const std::string game_line;

public:
  GameParser(std::string line) : game_line(line) {};
  int get_gameID();
  std::string getDrawString();
  void parseSingleDraws(std::string &draw, std::array<int, 3> &counts);
  std::vector<std::array<int, 3>> getParsedDraws();
  std::vector<std::string> getSingleDraws();
};

class GameRules {
private:
  std::array<int, 3> maxNumCubes;

public:
  GameRules(int red, int green, int blue) {
    maxNumCubes[0] = red;
    maxNumCubes[1] = green;
    maxNumCubes[2] = blue;
  };
  bool applyRules(std::vector<std::array<int, 3>> &draws);
};

bool GameRules::applyRules(std::vector<std::array<int, 3>> &draws) {
  int red = 0, green = 0, blue = 0;
  for (auto a : draws) {
    if (a[0] > red)
      red = a[0];
    if (a[1] > green)
      green = a[1];
    if (a[2] > blue)
      blue = a[2];
  }
  if ((red <= maxNumCubes[0]) and (green <= maxNumCubes[1]) and
      (blue <= maxNumCubes[2]))
    return true;
  else
    return false;
}

std::vector<std::array<int, 3>> GameParser::getParsedDraws() {
  std::vector<std::string> draws = getSingleDraws();
  std::vector<std::array<int, 3>> allCounts;
  std::array<int, 3> counts;
  for (auto s : draws) {
    parseSingleDraws(s, counts);
    allCounts.push_back(counts);
  }
  return allCounts;
}

int GameParser::get_gameID() {
  std::stringstream stream(game_line);
  std::string token;
  int gameID;

  getline(stream, token, ':');
  std::stringstream tokenstream(token);
  std::string game;
  tokenstream >> game >> gameID;

  return gameID;
}

std::string GameParser::getDrawString() {
  size_t pos = game_line.find(':');
  std::string drawString = game_line.substr(pos + 1);
  return drawString;
}

std::vector<std::string> GameParser::getSingleDraws() {
  std::string drawString = getDrawString();
  std::stringstream drawStream(drawString);
  std::string token;
  std::vector<std::string> draws;

  while (std::getline(drawStream, token, ';')) {
    draws.push_back(token);
  }
  return draws;
}

void GameParser::parseSingleDraws(std::string &draw,
                                  std::array<int, 3> &counts) {
  std::stringstream drawStream(draw);
  std::string token;

  counts.fill(0);

  int count;
  std::string color;

  std::unordered_map<std::string, int> colorIndex = {
      {"red", 0}, {"green", 1}, {"blue", 2}};

  while (getline(drawStream, token, ',')) {
    std::stringstream tokenStream(token);

    tokenStream >> count >> color;

    if (colorIndex.find(color) != colorIndex.end()) {
      counts[colorIndex[color]] += count;
    }
  }
}

int main() {
  std::string line;
  std::fstream file("input.txt");
  int game_id_sum = 0;
  GameRules rules(12, 13, 14);
  if (file.is_open()) {
    while (getline(file, line)) {
      GameParser game(line);
      int ID = game.get_gameID();
      std::vector<std::array<int, 3>> test = game.getParsedDraws();
      bool result = rules.applyRules(test);
      if (result) {
        game_id_sum += ID;
      }
    }
  }
  std::cout << game_id_sum;
}
