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

void print(std::vector<int> v) {
  for (auto i : v) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int find_points(std::string line, bool part2) {
  std::vector<std::string> cardContents;
  cardContents = str_tokenizer(line, '|');
  std::string match, card;
  match = str_tokenizer(cardContents[0], ':')[1];
  card = cardContents[1];

  std::vector<std::string> matchNums;
  std::vector<std::string> cardNums;

  matchNums = str_tokenizer(match, ' ');
  cardNums = str_tokenizer(card, ' ');

  auto stringToInt = [](const std::string &s) { return std::stoi(s); };

  std::vector<int> intMatchNums;
  std::transform(matchNums.begin(), matchNums.end(),
                 std::back_inserter(intMatchNums), stringToInt);

  std::vector<int> intCardNums;
  std::transform(cardNums.begin(), cardNums.end(),
                 std::back_inserter(intCardNums), stringToInt);

  std::sort(intMatchNums.begin(), intMatchNums.end());
  std::sort(intCardNums.begin(), intCardNums.end());

  int hits = 0;

  std::vector<int>::iterator it = intMatchNums.begin();
  std::vector<int>::iterator end = intMatchNums.end();

  std::vector<int>::iterator it2 = intCardNums.begin();
  std::vector<int>::iterator end2 = intCardNums.end();

  while (it != end && it2 != end2) {
    if (*it == *it2) {
      hits++;
      ++it;
      ++it2;
    } else if (*it < *it2) {
      ++it;
    } else {
      ++it2;
    }
  }

  int point;
  if (part2 == true) {
    point = hits;
  } else {
    point = std::pow(2, hits - 1);
  }
  return point;
}

void solvePart1(std::vector<std::string> lines) {
  int sum;
  for (auto l : lines) {
    sum += find_points(l, false);
  }
  std::cout << "answer is : " << sum;
}

void solvePart2(std::vector<std::string> &lines) {
  int sum = 0;
  std::vector<int> hit_list;
  int size = lines.size();

  for (int i = 0; i < size; i++) {
    hit_list.push_back(find_points(lines[i], true));
  }

  std::vector<int> instances(size, 1);
  print(hit_list);
  std::cout << std::endl;

  for (int i = 0; i < size; i++) {
    std::cout << "processing orignal " << i << std::endl;
    int cur = hit_list[i];
    int multiple = instances[i];
    for (int j = 0; j < cur; j++) {
      instances[j + i + 1] += multiple;
    }
    print(instances);
  }

  for (auto i : instances) {
    sum += i;
  }

  std::cout << "answer is : " << sum;
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

  //  solvePart1(lines);
  solvePart2(lines);

  return 0;
}
