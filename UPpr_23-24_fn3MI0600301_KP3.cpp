/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Stivan Nikolaev Aleksandrov
* @idnumber 3MI0600301
* @compiler VC
*
* realisation of the game ,,Bricks Drop''
*
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
//that symbol will be to visualize the game field (it will form the border)
const char BorderSymbol = '@';
//the field x will be 10 + 2 at start, because we will include the border, that consists of 1 symbol on the left and 1 symbol on the right
constexpr int FieldX = 16 + 2;
// the same reason for field y, but now 1 symbol on top and 1 symbol down
constexpr int FieldY = 16 + 2;
constexpr size_t MAX_STRING_SIZE = 128;
constexpr int minimumSymbols = 5;
char username[MAX_STRING_SIZE];
char password[MAX_STRING_SIZE];
int score = 0;
int maxScore = 0;
int getRandomNumber(int intervalLen, int startPoint) {
    srand(time(NULL));
    int randomNumber = rand() % intervalLen + startPoint;
    return randomNumber;
}
void generateGameField(char field[][FieldX], char emptySymbol) {
    for (int i = 0;i < FieldX;i++) {
        field[0][i] = BorderSymbol;
    }
    for (int y = 1;y < FieldY-1;y++) {
        for (int x = 0;x < FieldX;x++) {
            if (x == 0 || x == FieldX - 1) {
                field[y][x] = BorderSymbol;
            }
            else {
                field[y][x] = emptySymbol;
            }
        }
    }
    for (int i = 0;i < FieldX;i++) {
        field[FieldY-1][i] = BorderSymbol;
    }
}
void printField(const char field[][FieldX]) {
    for (int y = 0;y < FieldY;y++) {
        for (int x = 0;x < FieldX;x++) {
            std::cout << field[y][x];
        }
        std::cout << std::endl;
    }
}
int StringLengthFunc(const char* str) {
    if (!str)return -1;
    int len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len;
}
void writeDataToFile(const char* username,const char* password, int score) {
    if (!username || !password) return;
    std::ofstream ofs("data.txt");
    if (!ofs.is_open()) {
        std::cout << "File could not be loaded!" << std::endl;
        std::cout << "You will play as guest (your score will not be counted towards any max scores)!";
        return;
    }
    ofs << score << "\n";
    ofs << username << "\n";
    ofs << password << "\n";
    ofs.clear();
    ofs.close();
}
int main()
{
    char field[FieldX][FieldY];
    std::cout << "Welcome to Bricks Drop!"<<std::endl;
    std::cout << "Enter the number of the command you want to execute: "<<std::endl;
    std::cout << "Currently available commands: " << std::endl;
    std::cout << "1: Create new profile" << std::endl;
    std::cout << "2: Log in to an existing profile" << std::endl;
    std::cout << "Your command: ";
    int command;
    do {
        std::cin >> command;
    } while (command < 1 || command>3);
    if (command == 1) {
        std::cout << "Enter Username: ";
        std::cin >> username;
        while (StringLengthFunc(username) < minimumSymbols) {
            std::cout << "Your username is too short, enter new one: ";
            std::cin >> username;
        }
        std::cout << "Enter Password: ";
        std::cin >> password;
        while (StringLengthFunc(password) < minimumSymbols) {
            std::cout << "Your password is too short, enter new one: ";
            std::cin >> password;
        }
        writeDataToFile(username, password, score);
    }
    else if (command == 2) {
        // currently under development, check out later for updates :)
    }
}


