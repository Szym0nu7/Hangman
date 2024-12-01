#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

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

    if(file.is_open()){
    while (getline(file, line)) {
        number_of_lines++;
    }
    }else cout << fileName << " was not found or wasn't opened";
    file.close();
    return number_of_lines;
}

class HangmanGame {
public:

    string unifyString(string txt, bool noSpaces = false) {
        string result = "";
        for (char letter : txt) {
            if (hasChar(letters_to_guess, letter) || (letter == ' ' && !noSpaces))
                result += tolower(letter);
        }
        return result;
    }

    void Initialize() {

        system("cls");

        guessed_letters.clear();
        letters_to_guess.clear();
        hangman_progress = 0;
        hardMode = false;
       
        string output;

        //initializing letter data
        ifstream letterData("letterData.txt");
        
        if (letterData.is_open())
            while (getline(letterData, output))
                letters_to_guess.push_back(output[0]);
        else cout << "letterData.txt was not found or wasn't opened";
        letterData.close();


        cout
            << "Choose game mode: " << endl
            << "   1. Normal" << endl
            << "   2. Hard" << endl;

        string gameMode;
        while (true) {
            getline(cin, gameMode);

            if (gameMode == "1") gameMode = "normal";
            if (gameMode == "2") gameMode = "hard";

            gameMode = unifyString(gameMode, true);

            if (gameMode == "normal" || gameMode == "hard")break;
            cout << "Invalid input" << endl;
        }

        system("cls");

        cout << "Chosen game mode: " << gameMode << endl;

        if (gameMode == "hard")hardMode = true;


        //initialazition of guessed phrase
        string phraseFile = "phraseData.txt";
        if (hardMode)phraseFile = "phraseDataHardMode.txt";

        ifstream phraseData(phraseFile);
        

        if (phraseData.is_open()) { 
            srand(time(NULL));
            int randomPhrase = rand() % countLinesInFIle(phraseFile);

            for(int i = 0; i <= randomPhrase; i++)
                getline(phraseData, output);
        }else cout << phraseFile << " was not found or wasn't opened";
        phrase_to_guess = output;
               
        hangman_chances = 6;
        if (hardMode) {
            hangman_progress = 4;
            hangman_chances = 11;
        }

    };

    HangmanGame() {
        while (true) {
            Initialize();

            GameLoop();

            cout << endl
                << "Do you wish to play again?" << endl
                << "   1. Yes" << endl
                << "   2. No" << endl;

            string continueGame;
            while (true) {
                getline(cin, continueGame);

                if (continueGame == "1") continueGame = "yes";
                if (continueGame == "2") continueGame = "no";

                continueGame = unifyString(continueGame, true);

                if (continueGame == "yes" || continueGame == "no")break;
                cout << "Invalid input" << endl;
            }
            if (continueGame == "no")break;
        }
    };


    void printGame() {

        //dificulty
        ifstream lastWordsFile("lastWords.txt");
        string lastWords;
        switch (hangman_progress)
        {
        
        case 0:
            cout
                << endl << ""
                << endl << ""
                << endl << ""
                << endl << ""
                << endl << ""
                << endl << ""
                << endl << "______________"
                << endl << "|---|--------|-_";
            break;
        case 1:
            cout
                << endl << ""
                << endl << "  |"
                << endl << "  |"
                << endl << "  |"
                << endl << "  |"
                << endl << "  |"
                << endl << "_/|\\__________"
                << endl << "|---|--------|-_";
            break;
        case 2:
            cout
                << endl << "  ________"
                << endl << "  |/"
                << endl << "  |"
                << endl << "  |"
                << endl << "  |"
                << endl << "  |"
                << endl << "_/|\\__________"
                << endl << "|---|--------|-_";
            break;
        case 3:
            cout
                << endl << "  ________"
                << endl << "  |/     |"
                << endl << "  |      |"
                << endl << "  |     (_)"
                << endl << "  |"
                << endl << "  |"
                << endl << "_/|\\__________"
                << endl << "|---|--------|-_";
            break;
        case 4:
            cout
                << endl << "  ________"
                << endl << "  |/     |"
                << endl << "  |      |"
                << endl << "  |     (_)"
                << endl << "  |"
                << endl << "  |               O"
                << endl << "_/|\\__________   /|\\  "
                << endl << "|---|--------|-_ / \\  ";
            break;
        case 5:
            cout
                << endl << "  ________"
                << endl << "  |/     |"
                << endl << "  |      |"
                << endl << "  |     (_)"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "_/|\\____/ \\___"
                << endl << "|---|--------|-_";
            break;
        case 6:
            cout
                << endl << "  ________"
                << endl << "  |/     |"
                << endl << "  |      |"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;
        case 7:
            cout
                << endl << "  ________"
                << endl << "  |/     |  You're really bad at this, aren't you?"
                << endl << "  |      | /"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;
        case 8:
            cout
                << endl << "  ________"
                << endl << "  |/     |  My life is on the line here you know? Heh, quite literaly."
                << endl << "  |      | /"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;
        case 9:
            cout
                << endl << "  ________"
                << endl << "  |/     |  ..."
                << endl << "  |      | /"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;
        case 10:
            cout
                << endl << "  ________"
                << endl << "  |/     |  I guess it's time for my last words..."
                << endl << "  |      | /"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;
        case 11:
            
            if (lastWordsFile.is_open()) {
                srand(time(NULL));
                int randomWords = rand() % countLinesInFIle("lastWords.txt");

                for (int i = 0; i <= randomWords; i++)
                    getline(lastWordsFile, lastWords);
            }
            else cout << "lastWords.txt was not found or wasn't opened";
            
            cout
                << endl << "  ________"
                << endl << "  |/     |  " << lastWords
                << endl << "  |      | /"
                << endl << "  |      O"
                << endl << "  |     /|\\"
                << endl << "  |     / \\"
                << endl << "_/|\\__________"
                << endl << "|---|--------|";
            break;

        default:
            break;
        }
        lastWordsFile.close();

        //printing phrase to guess
        cout << endl << "Your phrase: ";
        for (int i = 0; i < phrase_to_guess.size(); i++) {
            if (hasChar(letters_to_guess,phrase_to_guess[i]) && !hasChar(guessed_letters, phrase_to_guess[i]))cout << "_";
            else cout << phrase_to_guess[i];
        }
        cout << endl;
    }

