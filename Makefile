# Compiler
CC = g++

# Program name
TARGET = game

# Source file(s)
SRC = Sources/main.cpp Sources/Game/game.cpp Sources/Level/gameLevel.cpp 

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Build rules
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
