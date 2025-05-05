# Basic Settings
CXX := g++
TARGET := game
CXXFLAGS := -Wall -std=c++17
LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source Groups
GAME_SRCS := Sources/Game/game.cpp Sources/Game/Pathfinding/aStar.cpp
LEVEL_SRCS := Sources/Level/gameLevel.cpp
TEXTURE_SRCS := Sources/Textures/gameTextures.cpp
SYSTEM_SRCS := Sources/System/camera.cpp
UI_SRCS := Sources/UIElements/TowerSelectionScreen/towerSelection.cpp \
            Sources/UIElements/TowerUpgradeScreen/TowerUpgradeScreen.cpp
TOWER_SRCS := Sources/Tower/archer.cpp Sources/Tower/wizard.cpp \
              Sources/Tower/artillery.cpp Sources/Tower/tower.cpp
CURRENCY_SRCS := Sources/Currency/currency.cpp
UTILS_SRCS := Sources/Utilities/tools.cpp
ENEMY_SRCS := Sources/Enemies/gameEnemies.cpp
INFO_DISPL := Sources/UIElements/InformationScreen/InformationScreen.cpp

# Combine sources
ALL_SRCS := Sources/main.cpp \
            $(GAME_SRCS) \
            $(LEVEL_SRCS) \
            $(TEXTURE_SRCS) \
            $(SYSTEM_SRCS) \
            $(UI_SRCS) \
            $(TOWER_SRCS) \
            $(CURRENCY_SRCS) \
            $(UTILS_SRCS) \
            $(ENEMY_SRCS) \
            $(INFO_DISPL)

# Build Rules
all: $(TARGET)

$(TARGET): $(ALL_SRCS)
	@echo "Building game..."
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)
	@echo "Build complete!"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

# Help message
help:
	@echo "Simple Game Makefile"
	@echo "Commands:"
	@echo "  make       - Build the game"
	@echo "  make run   - Build and run the game"
	@echo "  make clean - Remove the executable"
	@echo "  make help  - Show this message"