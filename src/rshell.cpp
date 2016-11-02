#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <string>
using namespace std;

void printUserInfo(){
    char* userName;
    userName = getlogin(); // Gets current user's username.
    if(userName == NULL){ // Checks if getlogin was successful.
        perror("Unable to retrieve current user name.");
        return;
    }
    char hostName[256]; // Initialize a char array with a size of HOST_NAME_MAX + 1 for hostName + null character.
    if(gethostname(hostName, 255) == -1){  // Sets hostName to current host name. Checks if gethostname was successful.
        perror("Unable to retrieve current host name.");
        return;
    }
    cout << userName << "@" << hostName << "$ ";
    return;
}

void parse(string userCommands){
    if(userCommands == "exit"){ // Exits if userCommands is exit
        exit(0);
    }
    char* c_userCommands = new char[userCommands.length() + 1]; // Creates a c string for strtok and sets it to userCommand
    strcpy(c_userCommands, userCommands.c_str()); 
    
    char* token = strtok(c_userCommands, " ");
    while(token != NULL){
        cout << token << endl;
        token = strtok(NULL, " ");
    }
    return;
}

int main(){
    while(true){
        printUserInfo();
        string userCommands;
        getline(cin, userCommands);
        parse(userCommands);
    }
    return 1;
}
