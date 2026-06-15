#include "StringProcessor.h"


int main() {
    StringProcessor processor;
    char target = 'a';

    processor.loadFromFile("input.txt");
    processor.findWordsStartingWith(target);
    processor.saveResultsToFile("output.txt", target);

    return 0;
}