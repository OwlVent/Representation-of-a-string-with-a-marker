#include "StringProcessor.h"

StringProcessor::StringProcessor(): rawData(nullptr), results(nullptr), marker('.') {}

StringProcessor::~StringProcessor(){
    delete[] rawData;
    clearResults();
}

void StringProcessor::clearResults(){
    while(results){
        WordNode* temp = results;
        results = results -> next;
        delete[] temp -> word;
        delete temp;
    }
}

void StringProcessor::loadFromFile(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()) return;

    std::string line;
    if(std::getline(file, line)){
        delete[] rawData;
        rawData = new char[line.length() + 1];
        for (size_t i = 0; i < line.length(); ++i){
            rawData[i] = line[i];
        }
        rawData[line.length()] = marker;
    }
    file.close();
}

char* StringProcessor::copyWord(const char* start, int length){
  char* newW = new char[length + 1];
    for (int i = 0; i < length; ++i) {
        newW[i] = start[i];
    }
    newW[length] = '\0';
    return newW;
}

void StringProcessor::findWordsStartingWith(char symbol) {
    clearResults();
    if (!rawData) return;

    int i = 0;
    while (rawData[i] != marker) {
        while (rawData[i] != marker && rawData[i] == ' ') i++;
        
        if (rawData[i] == marker) break;

        int wordStart = i;
        while (rawData[i] != marker && rawData[i] != ' ') i++;
        int wordLength = i - wordStart;

        if (rawData[wordStart] == symbol) {
            WordNode* newNode = new WordNode;
            newNode->word = copyWord(&rawData[wordStart], wordLength);
            if (!results) {
                results = newNode;
                newNode->next = nullptr;
            } else {
                WordNode* temp = results;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
                newNode->next = nullptr;
            }
        }
    }
}

void StringProcessor::saveResultsToFile(const std::string& filename, char targetSymbol) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "Input Data: " << rawData << std::endl;
    file << "Target Symbol: " << targetSymbol << std::endl;
    file << "Found Words:" << std::endl;

    WordNode* temp = results;
    if (!temp) {
        file << "No words found.";
    } else {
        while (temp) {
            file << "- " << temp->word << std::endl;
            temp = temp->next;
        }
    }
    file.close();
}