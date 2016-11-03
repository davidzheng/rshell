#include <iostream>
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

bool checkForFlag(char* rawCommand){ // Returns true if a flag is pressent in the token
    if(strchr(rawCommand, '-') != NULL){
        return true;
    }
    return false;
}

Base*  makeTree(deque<char*> fixedCommandList){
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
    /*cout << "DONE" << endl;
    for(int i = 0; i < commandsParsed.size(); ++i){
        commandsParsed.at(i)->printCommand();
        commandsParsed.at(i)->printFlags();
    }
    for(int i = 0; i < connectorsParsed.size(); ++i){
            cout << connectorsParsed.at(i) << endl;
    }*/

    
    if(!connectorsParsed.empty()){
        Command* leftBase = commandsParsed.front();
        commandsParsed.pop_front();
        Command* rightBase = commandsParsed.front();
        commandsParsed.pop_front();
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
            Base* newLeftBase = commandTree.back();
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
        if(strchr(currentToken, '#') != NULL){ // If a comment exists, ignore the reset of user input during parsing
            for(int i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
                cout << fixedCommandList.at(i) << endl;
            }
            return fixedCommandList;
        }       
        rawCommandList.pop_front();
        /*if(strchr(currentToken, ';') != NULL){ 
            string temp = currentToken;
            temp = temp.substr(0, temp.size() - 1);
            strcpy(currentToken, temp.c_str());
            char semicolonChar[] = ";";
            char* semicolonArray = semicolonChar;
            fixedCommandList.push_back(currentToken);
            fixedCommandList.push_back(semicolonArray);
        }
        else{
            fixedCommandList.push_back(currentToken);
        }*/
        fixedCommandList.push_back(currentToken);
    }
   /* cout << "Fixed CMD list" << endl;
    for(int i = 0; i < fixedCommandList.size(); ++i){ // For testing purposes
        cout << fixedCommandList.at(i) << endl;
    }*/
    return fixedCommandList;
}


int main(){
    while(true){
        printUserInfo();
        string userCommands;
        getline(cin, userCommands);
        deque<char*> temp = parse(userCommands);
        /*cout << "AFTER PARSE:" << endl;
        for(int i = 0; i < temp.size(); ++i){
                cout << temp.at(i) << endl;
        }*/
        Base* cmdTree = makeTree(temp);
        cmdTree->runCommand();
    }
    return 1;
}
