#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

//Printing a message
void printMessage(string message, bool printTop=true, bool printBottom=true)
{
    if(printTop)
    {
        cout<<"+---------------------------------+"<<endl;
        cout<<"|";
    }
    else
    {
        cout<<"|";
    }
    bool front=true;
    for(int i=message.length();i<33;i++)
    {
        if(front)
            message=" " + message;
        else
            message=message + " ";

        front=!front;
    }
    cout<<message.c_str();

    if(printBottom)
    {
        cout<<"|"<<endl;
        cout<<"+---------------------------------+"<<endl;
    }
    else
    {
        cout<<"|"<<endl;
    }


}
//Drawing the hangman
void Draw(int guess=0)
{
    //Drawing the shapes
    if(guess>=1)
        printMessage("|",false,false);
    else
        printMessage("",false,false);

    if(guess>=2)
        printMessage("|",false,false);
    else
        printMessage("",false,false);

    if(guess>=3)
        printMessage("O",false,false);
    else
        printMessage("",false,false);

    if(guess==4)
        printMessage("/  ",false,false);

    if(guess==5)
        printMessage("/| ",false,false);

    if(guess>=6)
        printMessage("/|\\",false,false);
    else
        printMessage("",false,false);

    if(guess>=7)
        printMessage("|",false,false);
    else
        printMessage("",false,false);

    if(guess==8)
        printMessage("/",false,false);

    if(guess>=9)
        printMessage("/ \\",false,false);
    else
        printMessage("",false,false);
}
//Printing the letters
void printLetters(string input,char from,char to)
{
    //Finding the letters
    string str;
    for(char i=from;i<=to;i++)
    {
        if(input.find(i)==string::npos)
        {
            str=str+i;
            str=str+" ";
        }
        else
            str=str+"  ";
    }
    printMessage(str,false,false);

}
//Printing the available letters
void availableLetters(string letter)
{
    printMessage("Available letters");
    printLetters(letter,'A','F');
    printLetters(letter,'G','L');
    printLetters(letter,'M','R');
    printLetters(letter,'S','X');
    printLetters(letter,'Y','Z');
}

bool printWord_checkWin(string word, string guessed)
{
    bool won=true;
    string c;
    for(int i=0;i<word.length();i++)
    {
        if(guessed.find(word[i])== string::npos) //"find" will return npos if it doesn't find the current character in the for loop.
        {
            won=false;
            c+="_ "; //placeholder for the letter, so the player can't see the current letter of the word.

        }
        else
        {
            c+=word[i];
            c+=" ";
        }
    }
    printMessage(c,false);
    return won;

}
//Generating the random word
string randomWord(string path)
{
    int lineCount=0;
    string word;
    vector<string>v;
    ifstream reader(path.c_str());
    if(reader.is_open())
    {
        while(std::getline(reader, word))
        v.push_back(word);

        int randomLine= rand() % v.size();

        word=v.at(randomLine);
        reader.close();

    }
    return word;

}

int triesLeft(string word, string guessed)
{
    int error=0;
    for(int i=0; i<guessed.length();i++)
    {
        if(word.find(guessed[i])==string::npos)
            error++;
    }
    return error;
}


int main()
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess=randomWord("Words.txt");
    int tries=0;
    bool win=false;
    do{
        system("cls");
        printMessage("HANGMAN");
        Draw(tries);
        availableLetters(guesses);
        printMessage("Guess the word");
        win=printWord_checkWin(wordToGuess,guesses);

        if(win)
            break;

        char d;
        cout<<">";
        cin>>d;

        if(guesses.find(d)==string::npos)
            guesses=guesses+d;

        tries=triesLeft(wordToGuess,guesses);


      }while(tries<10);

      if(win)
        printMessage("YOU WON");
      else
        printMessage("GAME OVER");




    return 0;
}
