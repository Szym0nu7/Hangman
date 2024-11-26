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

        if (hangman_progress >= 8)cout << endl << "  ________";
        if (hangman_progress >= 7)cout << endl << "  |/     |";
        if (hangman_progress >= 6)cout << endl << "  |      |";
        if (hangman_progress >= 5)cout << endl << "  |      O";
        if (hangman_progress >= 4)cout << endl << "  |     /|\\";
        if (hangman_progress >= 3)cout << endl << "  |     / \\";
        if (hangman_progress >= 2)cout << endl << "_/|\\__________";
        if (hangman_progress >= 1)cout << endl << "|---|--------|";

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
        
        while (true){
            cout << endl << "Choose letter or type in the answer: ";
            getline(cin, player_input);
            if (player_input.size() > 1) {
                bool wrongInput = false;
                for (char letter : player_input) {
                    if (hasChar(letters_to_guess, player_input[0])) {
                        if (hasChar(guessed_letters, player_input[0])) {
                            cout << endl << "Contains already guesssed letters";
                            wrongInput = true;
                            break;
                        }
                    }
                    else {
                        cout << endl << "Contains letters not in letter base";
                        wrongInput = true;
                        break;
                    }
                }
            }
            if (hasChar(letters_to_guess, player_input[0]))
                if (!hasChar(guessed_letters, player_input[0]))break;
                else cout << endl << "Letter already guesssed";
            else cout << endl << "Letter not in letter base";
        }
    }

    bool checkPlayerInput() {
        
        if (player_input == word_to_guess) {
            //yay you win
            cout << endl << "You guessed the word";
            return true;
        }

        if (player_input.size() > 1)return false;

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
            if (hangman_progress == hangman_chances)return true;
            return false;
        }
        
    }

    
    void GameLoop() {
        printGame();
    //render rules and game
    //choose guessed word
        while (true) {
            playerInput();
            if(checkPlayerInput())break;
            printGame();
            
        }
    //end game
    };

private:
    int hangman_progress = 0;
    int hangman_chances = 8;
    string word_to_guess = "Oto wisielec";
    string player_input;
    vector<char> guessed_letters;
    vector<char> letters_to_guess;
};

int main()
{
    HangmanGame game;
    game.GameLoop();
    
}

