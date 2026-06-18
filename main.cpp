#include "StringProcessor.h"


int main() {
    StringProcessor processor;

    char target = processor.loadTargetSymbol("settings.txt");
    
    if (target == '\0') {
        std::cerr << "No target symbol. Exiting..." << std::endl;
        return 1;
    }

    processor.loadFromFile("input.txt");
    processor.findWordsStartingWith(target);
    processor.saveResultsToFile("output.txt", target);

    return 0;
}