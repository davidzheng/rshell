#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <string.h>
#include <deque>
#include <vector>
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

bool checkForConnector(char* rawCommand){
    vector<string>connectors;
    connectors.push_back("&&");
    connectors.push_back("||");
    connectors.push_back(";");
    for(unsigned int i = 0; i < 3; ++i){
        if(rawCommand == connectors.at(i)){
            return true;
        }
    }
    return false;
}

void makeTree(deque<char*> fixedCommandList);

deque<char*> parse(string userCommands){
    if(userCommands == "exit"){ // Exits if userCommands is exit
        exit(0);
    }
    char* c_userCommands = new char[userCommands.length() + 1]; // Creates a c string for strtok and sets it to userCommand
    strcpy(c_userCommands, userCommands.c_str()); 
    
    char* token = strtok(c_userCommands, " "); // Uses strtok to set all " " to \0
    deque<char*>rawCommandList; // Raw command list before handling
    while(token != NULL){ // populates the rawCommandList with tokens
        rawCommandList.push_back(token);
        token = strtok(NULL, " ");
    }
    /*for(int i = 0; i < rawCommandList.size(); ++i){ // For testing purposes
        cout << rawCommandList.at(i) << endl;
    }*/
    deque<char*>fixedCommandList; // Command list post handling
    while(!rawCommandList.empty()){
        //cout << rawCommandList.front() << endl;
        char* currentToken = rawCommandList.front();
        if(strchr(currentToken, '#') != NULL){
        for(int i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
        cout << fixedCommandList.at(i) << endl;
        }
            return fixedCommandList;
        }       
        rawCommandList.pop_front();
        if(strchr(currentToken, ';') != NULL){
            string temp = currentToken;
            temp = temp.substr(0, temp.size() - 1);
            strcpy(currentToken, temp.c_str());
            char semicolonChar[] = ";";
            fixedCommandList.push_back(currentToken);
            fixedCommandList.push_back(semicolonChar);
        }
        else{
            fixedCommandList.push_back(currentToken);
        }
    }
    //cout << "Fixed CMD list" << endl;
    for(int i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
        cout << fixedCommandList.at(i) << endl;
    }
    return fixedCommandList;
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
