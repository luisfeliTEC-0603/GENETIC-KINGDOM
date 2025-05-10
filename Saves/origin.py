"""
Map Generator Module
===================

Generates procedural 2D grid-based maps with:
- Random walk paths
- Rivers
- Central goal structure
- Multiple entry points

Usage example:
    python3 origin.py --width=208 --height=96 --paths=60 --rivers=15 --output=map.txt
"""

import random
from typing import List, Tuple
import argparse

# Constants
WALL = '#'
PATH = ' '
RIVER = '$'
GOAL = 'G'
DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0), 
              (1, 1), (-1, -1), (1, -1), (-1, 1)]
MAX_ATTEMPTS = 100

def create_blank_map(width: int, height: int) -> List[List[str]]:
    """Create a new map filled with walls.
    
    Args:
        width: Map width in cells
        height: Map height in cells
    
    Returns:
        2D grid filled with wall characters
    """
    return [[WALL for _ in range(width)] for _ in range(height)]

def carve_path(grid: List[List[str]], start: Tuple[int, int], 
               goal: Tuple[int, int], path_char: str, 
               can_overwrite: List[str] = None) -> bool:
    """Carve a path between two points using random walk.
    
    Args:
        grid: The map grid to modify
        start: (x, y) starting coordinates
        goal: (x, y) target coordinates
        path_char: Character to use for path
        can_overwrite: List of characters that can be overwritten
    
    Returns:
        True if path reached goal, False otherwise
    """
    if can_overwrite is None:
        can_overwrite = [WALL]
    
    x, y = start
    goal_x, goal_y = goal
    attempts = 0
    
    while (x != goal_x or y != goal_y) and attempts < MAX_ATTEMPTS:
        random.shuffle(DIRECTIONS)
        path_found = False
        path_width = random.randint(1, 2)
        
        for dx, dy in DIRECTIONS:
            nx, ny = x + dx, y + dy
            
            if (0 <= nx < len(grid[0]) and 0 <= ny < len(grid) and 
                grid[ny][nx] in can_overwrite):
                
                # Carve path with random width
                for i in range(-path_width // 2, path_width // 2 + 1):
                    if 0 <= nx + i < len(grid[0]):
                        grid[ny][nx + i] = path_char
                    if 0 <= ny + i < len(grid):
                        grid[ny + i][nx] = path_char
                
                x, y = nx, ny
                path_found = True
                break
        
        if not path_found:
            attempts += 1
    
    return x == goal_x and y == goal_y

def add_goal(grid: List[List[str]], goal_size: Tuple[int, int]) -> bool:
    """Add a goal structure to the center of the map.
    
    Args:
        grid: The map grid to modify
        goal_size: (width, height) of goal area
    
    Returns:
        True if goal was placed, False if map was too small
    """
    goal_width, goal_height = goal_size
    if len(grid[0]) < goal_width or len(grid) < goal_height:
        return False
    
    start_x = (len(grid[0]) - goal_width) // 2
    start_y = (len(grid) - goal_height) // 2
    
    for y in range(goal_height):
        for x in range(goal_width):
            if x == goal_width // 2 and y == goal_height // 2:
                grid[start_y + y][start_x + x] = GOAL
            else:
                grid[start_y + y][start_x + x] = PATH
    
    return True

def save_map(grid: List[List[str]], filename: str) -> None:
    """Save map to a text file.
    
    Args:
        grid: The map grid to save
        filename: Output file path
    """
    with open(filename, 'w') as f:
        for row in grid:
            f.write("".join(row) + "\n")

def create_spawn_points(grid: List[List[str]]) -> List[List[str]]:
    """Replace some perimeter walls with spawn points ('S').
    
    Args:
        grid: The map grid to modify
    
    Returns:
        The modified grid with spawn points added
    """
    height = len(grid)
    width = len(grid[0]) if height > 0 else 0
    
    # Top and bottom edges
    for x in range(width):
        if grid[0][x] == PATH:
            grid[0][x] = 'S'
        if grid[height-1][x] == PATH:
            grid[height-1][x] = 'S'
    
    # Left and right edges (skip corners already done above)
    for y in range(1, height-1):
        if grid[y][0] == PATH:
            grid[y][0] = 'S'
        if grid[y][width-1] == PATH:
            grid[y][width-1] = 'S'
    
    return grid

def generate_map(width: int = 100, height: int = 50, 
                num_paths: int = 35, num_rivers: int = 5) -> List[List[str]]:
    """Generate a complete map with paths, rivers and goal.
    
    Args:
        width: Map width in cells
        height: Map height in cells
        num_paths: Number of random paths to generate
        num_rivers: Number of random rivers to generate
    
    Returns:
        The generated map grid
    """
    grid = create_blank_map(width, height)
    center = (width // 2, height // 2)
    
    # Main paths from edges
    for start in [(width//2, 0), (0, height//2), 
                 (width-1, height//2), (width//2, height-1)]:
        carve_path(grid, start, center, PATH)
    
    # Random paths
    for _ in range(num_paths):
        start = (random.randint(0, width-1), random.randint(0, height-1))
        carve_path(grid, start, center, PATH)
    
    # Rivers (can overwrite paths)
    for _ in range(num_rivers):
        start = (random.randint(0, width-1), random.randint(0, height-1))
        carve_path(grid, start, center, RIVER, [WALL, PATH])
    
    # Add goal
    goal_size = (2, 2)
    add_goal(grid, goal_size)
    
    # Add spawn points 
    create_spawn_points(grid)
    
    return grid

def main():
    """Command line interface for map generation."""
    parser = argparse.ArgumentParser(description="Generate procedural 2D maps")
    parser.add_argument("--width", type=int, default=100, help="Map width")
    parser.add_argument("--height", type=int, default=50, help="Map height")
    parser.add_argument("--paths", type=int, default=35, help="Number of paths")
    parser.add_argument("--rivers", type=int, default=5, help="Number of rivers")
    parser.add_argument("--output", default="map.txt", help="Output filename")
    args = parser.parse_args()
    
    print(f"Generating {args.width}x{args.height} map...")
    map_grid = generate_map(args.width, args.height, args.paths, args.rivers)
    save_map(map_grid, args.output)
    print(f"Map saved to {args.output}")

if __name__ == "__main__":
    main()