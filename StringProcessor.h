#pragma once
#include <iostream>
#include <fstream>
#include <string>

class StringProcessor{
    private:
    struct WordNode {
        char* word;
        WordNode* next;
    };
    
    char* rawData;
    WordNode* results;
    char marker;

    char* copyWord(const char* start, int length);

    public:
    StringProcessor();
    ~StringProcessor();

    void loadFromFile(const std::string& filename);
    void findWordsStartingWith(char symbol);
    void saveResultsToFile(const std::string& filename, char targetSymbol);
    void clearResults();
};