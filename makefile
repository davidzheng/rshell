CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic

all: Command Exit Connector Semicolon Or And Test	
	mkdir -p bin
	$(CC) $(CC_FLAGS) ./src/rshell.cpp Command.o Exit.o Connector.o semiColon.o OR.o AND.o TEST.o -o ./bin/rshell

rshell:
	$(CC) $(CC_FLAGS) -c ./src/rshell.cpp

Command:
	$(CC) $(CC_FLAGS) -c ./src/Command.cpp

Exit:
	$(CC) $(CC_FLAGS) -c ./src/Exit.cpp

Connector:
	$(CC) $(CC_FLAGS) -c ./src/Connector.cpp

Semicolon:
	$(CC) $(CC_FLAGS) -c ./src/semiColon.cpp

Or: 
	$(CC) $(CC_FLAGS) -c ./src/OR.cpp

And:
	$(CC) $(CC_FLAGS) -c ./src/AND.cpp
Test:
	$(CC) $(CC_FLAGS) -c ./src/TEST.cpp

clean:
	rm -f *.o
	rm -r bin

