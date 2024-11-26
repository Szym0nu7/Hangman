#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<char> stringToCharArray(string txt) {
    vector<char> array;
    for (char letter : txt) {
        array.push_back(letter);
    }
    return array;
}

bool hasChar(vector<char> arr, char letter ){
    if (find(arr.begin(), arr.end(), tolower(letter)) != arr.end()
        || find(arr.begin(), arr.end(), toupper(letter)) != arr.end())
        return true;
    else return false;
}

class HangmanGame {
public:

    void Initialize() {
        //initializing letter data
        ifstream letterData("letterData.txt");
        string letter;
        if (letterData.is_open())
            while (getline(letterData, letter))
                letters_to_guess.push_back(letter[0]);
        else cout << "letterData.txt not found";
        letterData.close();
    };

    HangmanGame() {
        Initialize();
    };

    void printGame() {
        cout << endl;
        for (int i = 0; i < word_to_guess.size(); i++) {
            if (word_to_guess[i] != ' ' && !hasChar(guessed_letters,word_to_guess[i]))cout << "_";
            else cout << word_to_guess[i];
        }
        cout << endl;
    }

    void playerInput() {
        cout << endl;
        for (char letter : letters_to_guess) {
            if (hasChar(guessed_letters, letter))cout << "- ";
                else cout << letter << " ";
        }
        cout << endl;
        
        cout << "Choose letter or type in the answer: ";
        getline(cin,player_input);
    }

    bool checkPlayerInput() {
        
        if (player_input == word_to_guess) {
            //yay you win
            cout << endl << "You guessed the word";
            return true;
        }

        guessed_letters.push_back(player_input[0]);
        if (hasChar(stringToCharArray((word_to_guess)), player_input[0])) {
            cout << endl << "You guessed one letter";

            for (char letter : word_to_guess) {
                if (!hasChar(guessed_letters, letter) && letter != ' ')return false;
            }
            return true;
        }
        else {
            hangman_progress++;
            cout << endl << "You're guess was wrong";
        }
        return false;
    }

    void GameLoop() {
        printGame();
    //render rules and game
    //choose guessed word
        while (true) {
            playerInput();
            if(checkPlayerInput())break;
            //check answer
            printGame();
            
        }
    //end game
    };
private:
    int hangman_progress = 0;
    string word_to_guess = "Oto wisielec";
    string player_input;
    vector<char> guessed_letters;
    vector<char> letters_to_guess;
    vector<char> letters_to_print;
};

int main()
{
    HangmanGame game;
    game.GameLoop();
    
}

