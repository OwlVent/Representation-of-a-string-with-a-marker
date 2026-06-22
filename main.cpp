#include "StringProcessor.h"
#include <iostream>

int main() {
    StringProcessor processor;

    char target = processor.loadTargetSymbol("settings.txt");
    if (target == '\0') {
        std::cerr << "Failed to load target symbol from settings.txt" << std::endl;
        return 1;
    }

    if (!processor.loadData("input.txt")) return 1;

    processor.processWords(target);
    processor.saveToFile("output.txt", target);

    std::cout << "Success! Please check output.txt for results." << std::endl;

    return 0;
}