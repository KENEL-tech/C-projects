// Counts lines, words and characters in a text file
// and shows the most frequent words.
// Usage: word_counter <file> [how many top words, default 5]

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Makes a word lowercase and removes punctuation around it,
// so "Hello," and "hello" count as the same word.
std::string cleanWord(const std::string &word) {
    std::string result;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: word_counter <file> [top N]\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }

    int topCount = 5;
    if (argc >= 3) topCount = std::stoi(argv[2]);

    int lines = 0, words = 0, characters = 0;
    std::map<std::string, int> frequency;

    std::string line;
    while (std::getline(file, line)) {
        lines++;
        characters += static_cast<int>(line.size());

        std::string word;
        for (size_t i = 0; i <= line.size(); i++) {
            // A space or the end of the line finishes the current word.
            if (i == line.size() || std::isspace(static_cast<unsigned char>(line[i]))) {
                std::string cleaned = cleanWord(word);
                if (!cleaned.empty()) {
                    words++;
                    frequency[cleaned]++;
                }
                word.clear();
            } else {
                word += line[i];
            }
        }
    }

    std::cout << "Lines:      " << lines << "\n";
    std::cout << "Words:      " << words << "\n";
    std::cout << "Characters: " << characters << "\n";

    // Copy the map into a vector so it can be sorted by count.
    std::vector<std::pair<std::string, int>> sorted(frequency.begin(), frequency.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    std::cout << "\nMost frequent words:\n";
    for (int i = 0; i < topCount && i < static_cast<int>(sorted.size()); i++) {
        std::cout << "  " << sorted[i].first << " - " << sorted[i].second << "\n";
    }
    return 0;
}
