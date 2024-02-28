#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
using namespace std;

// const string wordAnimal[8] = {"tiger", "sheep", "hourse", "crab", "panda", "spider", "mouse", "buterfly"};
const int MAX_BAD_GUESS = 7;

string init(){
    ifstream in("data.txt");
    vector<string> wordAnimal;
    string tmp;
    while(in >> tmp){
        wordAnimal.push_back(tmp);
    }
    return wordAnimal[rand()%wordAnimal.size()];
}

bool checkEndGame(const int& length, vector<bool> trueGuess){
    for(int i = 0; i < length; i++)        if(trueGuess[i] == 0)     return false;
    return true;
}

void render(const int& badGuessed, const int& length, const vector<bool> trueGuess, const string secretWord){
    string man[] = {"     _________", "    |", "    |", "    |", "    |", "    |", "____|____"};
    if(badGuessed >= 1)        man[2] = "    |        o";
    if(badGuessed == 2)        man[3] = "    |        |";
    else if(badGuessed == 3)   man[3] = "    |       /|";
    else if(badGuessed >= 4)   man[3] = "    |       /|\\";
    if(badGuessed == 5)        man[4] = "    |       /";
    else if(badGuessed >= 6)   man[4] = "    |       / \\";
    if(badGuessed == 7)        man[1] = "    |        |";
    
    for(int i = 0; i < 7; i++)      cout << man[i] << "\n";

    cout << "\n\nGuessed Word : ";
    for(int i = 0; i < length; i++)     cout << (trueGuess[i] ? secretWord[i] : '_');
    cout << "\n";
}

bool update(const string& secretWord, vector<bool>& trueGuessed, const char& typedChar){
    /*
        If typedChar in secret word ==> sign index in vector true guessed
        Else we ++bad Guessed
    */

    int leng = secretWord.size();
    bool atLeastOne = 0;
    for(int i = 0; i < leng; i++){
        if(secretWord[i] == typedChar)      trueGuessed[i] = 1, atLeastOne = 1;
    }
    return !atLeastOne;
}

void play(){
    string secretWord = init();
    int length = secretWord.size(), badGuessed = 0;
    bool gameOver;
    vector<bool> trueGuessed(length, 0);
    
    render(0, length, trueGuessed, secretWord);
    while(true){
        cout << "Type character : ";
        char typedChar;     cin >> typedChar;
        badGuessed += update(secretWord, trueGuessed, typedChar);

        gameOver = checkEndGame(length, trueGuessed);
        render(badGuessed, length, trueGuessed, secretWord);

        if(gameOver)       {  cout << "YOU WIN \n"; break; }
        if(badGuessed == 7){  cout << "YOU LOSS\n"; break; }
    }
}

int main(){
    srand(time(0));
    char opt;
    do{
        play();
        cout << "Do U want to play again (y/n)? : ";
        cin >> opt;
    }while(opt == 'y');
}