    void playerInput() {
        
        //printing letterData
        cout << endl << "Letters left" << endl;
        for (int i = 0; i < letters_to_guess.size(); i++) {
            cout << "--";
        }
        cout << endl;
        for (char letter : letters_to_guess) {
            if (hasChar(guessed_letters, letter))cout << "- ";
                else cout << letter << " ";
        }
        cout << endl;
        for (int i = 0; i < letters_to_guess.size(); i++) {
            cout << "--";
        }
        cout << endl;
        
        //player input
        while (true){
            cout << endl << "Choose letter or type in the answer: ";
            getline(cin, player_input);

            //phrase validation
            if (player_input.size() > 1) {
                bool wrongInput = false;
                for (char letter : player_input) {

                    if (hasChar(letters_to_guess, letter) 
                        || hasChar(stringToCharArray(phrase_to_guess), letter)) { // this is so interpunction can be used in an answer
                        if (hasChar(guessed_letters, letter) && !hasChar(stringToCharArray(phrase_to_guess),letter)) {
                            cout << "Contains already guesssed letters" << endl;
                            wrongInput = true;
                            break;
                        }
                    }
                    else {
                        cout << "Contains letters not in letter base" << endl;
                        wrongInput = true;
                        break;
                    }
                }
                
                if (!wrongInput)break;
                else continue;
            }
            
            //single letter validation
            if (hasChar(letters_to_guess, player_input[0]))
                if (!hasChar(guessed_letters, player_input[0]))break;
                else cout << "Letter already guesssed" << endl;
            else cout << "Letter not in letter base" << endl;
        }
    }

    bool checkPlayerInput() {
        
        system("cls");

        string unifiedInput = unifyString(player_input);
        string unifiedPhrase = unifyString(phrase_to_guess);

        if (unifiedInput == unifiedPhrase) {
            
            //yay you win

            cout << "You have won" << endl;
            return true;
        }

        if (player_input.size() == 1) {
            guessed_letters.push_back(player_input[0]);

            if (hasChar(stringToCharArray((phrase_to_guess)), player_input[0])) {
                cout << "You guessed one letter" << endl;

                for (char letter : phrase_to_guess) {
                    if (!hasChar(guessed_letters, letter) && hasChar(letters_to_guess,letter))return false;
                }
                cout << "You have won" << endl;
                return true;
            }
        }

        hangman_progress++;
        if (hangman_progress == hangman_chances) {
            cout << "You have lost" << endl;
            return true;
        }else cout << "You're guess was wrong" << endl;
        return false;

    }

    
    void GameLoop() {
        printGame();
    //render rules and game
    //choose guessed word
        while (true) {
            playerInput();
            if (checkPlayerInput())break;
            printGame();
        }
        cout << endl << "The phrase: " << phrase_to_guess;
        printGame();
    };

private:
    int hangman_progress = 0;
    bool hardMode = false;
    int hangman_chances = 6;
    string phrase_to_guess;
    string player_input;
    vector<char> guessed_letters;
    vector<char> letters_to_guess;
};

int main()
{

        HangmanGame game;
    
}

