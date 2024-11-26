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

int countLinesInFIle(string fileName) {
    ifstream file(fileName);
    string line;
    int number_of_lines = 0;
    while (getline(file, line)) {
        number_of_lines++;
    }
    file.close();
    return number_of_lines;
}

class HangmanGame {
public:

    void Initialize() {
        string output;

        //initializing letter data
        ifstream letterData("letterData.txt");

        if (letterData.is_open())
            while (getline(letterData, output))
                letters_to_guess.push_back(output[0]);
        else cout << "letterData.txt was not found or wasn't opened";
        letterData.close();

        //initialazition of guessed phrase
        ifstream phraseData("phraseData.txt");
        srand(time(NULL));
        int randomPhrase = rand() % countLinesInFIle("phraseData.txt");

        if (phraseData.is_open()) { 
            for(int i = 0; i <= randomPhrase; i++)
                getline(phraseData, output);
        }else cout << "phraseData.txt was not found or wasn't opened";
        phrase_to_guess = output;
        cout << "phrase: " << output;
            
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
        for (int i = 0; i < phrase_to_guess.size(); i++) {
            if (hasChar(letters_to_guess,phrase_to_guess[i]) && !hasChar(guessed_letters, phrase_to_guess[i]))cout << "_";
            else cout << phrase_to_guess[i];
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

                    if (hasChar(letters_to_guess, letter) 
                        || hasChar(stringToCharArray(phrase_to_guess), letter)) { // this is so interpunction can be used in an answer
                        if (hasChar(guessed_letters, letter)) {
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
                
                if (!wrongInput)break;
                else continue;
            }
            
            

            if (hasChar(letters_to_guess, player_input[0]))
                if (!hasChar(guessed_letters, player_input[0]))break;
                else cout << endl << "Letter already guesssed";
            else cout << endl << "Letter not in letter base";
        }
    }

    string unifyString(string txt) {
        string result = "";
        for (char letter : txt) {
            if (hasChar(letters_to_guess, letter) || letter == ' ')
                result += tolower(letter);
        }
        return result;
    }

    bool checkPlayerInput() {
        
        string lowerInput = unifyString(player_input);
        string lowerPhrase = unifyString(phrase_to_guess);

        if (player_input == phrase_to_guess) {
            
            //yay you win
            cout << endl << "You guessed the phrase";
            return true;
        }

        if (player_input.size() == 1) {
            guessed_letters.push_back(player_input[0]);

            if (hasChar(stringToCharArray((phrase_to_guess)), player_input[0])) {
                cout << endl << "You guessed one letter";

                for (char letter : phrase_to_guess) {
                    if (!hasChar(guessed_letters, letter) && letter != ' ')return false;
                }
                return true;
            }
        }

        hangman_progress++;
        cout << endl << "You're guess was wrong";
        if (hangman_progress == hangman_chances)return true;
        return false;

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
    string phrase_to_guess;
    string player_input;
    vector<char> guessed_letters;
    vector<char> letters_to_guess;
};

int main()
{
    HangmanGame game;
    game.GameLoop();
    
}

