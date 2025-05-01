import random

def newGrid(width, height):
    return [['#' for _ in range(width)] for _ in range(height)]

def generate_path(grid, start_x, start_y, goal_x, goal_y, path_width):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
    x, y = start_x, start_y

    # Randomly carve paths towards the goal
    while (x != goal_x or y != goal_y):

        # Randomize direction
        random.shuffle(directions)
        path = False
        
        for dx, dy in directions:
            # Carve a path in the direction of the selected move
            nx, ny = x + dx, y + dy
            
            # Ensure we're within bounds and not at a wall
            if 0 <= nx < len(grid[0]) and 0 <= ny < len(grid) and grid[ny][nx] == '#':
                # Carve path (expand width)
                for i in range(-path_width // 2, path_width // 2 + 1):
                    if 0 <= nx + i < len(grid[0]) and 0 <= ny + i < len(grid):
                        grid[ny + i][nx] = ' '
                        grid[ny][nx + i] = ' '
                # Move to next position
                x, y = nx, ny
                path = True
                break

        # Couldn't find a viable path
        if not path:
            break

    return grid

def add_goal(grid, goal_x, goal_y):
    grid[goal_y][goal_x] = 'G'

def save_grid_to_file(grid, filename):
    with open(filename, 'w') as f:
        for row in grid:
            f.write("".join(row) + "\n")

def main():

    # General Grid Parameters
    width = 208
    height = 96

    # Goal Parameters
    goal_width = int(width * 5 / 100)
    goal_height = int(height * 10 / 100)
    goal = [[' ' for _ in range(goal_width)] for _ in range(goal_height)]
    goal[goal_height // 2][goal_width // 2] = 'G'
    
    # Generate Grid
    grid = newGrid(width, height)

    # Generate paths
    grid = generate_path(grid, 0, random.randint(0, height-1), goal_x, goal_y)  # From West
    grid = generate_path(grid, width - 1, random.randint(0, height-1), goal_x, goal_y)  # From East
    grid = generate_path(grid, random.randint(0, width-1), 0, goal_x, goal_y)  # From North
    grid = generate_path(grid, random.randint(0, width-1), height - 1, goal_x, goal_y)  # From South

    # Add the goal 'G'
    add_goal(grid, goal_x, goal_y)

    # Save the grid to a file
    save_grid_to_file(grid, "map.txt")

if __name__ == "__main__":
    main()
