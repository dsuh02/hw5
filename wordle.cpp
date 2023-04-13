#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string in, const string& floating, 
    const set<string>& dict, set<string>& results, 
    unsigned int index); 

bool validWord(string in, const string& floating);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    std::string incopy = in;
    std::string fcopy = floating;
    wordleHelper(incopy, fcopy, dict, results, 0);
    return results;
}

// Define any helper functions here
// recursed function in wordle function
void wordleHelper(string in, const string& floating, const set<string>& dict, set<string>& results, unsigned int index)
{
    //1st case word is not valid
    if(!validWord(in,floating)){
        return;
    }
    //if index is at the last position
    if(index==in.length()){
        if(dict.find(in) != dict.end() && validWord(in, floating)){
            results.insert(in);
        }
        return;
    }
    // if the next position is a blank
    if(in[index]=='-'){
        for(char c='a'; c <= 'z'; c++){ //travel through alphabet ASCII
            in[index]=c;
            //recurse for every possible letter for the next position
            wordleHelper(in, floating, dict, results, index+1);
        }
    }
    //else recurse with next position
    else{
        wordleHelper(in, floating, dict, results, index+1);
    }
}

//returns true if there are NO MORE floating positions
//false if floating var has a '-' position
bool validWord(string in, const string& floating)
{
    if(floating == "")
        return true;
    for(unsigned int i=0; i<floating.length(); i++)
    { 
        if(in.find(floating[i]) == string::npos && in.find('-')==string::npos){
            return false;
        }
        else{
            if(in.find(floating[i]) != std::string::npos){
                in.erase(in.find(floating[i]), 1);
            }
            else{
                in.erase(in.find('-'), 1);
            }
        }
    }
    return true;
}