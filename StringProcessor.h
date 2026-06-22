#pragma once
#include <iostream>
#include <fstream>
#include <string>

const int N = 55; 

class StringProcessor {
private:
    char inputArray[N + 1];
    char outputArray[N + 1];
    char stringMarker;       
    char fileMarker;         
    bool isDataLoaded;       

public:
    StringProcessor();
    
    char loadTargetSymbol(const std::string& filename);
    bool loadData(const std::string& filename);
    void processWords(char target);
    void saveToFile(const std::string& filename, char target);
};