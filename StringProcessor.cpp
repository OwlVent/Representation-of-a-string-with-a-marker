#include "StringProcessor.h"

StringProcessor::StringProcessor(): rawData(nullptr), results(nullptr), tail(nullptr), marker('\0') {}

StringProcessor::~StringProcessor(){
    delete[] rawData;
    clearResults();
}

void StringProcessor::clearResults(){
    while (results != nullptr) {
        WordNode* temp = results;
        results = results->next;
        if (temp->word != nullptr) {
            delete[] temp->word;
        }
        delete temp;
    }
    tail = nullptr;
}

void StringProcessor::loadFromFile(const std::string& filename){
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    
    if (file.is_open()) {
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);    

        delete[] rawData;
        rawData = new char[size + 1];

        if (file.read(rawData, size)) {
            rawData[size] = marker;
        }

        file.close();
    } else {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
    }
}

char StringProcessor::loadTargetSymbol(const std::string& filename) {
    std::ifstream file(filename);
    char symbol = '\0';

    if (file.is_open()) {
        if (!(file >> symbol)) {
            std::cerr << "Warning: Settings file is empty!" << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open settings file: " << filename << std::endl;
    }

    return symbol;
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
        while (rawData[i] != marker && (rawData[i] == ' ' || rawData[i] == '\n' || rawData[i] == '\r')) {
            i++;
        }
        
        if (rawData[i] == marker) break;

        int wordStart = i;
        while (rawData[i] != marker && rawData[i] != ' ' && rawData[i] != '\n' && rawData[i] != '\r') {
            i++;
        }
        int wordLength = i - wordStart;

        if (rawData[wordStart] == symbol) {
            WordNode* newNode = new WordNode;
            newNode->word = copyWord(&rawData[wordStart], wordLength);
            newNode->next = nullptr;
            if (!results) {
                results = newNode;
                tail = newNode;
            } else {
                tail -> next = newNode;
                tail = newNode;
            }
        }
    }
}

void StringProcessor::saveResultsToFile(const std::string& filename, char targetSymbol) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open output file!" << std::endl;
        return;
    }

    file << "--- Control Output ---" << std::endl;
    if (rawData) {
        file << "Raw stored data: " << rawData << std::endl;
    } else {
        file << "No data loaded." << std::endl;
    }

    file << "\n--- Search Results ---" << std::endl;
    file << "Target symbol: '" << targetSymbol << "'" << std::endl;

    WordNode* curr = results;
    if (curr == nullptr) {
        file << "No words found starting with this symbol." << std::endl;
    } else {
        int count = 0;
        while (curr != nullptr) {
            count++;
            file << count << ". " << curr->word << std::endl;
            curr = curr->next; 
        }
    }

    file.close();
    std::cout << "Results successfully saved to " << filename << std::endl;
}