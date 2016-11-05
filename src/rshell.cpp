#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <string.h>
#include <deque>
#include <vector>
#include "Base.h"
#include "Command.h"
#include "Connector.h"
#include "AND.h"
#include "OR.h"
#include "semiColon.h"
#include "Exit.h"

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

bool checkForConnector(char* rawCommand){ // Populates and vector with connector strings and compares it to the input
    vector<string>connectors;
    connectors.push_back("&&");
    connectors.push_back("||");
    for(unsigned int i = 0; i < 2; ++i){ // Returns true if a connector string is present in input
        if(rawCommand == connectors.at(i)){
            return true;
        }
    }
    return false;
}

bool checkForSemi(char* rawCommand){
    if(strchr(rawCommand, ';') != NULL){
        return true;
    }
    return false;
}

Base* makeTree(deque<char*> fixedCommandList){
    deque<Command*> commandsParsed;
    deque<char*> connectorsParsed;
    deque<Connector* > commandTree;
    while(!fixedCommandList.empty()){
        bool commandWithSemi = false; 
        char* tempToken = fixedCommandList.front();
        fixedCommandList.pop_front();
        if(checkForSemi(tempToken)){
            string tempStr = string(tempToken);
            tempStr = tempStr.substr(0, tempStr.size() - 1);
            strcpy(tempToken, tempStr.c_str());
            string colonChar = ";";
            char* c_colonChar = new char[2];
            strcpy(c_colonChar, colonChar.c_str());
            connectorsParsed.push_back(c_colonChar);
            commandWithSemi = true;
        }
        if(strcmp(tempToken, "exit") == 0){
            Exit* newExit = new Exit();
            commandsParsed.push_back(newExit);
        }
        else{        
            Command* newCommand = new Command(tempToken); 
            while(!fixedCommandList.empty() && !checkForConnector(fixedCommandList.front())){
                if(commandWithSemi){
                    break;
                }
                tempToken = fixedCommandList.front();
                if(checkForSemi(tempToken)){
                    string tempStr = string(tempToken);
                    tempStr = tempStr.substr(0, tempStr.size() - 1);
                    strcpy(tempToken, tempStr.c_str());
                    newCommand->addFlag(fixedCommandList.front());
                    fixedCommandList.pop_front();
                    string colonChar = ";";
                    char* c_colonChar = new char[2];
                    strcpy(c_colonChar, colonChar.c_str());
                    connectorsParsed.push_back(c_colonChar);
                    break;
                }
                newCommand->addFlag(fixedCommandList.front());
                fixedCommandList.pop_front();   
            }
            commandsParsed.push_back(newCommand); 
        }
        if(!fixedCommandList.empty() && checkForConnector(fixedCommandList.front())){
            tempToken = fixedCommandList.front();
            fixedCommandList.pop_front();
            connectorsParsed.push_back(tempToken);
        }
    }    
    if(connectorsParsed.size() > 0){
        Base* leftBase = commandsParsed.at(0);
        commandsParsed.pop_front();
        Base* rightBase = commandsParsed.at(0);
        commandsParsed.pop_front();
        char* connectorChar = connectorsParsed.at(0);
        connectorsParsed.pop_front();
        if(strchr(connectorChar, ';') != NULL){
            semiColon* newSemicolon = new semiColon(leftBase, rightBase); 
            commandTree.push_back(newSemicolon);
        }
        else if(strstr(connectorChar, "&&") != NULL){
            AND* newAnd = new AND(leftBase, rightBase);
            commandTree.push_back(newAnd);
        }
        else if(strstr(connectorChar, "||") != NULL){
            OR* newOr = new OR(leftBase, rightBase);
            commandTree.push_back(newOr);
        } 
        while(!connectorsParsed.empty() && !commandsParsed.empty()){
            Base* rBase = commandsParsed.front();
            commandsParsed.pop_front();
            Base* lBase = commandTree.at(0);
            commandTree.pop_front();
            char* connectChar = connectorsParsed.at(0);
            connectorsParsed.pop_front();
            if(strchr(connectChar, ';') != NULL){ 
                semiColon* newSemiColon = new semiColon(lBase, rBase); 
                commandTree.push_back(newSemiColon);
            }
            else if(strstr(connectChar, "&&") != NULL){ 
                AND* newAND = new AND(lBase, rBase);
                commandTree.push_back(newAND);
            }
            else if(strstr(connectChar, "||") != NULL){ 
                OR* newOR = new OR(lBase, rBase);
                commandTree.push_back(newOR);
            }
        }
    }
    else{
        return commandsParsed.front();
    }   
    if(commandsParsed.size() != 0){
        perror("invalid number of commands and connectors");
    }
    else{
        return commandTree.back();
    }
    return NULL;    
}

deque<char*> parse(string userCommands){
    if(userCommands == "exit"){ // Exits if userCommands is exit
        Exit* newExit = new Exit();
        newExit->runCommand();
    }
    char* c_userCommands = new char[userCommands.length() + 1]; // Creates a c string for strtok and sets it to userCommand
    strcpy(c_userCommands, userCommands.c_str()); 
    
    char* token = strtok(c_userCommands, " "); // Uses strtok to set all " " to \0
    deque<char*>rawCommandList; // Raw command list before handling
    while(token != NULL){ // populates the rawCommandList with tokens
        rawCommandList.push_back(token);
        token = strtok(NULL, " ");
    }
    deque<char*>fixedCommandList; // Command list comment handling
    while(!rawCommandList.empty()){
        char* currentToken = rawCommandList.front();
        if(strchr(currentToken, '#') != NULL){ // If a comment exists, ignore the reset of user input during parsing
            /*for(unsigned i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
                cout << fixedCommandList.at(i) << endl;
            }*/
            return fixedCommandList;
        }       
        rawCommandList.pop_front();
        fixedCommandList.push_back(currentToken);
    }
    return fixedCommandList;
}


int main(){
    while(true){
        printUserInfo();
        string userCommands;
        getline(cin, userCommands);
        deque<char*> temp = parse(userCommands);
        Base* cmdTree = makeTree(temp);
        cmdTree->runCommand();
    }  
    return 0;
}

