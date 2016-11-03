CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=rshell.o Command.o Connector.o AND.o OR.o semiColon.o

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)

