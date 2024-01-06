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
//the field x will be 10 + 2 at start, because we will include the border, that consists of 1 symbol on the left and 1 symbol on the right + '\0' at the end of every row
constexpr int FieldX = 16 + 3;
// the same reason for field y, but now 1 symbol on top and 1 symbol down
constexpr int FieldY = 16 + 2;
constexpr size_t MAX_STRING_SIZE = 128;
constexpr int minimumSymbols = 5;
char username[MAX_STRING_SIZE];
char password[MAX_STRING_SIZE];
int score = 0;
int maxScore = 0;
int getRandomNumber(int intervalLen, int startPoint) {
    int randomNumber = rand() % intervalLen + startPoint;
    return randomNumber;
}
int convertCharToInt(char symbol) {
    return symbol - '0';
}
void generateGameField(char field[][FieldX], char emptySymbol) {
    for (int i = 0;i < FieldX-1;i++) {
        field[0][i] = BorderSymbol;
    }
    for (int y = 1;y < FieldY-1;y++) {
        for (int x = 0;x < FieldX-1;x++) {
            if (x == 0 || x == FieldX - 2) {
                field[y][x] = BorderSymbol;
            }
            else {
                field[y][x] = emptySymbol;
            }
        }
    }
    for (int i = 0;i < FieldX-1;i++) {
        field[FieldY-1][i] = BorderSymbol;
    }
    for (int j = 0;j < FieldY - 1;j++) {
        field[j][FieldX - 1] = '\0';
    }
}
void printField(const char field[][FieldX]) {
    for (int y = 0;y < FieldY;y++) {
        for (int x = 0;x < FieldX-1;x++) {
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
int convertToInt(const char* str) {
    if (!str)return -1;
    int result = 0;
    while (*str) {
        (result *= 10) += convertCharToInt(*str);
        str++;
    }
    return result;
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
bool compareStrings(const char* str1, const char* str2) {
    if (!str1 || !str2)return false;
    while (*str1 && *str2) {
        if ((*str1) != (*str2))return false;
        str1++;
        str2++;
    }
    return (*str1) == (*str2);
}
// no need to type username and password as parameters of the function because they are globally declared
void loginToAccount() {
    if (!username || !password) return;
    std::ifstream ifs("data.txt");
    if (!ifs.is_open()) {
        std::cout << "Unexpected Error! You will play as guest!";
    }
    char previousMaxScore[MAX_STRING_SIZE];
    char previousUsername[MAX_STRING_SIZE];
    char previousPassword[MAX_STRING_SIZE];
    ifs.getline(previousMaxScore, MAX_STRING_SIZE);
    ifs.getline(previousUsername, MAX_STRING_SIZE);
    ifs.getline(previousPassword, MAX_STRING_SIZE);
    maxScore = convertToInt(previousMaxScore);
    while (!compareStrings(username, previousUsername) || !compareStrings(password, previousPassword)) {
        std::cout << "Username or Password is invalid! Enter new ones: \n";
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
    }
    ifs.clear();
    ifs.close();
}
// no need to type username and password as parameters of the function because they are globally declared
void enterAccountInfo() {
    if (!username || !password)return;
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
}
int main()
{
    char field[FieldY][FieldX];
    generateGameField(field, ' ');
    srand(time(NULL));
    std::cout << "Welcome to Bricks Drop!"<<std::endl;
    std::cout << "Enter the number of the command you want to execute: "<<std::endl;
    std::cout << "Currently available commands: " << std::endl;
    std::cout << "1: Create new profile" << std::endl;
    std::cout << "2: Log in to an existing profile" << std::endl;
    std::cout << "Your command: ";
    int command;
    do {
        std::cin >> command;
    } while (command < 1 || command > 2);
    switch (command) {
    case 1: 
        enterAccountInfo();
        writeDataToFile(username, password, score);

        break;
    case 2:
        enterAccountInfo();
        loginToAccount();

        break;
    default: std::cout << "ERROR!";break;
    }
}


