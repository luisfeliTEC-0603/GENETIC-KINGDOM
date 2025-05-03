# Compiler
CC = g++

# Program name
TARGET = game

# Source file(s)
SRC = Sources/main.cpp Sources/Game/game.cpp Sources/Level/gameLevel.cpp Sources/Textures/gameTextures.cpp Sources/System/camera.cpp Sources/UIElements/TowerSelectionScreen/towerSelection.cpp Sources/Tower/archer.cpp Sources/Tower/whizard.cpp Sources/Tower/artillery.cpp Sources/Tower/tower.cpp Sources/Currency/currency.cpp Sources/Utilities/tools.cpp Sources/UIElements/TowerUpgradeScreen/TowerUpgradeScreen.cpp Sources/Enemies/gameEnemies.cpp

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
