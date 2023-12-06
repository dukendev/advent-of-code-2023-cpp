#include "iostream"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

inline std::string trim(std::string &str) {
  str.erase(str.find_last_not_of(' ') + 1); // suffixing spaces
  str.erase(0, str.find_first_not_of(' ')); // prefixing spaces
  return str;
}

std::vector<std::string> str_tokenizer(std::string s, char del) {
  std::istringstream ss(s);
  std::string word;
  std::vector<std::string> tokens;

  while (getline(ss, word, del)) {
    if (!word.empty()) {
      tokens.push_back(trim(word));
    }
  }

  return tokens;
}

int find_points(std::string line) {
  std::vector<std::string> cardContents;
  cardContents = str_tokenizer(line, '|');
  std::string match, card;
  match = str_tokenizer(cardContents[0], ':')[1];
  card = cardContents[1];
  std::cout << match << " cards in hand " << card << std::endl;

  std::vector<std::string> matchNums;
  std::vector<std::string> cardNums;

  matchNums = str_tokenizer(match, ' ');
  cardNums = str_tokenizer(card, ' ');

  std::sort(matchNums.begin(), matchNums.end());
  std::sort(cardNums.begin(), cardNums.end());

  int hits = 0;

  std::vector<std::string>::iterator it = matchNums.begin();
  std::vector<std::string>::iterator end = matchNums.end();

  std::vector<std::string>::iterator it2 = cardNums.begin();
  std::vector<std::string>::iterator end2 = cardNums.end();

  while (it != end && it2 != end2) {
    if (std::stoi(*it) == std::stoi(*it2)) {
      std::cout << "hit for " << *it << " and " << *it2 << std::endl;
      hits++;
      ++it;
      ++it2;
    } else if (std::stoi(*it) < std::stoi(*it2)) {
      ++it;
    } else {
      ++it2;
    }
  }

  int point = std::pow(2, hits - 1);

  std::cout << "point " << point << std::endl;

  return point;
}

int main() {

  std::string inputPath = "./input.txt";
  std::fstream openFile(inputPath);

  if (!openFile.is_open()) {
    std::cerr << "Error opening file: " << inputPath << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(openFile, line)) {
    lines.push_back(line);
  }
  openFile.close();

  int sum;
  for (auto l : lines) {
    sum += find_points(l);
  }

  std::cout << "answer is : " << sum;

  return 0;
}
