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
//#include "Exit.h"

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
        if(!fixedCommandList.empty() && checkForConnector(fixedCommandList.front())){
            tempToken = fixedCommandList.front();
            fixedCommandList.pop_front();
            connectorsParsed.push_back(tempToken);
        }
    }
    for(int i = 0; i < commandsParsed.size(); ++i){
        commandsParsed.at(i)->printCommand();
    }
    cout << connectorsParsed.size() << endl;
    if(!connectorsParsed.empty()){
        for(int i = 0; i < commandsParsed.size(); ++i){
            commandsParsed.at(i)->printCommand();
        }
        Base* leftBase = commandsParsed.front();
        commandsParsed.pop_front();
        Base* rightBase = commandsParsed.front();
        commandsParsed.pop_front();
        rightBase->printCommand();
        char* tempConnector = connectorsParsed.front();
        connectorsParsed.pop_front();
        if(strstr(tempConnector, "&&") != NULL){
            AND* newAND = new AND(leftBase, rightBase);
            commandTree.push_back(newAND);
        }
        else if(strstr(tempConnector, "||") != NULL){
            OR* newOR = new OR(leftBase, rightBase);
            commandTree.push_back(newOR);
        }
        else{
            semiColon*  newSemicolon = new semiColon(leftBase, rightBase);
            commandTree.push_back(newSemicolon);
        }        
        while(!connectorsParsed.empty()){
            cout << "CONNECTER AND COMMAND" << endl;
        //    commandTree.front()->printCommand();
            Base* newLeftBase = commandTree.front();
            //newLeftBase->printCommand();
            commandTree.pop_front();
        //    commandsParsed.front()->printCommand();
            Base* newRightBase = commandsParsed.front();
            commandsParsed.pop_front();
            char* tmpConnector = connectorsParsed.front();
            connectorsParsed.pop_front();
            if(strstr(tmpConnector, "&&") != NULL){
                AND* newAND = new AND(newLeftBase, newRightBase);
                commandTree.push_back(newAND);
            }
            else if(strstr(tmpConnector, "||") != NULL){
                OR* newOR = new OR(newLeftBase, newRightBase);
                commandTree.push_back(newOR);
            }
            else{
                semiColon* newSemicolon = new semiColon(leftBase, rightBase);
                commandTree.push_back(newSemicolon);
            }
      //      commandTree.back()->printCommand();
        }
    }
    else{
        return commandsParsed.front();
    }
        
    if(commandsParsed.size() != 0){
        perror("invalid number of commands and connectors");
    }
    else{
        cout << "DONE TREE" << endl;
        cout << commandTree.size() << endl;
        //commandTree.back()->printCommand();
        return commandTree.back();
    }
    return NULL;    
}

deque<char*> parse(string userCommands){
    if(userCommands == "exit"){ // Exits if userCommands is exit
        exit(1);
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
            for(unsigned i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
                cout << fixedCommandList.at(i) << endl;
            }
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
    return 1;
}
