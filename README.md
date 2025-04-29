# Genetic Kingdom - Tower Defense Game  
Course: CE-2103 – Project II

## Overview
Genetic Kingdom is a Tower Defense game developed in C++ for CE-2103. The game incorporates the RayLib library. It features the use of genetic algorithms to simulate the evolution of enemy behavior over successive waves and implements the A* pathfinding algorithm to enable enemies to navigate efficiently toward the player's keep. The game emphasizes strategic tower placement and adaptive gameplay in response to increasingly challenging enemy waves.

## How to Run
To compile and execute the project, navigate to the corresponding project directory and use the provided Makefile. Execute the following commands in the terminal:
```bash
make && make run
```
Once the application has completed its execution, the build artifacts can be removed with:
```bash
make clean
```

## Dependencies and Libraries
This project requires a C++ compiler (such as GCC), the Make utility, and Git for version control. On Debian-based systems, the necessary tools can be installed with the following command:
```bash
sudo apt update
sudo apt install build-essential git
```

### RayLib
The graphical interface is implemented using the RayLib library, which must also be installed and properly configured for the project to compile and run successfully. RayLib can be built from source. The official source code and build instructions can be found in the RayLib GitHub repository: https://github.com/raysan5/raylib .