import random

def newMap(width, height):
    return [['#' for _ in range(width)] for _ in range(height)]

def newPath(grid, start_x, start_y, goal_x, goal_y, char):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
    x, y = start_x, start_y

    attempt = 0
    attempt_max = 100

    # Randomly carve paths towards the goal
    while (x != goal_x or y != goal_y) and (attempt < attempt_max):
        random.shuffle(directions)
        path = False
        path_width = random.randint(1, 2)
        
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            # Ensure limits
            if 0 <= nx < len(grid[0]) and 0 <= ny < len(grid) and grid[ny][nx] == '#':
                # Carve path (expand width)
                for i in range(-path_width // 2, path_width // 2 + 1):
                    if 0 <= nx + i < len(grid[0]) and 0 <= ny + i < len(grid):
                        grid[ny + i][nx] = char
                        grid[ny][nx + i] = char

                # Move to next position
                x, y = nx, ny
                path = True
                break
        
        if not path:
            attempt +=1
    
    return grid

def newRiver(grid, start_x, start_y, goal_x, goal_y, char):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]
    x, y = start_x, start_y

    attempt = 0
    attempt_max = 100

    # Randomly carve paths towards the goal
    while (x != goal_x or y != goal_y) and (attempt < attempt_max):
        random.shuffle(directions)
        path = False
        path_width = random.randint(1, 2)
        
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            
            # Ensure limits
            if 0 <= nx < len(grid[0]) and 0 <= ny < len(grid) and (grid[ny][nx] == '#' or grid[ny][nx] == ' '):
                # Carve path (expand width)
                for i in range(-path_width // 2, path_width // 2 + 1):
                    if 0 <= nx + i < len(grid[0]) and 0 <= ny + i < len(grid):
                        grid[ny + i][nx] = char
                        grid[ny][nx + i] = char

                # Move to next position
                x, y = nx, ny
                path = True
                break
        
        if not path:
            attempt +=1
    
    return grid

def AddGoal(grid, goal):

    # Check Acceptable Dimensions between Matrixes 
    if len(grid) < len(goal) or len(grid[0]) < len(goal[0]):
        return
    
    # Coordinates to Redraw the Grid
    start_y = (len(grid) - len(goal)) // 2
    start_x = (len(grid[0]) - len(goal)) // 2

    # Redrawing
    for y in range(len(goal)):
        for x in range(len(goal[0])):
            grid[start_y + y][start_x + x] = goal[y][x] 

def SaveFIle(grid, filename):
    with open(filename, 'w') as f:
        for row in grid:
            f.write("".join(row) + "\n")

def main():

    # General Grid Parameters
    width = 100
    height = 50
    goal_x = width // 2
    goal_y = height // 2
    numPaths = 35
    numRiver = 5

    # Goal Parameters
    goal_width = int(width * 10 / 100) + 1
    goal_height = int(height * 10 / 100)
    goal = [[' ' for _ in range(goal_width)] for _ in range(goal_height)]
    goal[goal_height // 2][goal_width // 2] = 'G'
    
    # Generate Grid
    grid = newMap(width, height)

    # Generate paths
    grid = newPath(grid, width // 2, 0, goal_x, goal_y, ' ')  # From West
    grid = newPath(grid, 0, height // 2, goal_x, goal_y, ' ')  # From East
    grid = newPath(grid, width - 1, height // 2, goal_x, goal_y, ' ')  # From North
    grid = newPath(grid, width // 2, height - 1, goal_x, goal_y, ' ')  # From South

    for _ in range(numPaths):
        grid = newPath(grid, random.randint(0, width-1), random.randint(0, height-1), goal_x, goal_y, ' ')

    # Add Body of Water
    grid = newRiver(grid, width // 2, 0, goal_x, goal_y, '$')  # From West
    grid = newRiver(grid, 0, height // 2, goal_x, goal_y, '$')  # From East
    grid = newRiver(grid, width - 1, height // 2, goal_x, goal_y, '$')  # From North
    grid = newRiver(grid, width // 2, height - 1, goal_x, goal_y, '$')  # From South

    # Add the Goal -exclusively in the middle-
    AddGoal(grid, goal)

    # Save the grid to a file
    SaveFIle(grid, "map.txt")

if __name__ == "__main__":
    main()
