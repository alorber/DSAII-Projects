// Andrew Lorber
// DSA II Project 4 - Together to the End (From the 1998 regional ACM Programming Contest)

// Problem: Define a merge of two strings to be any string formed from all the characters in both strings, 
//          interspersed, but in their original order. For example, for the strings chocolate and chips, 
//          cchocholaiptes is a merge, but chocochilatspe or bananasplit are not. This problem requires writing 
//          a program that can tell if a given string is a merge of two other given strings. For the purposes of 
//          this problem, the input strings will contain only lowercase alphabetic characters.

#include <iostream>
#include <fstream>
#include <cctype>

// 2-D array to map path of A & B in C
bool grid[1001][1001];

// Prints grid (for testing)
void printGrid(std::string &A, std::string &B) {
    for(int j = 0; j <= B.size(); j++) {
        for(int i = 0; i <= A.size(); i++) {
            std::cout << int(grid[j][i]) << " | ";
        }
        std::cout << "\n----------------------------------------\n";
    }
}

// Capitalizes the letters of A within C (Assumes A was found)
void capitalizeA(std::string &A, std::string &B, std::string &C) {
    int i = A.size(), j = B.size();
    int indC = C.size() - 1; // Index of current letter in C

    // Retraces path in grid, capitalize letters of A as they are found
    while(i > 0 || j > 0) {
        // Checks if letter in B
        if(j > 0 && grid[j-1][i]) {
            j--;
            indC--;
        } 
        // Else, letter in A
        else {
            C.at(indC) = toupper(C.at(indC));
            i--;
            indC--;
        }
    }
}

std::string solveMerge(std::string &A, std::string &B, std::string C) {
    // Checks that size of strings match
    if(A.size() + B.size() != C.size()) {
        return "*** NOT A MERGE ***";
    } 

    // Finds path through grid
    // For each square, checks if this is part of a valid "path" by checking that the current square 
    //      is the next letter being searched for & by checking against the corresponding value in C.
    for(int j = 0; j <= B.size(); j++) {
        for(int i = 0; i <= A.size(); i++) {
            // Sets start of path
            if(i == 0 && j == 0) {
                grid[j][i] = true;
            }
            // Checks letter in string A against corresponding letter in C
            //  and checks that the previous letter in string A was already
            //  found.
            else if(i > 0 && A.at(i - 1) == C.at(i + j - 1) && (i == 1 || grid[j][i-1])) {
                grid[j][i] = true;
            }
            // Checks against string B against corresponding letter in C
            //  and checks that the previous letter in string B was already
            //  found.
            else if(j > 0 && B.at(j - 1) == C.at(i + j - 1) && (j == 1 || grid[j-1][i])) {
                grid[j][i] = true;
            } 
            else {
                grid[j][i] = false;
            }
        }
    }
    
    // Checks if A & B were found in C
    if(grid[B.size()][A.size()]) {
        // Capitalize A within C
        capitalizeA(A,B,C);
        return C;
    } else {
        return "*** NOT A MERGE ***";
    }
}

int main(int argc, char* argv[]) {
    // Reads in & opens input file
    std::string file;
    std::ifstream infile;

    do {
        std::cout << "Please enter the input file.\n";
        std::cin >> file;
        infile.open(file);
    } while(!infile.is_open());

    // Reads in & opens output file
    std::ofstream outfile;

    do {
        std::cout << "Please enter the output file.\n";
        std::cin >> file;
        outfile.open(file);
    } while(!outfile.is_open());

    // Continuously gets groups of three lines and passes to solver function
    // Writes return value to output file
    std::string stringA, stringB, stringC;
    while(infile >> stringA >> stringB >> stringC) {
        outfile << solveMerge(stringA, stringB, stringC) << '\n';
    }

    // Closes files
    infile.close();
    outfile.close();

    return 0;
}