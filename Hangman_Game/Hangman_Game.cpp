#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool hasChar(string txt, char letter) {
    if (txt.find(letter) < txt.size() && txt.find(letter) >= 0)
        return true;
    else
        return false;
}

class HangmanGame {
public:
    HangmanGame() {};

    void printGame() {
        cout << endl;
        for (int i = 0; i < word_to_guess.size(); i++) {
            if (word_to_guess[i] != ' ')cout << "_";
            else cout << word_to_guess[i];
        }
        cout << endl;
    }

    void playerInput() {
        //print accessible letters
        cout << "Choose letter or type in the answer: ";
        getline(cin,player_input);
    }

    void checkPlayerInput() {
        if (player_input == word_to_guess) {
            //yay you win
            cout << endl << "You guessed the word";
        }
        if (hasChar(word_to_guess,player_input[0])) {
            //trigger letter
            cout << endl << "You one letter";
        }
        else {
            //progress the hanging proccess by one
        }
    }

    void GameLoop() {
        printGame();
    //render rules and game
    //choose guessed word
        while (true) {
            playerInput();
            checkPlayerInput();
            //check answer
            printGame();
            
        }
    //end game
    };
private:
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

