#include "StringProcessor.h"

StringProcessor::StringProcessor() : stringMarker('\0'), fileMarker('\0'), isDataLoaded(false) {
    for (int i = 0; i <= N; i++) {
        inputArray[i] = '\0';
        outputArray[i] = '\0';
    }
}

char StringProcessor::loadTargetSymbol(const std::string& filename) {
    std::ifstream file(filename);
    char symbol = '\0';
    if (file.is_open()) {
        file >> symbol; 
        file.close();
    } else {
        std::cerr << "Error: Settings file not found!" << std::endl;
    }
    return symbol;
}

bool StringProcessor::loadData(const std::string& filename) {
    for (int j = 0; j <= N; j++) {
        inputArray[j] = '\0';
        outputArray[j] = '\0';
    }
    isDataLoaded = false;

    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: File '" << filename << "' not found." << std::endl;
        return false;
    }
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: Input file is empty!" << std::endl;
        return false;
    }
    if (!(file >> stringMarker >> fileMarker)) {
        std::cerr << "Error: Could not read markers. Check file format!" << std::endl;
        return false;
    }

    file.ignore(1, ' ');

    char ch;
    int i = 0;

    while (file.get(ch) && ch != fileMarker && i < N) {
        inputArray[i] = ch;
        i++;
    }

    if (i == N && ch != fileMarker && !file.eof()) {
        std::cerr << "\n!!! ATTENTION: Input buffer limit reached (N = " << N << ") !!!" << std::endl;
        std::cerr << "Only the first " << N << " characters were loaded into memory." << std::endl;
        std::cerr << "The rest of the file was ignored.\n" << std::endl;
    }

    inputArray[i] = stringMarker;
    
    isDataLoaded = true;
    file.close();
    
    return true;
}

void StringProcessor::processWords(char target) {
    if (!isDataLoaded || target == '\0') return;

    int inIdx = 0;   
    int outIdx = 0;  

    while (inputArray[inIdx] != stringMarker) {
        while (inputArray[inIdx] != stringMarker && inputArray[inIdx] == ' ') {
            inIdx++;
        }
        
        if (inputArray[inIdx] == stringMarker) break;
        int wordStart = inIdx;
        while (inputArray[inIdx] != stringMarker && inputArray[inIdx] != ' ') {
            inIdx++;
        }
        int wordEnd = inIdx;
        int wordLength = wordEnd - wordStart;

        if (inputArray[wordStart] == target) {
            int spaceNeeded = (outIdx > 0) ? 1 : 0;
            if (outIdx + wordLength + spaceNeeded >= N) {
                std::cerr << "Warning: Output buffer limit reached!" << std::endl;
                break;
            }
            if (outIdx > 0) outputArray[outIdx++] = ' ';
            for (int k = 0; k < wordLength; k++) {
                outputArray[outIdx++] = inputArray[wordStart + k];
            }
        }
    }
    outputArray[outIdx] = stringMarker;
}

void StringProcessor::saveToFile(const std::string& filename, char target) {
    if (!isDataLoaded) return;

    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    file << "1. Control Output:" << std::endl;
    for (int i = 0; i < N; i++) {
        file << inputArray[i];
        if (inputArray[i] == stringMarker) break;
    }
    file << std::endl;

    file << "\n2. Final Result:" << std::endl;
    if (outputArray[0] == stringMarker) {
        file << "[No matches found]" << std::endl;
    } else {
        for (int i = 0; i <= N; i++) {
            file << outputArray[i];
            if (outputArray[i+1] == stringMarker) break;
        }
        file << std::endl;
    }

    file.close();
}