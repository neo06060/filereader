#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>

// This class reads a text file, counts how many times each word appears,
// and can display or save the results.
class FileAnalyzer {
public:
    void readFile(const std::string& filename);                  // Reads file content into a string
    void parseWords();                                           // Breaks content into words and counts them
    void displayWordCount() const;                               // Outputs word count to the console
    void writeWordCountToFile(const std::string& outputFilename) const; // Writes results to a file

private:
    std::map<std::string, int> wordCount;   // Stores word and how often it appears
    std::string content;                    // Stores the entire content of the file

    void filterUnwantedCharacters(std::string& word); // Cleans words: removes punctuation, lowers case
};

// Loads entire file into 'content' string
void FileAnalyzer::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    file.close();
}

// Goes through 'content', extracts words, and counts them
void FileAnalyzer::parseWords() {
    std::istringstream stream(content);
    std::string word;
    while (stream >> word) {
        filterUnwantedCharacters(word);
        if (!word.empty()) {
            ++wordCount[word];
        }
    }
}

// Removes punctuation and makes all letters lowercase
void FileAnalyzer::filterUnwantedCharacters(std::string& word) {
    word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
        return std::ispunct(c);
        }), word.end());

    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
}

// Prints each word and how many times it appears
void FileAnalyzer::displayWordCount() const {
    for (const auto& pair : wordCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// Saves the word count results into an output file
void FileAnalyzer::writeWordCountToFile(const std::string& outputFilename) const {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        return;
    }
    for (const auto& pair : wordCount) {
        outFile << pair.first << ": " << pair.second << std::endl;
    }
    outFile.close();
}

// Main function: gets filenames from user, runs the analysis, shows and saves result
int main() {
    FileAnalyzer analyzer;
    std::string filename;

    std::cout << "Enter the path to the text file: ";
    std::getline(std::cin, filename);

    analyzer.readFile(filename);        // Read file into memory
    analyzer.parseWords();             // Process and count words
    analyzer.displayWordCount();       // Show results in console

    std::string outputFilename;
    std::cout << "Enter the output file name: ";
    std::getline(std::cin, outputFilename);

    analyzer.writeWordCountToFile(outputFilename); // Save results to file

    return 0;
}
