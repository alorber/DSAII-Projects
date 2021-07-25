// Andrew Lorber
// DSA II Project 1 - Spell Check
// Main Program

#include "hash.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>

// Checks if character is valid
bool isValidChar(char c){
    return ((int(c) == 39) || (int(c) == 45) || isalnum(c));
}

// Fills dictionary hash table with words from file
void createDictionary(std::string dictf, hashTable* dictionary){
    // Opens file
    std::ifstream fin(dictf);
    std::string word;

    // Reads in words
    bool invalid = false;
    while(getline(fin, word)){
        // Checks for valid word
        invalid = false;
        if(word.length() <= 20){
            for(char c : word){
                if(!isValidChar(c)){
                    invalid = true;
                    break;
                }
            }
            if(!invalid){
                // Converts to lower-case
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                dictionary->insert(word);
            }
        }  
    }
    fin.close();
}

void spellCheck(std::string inf, std::string outf, hashTable* dictionary){
    // Opens file
    std::ifstream fin(inf);
    std::ofstream fout(outf);
    std::string line;
    std::string word = "";
    char current_char;
    int line_num = 0;
    bool ignore = false; // Whether word has digit and should be ignored.

    // Reads in one line at a time
    while(getline(fin, line)){
        line_num++;

        // Reads each character in the line
        for(char c : line){
            // Checks if valid character
            if(isValidChar(c)){
                word += tolower(c);

                // Checks if digit
                if(isdigit(c)){
                    ignore = true;
                }
            } else {
                if(!ignore && word.length() > 0){
                    // Checks if word is too long
                    if(word.length() > 20){
                        fout << "Long word at line " << line_num << ", starts: " << word.substr(0, 20) << '\n';
                    }

                    // Check current word in dictionary
                    else if(!dictionary->contains(word)){
                        fout << "Unknown word at line " << line_num << ": " << word << '\n';
                    }
                }

                word = "";
                ignore = false;
            }
        }
        // Checks word at newline
        if(!ignore && word.length() > 0){
                    // Checks if word is too long
                    if(word.length() > 20){
                        fout << "Long word at line " << line_num << ", starts: " << word.substr(0, 20) << '\n';
                    }

                    // Check current word in dictionary
                    else if(!dictionary->contains(word)){
                        fout << "Unknown word at line " << line_num << ": " << word << '\n';
                    }
        }

        word = "";
        ignore = false;
    }
    fin.close();
    fout.close();
}

int main(){
    // Gets files from user
    std::string dictf, inf, outf;
    std::cout << "Please enter the dictionary file.\n";
    getline(std::cin, dictf);
    std::cout << "Please enter the input file to be spell-checked.\n";
    getline(std::cin, inf);
    std::cout << "Please enter the output file.\n";
    getline(std::cin, outf);

    // Creates dictionary hash table
    hashTable dictionary;
    clock_t start = clock();
    createDictionary(dictf, &dictionary);
    clock_t end = clock();
    std::cout << "Total time (in seconds) to load dictionary: " << ((double) (end - start)) / CLOCKS_PER_SEC << '\n';


    // Spell-checks input file
    start = clock();
    spellCheck(inf, outf, &dictionary);
    end = clock();
    std::cout << "Total time (in seconds) to check document:: " << ((double) (end - start)) / CLOCKS_PER_SEC << '\n'; 
}