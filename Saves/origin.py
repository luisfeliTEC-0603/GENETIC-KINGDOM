import random

def generar_map():
    ancho = 208
    alto = 96
    mapa = [[' ' for _ in range(ancho)] for _ in range(alto)]
    
    # Bordes
    for x in range(ancho):
        mapa[0][x] = '#'
        mapa[alto-1][x] = '#'
    for y in range(alto):
        mapa[y][0] = '#'
        mapa[y][ancho-1] = '#'
    
    # Patrón de laberinto principal
    for y in range(2, alto-2, 6):
        for x in range(2, ancho-2, 12):
            # Paredes verticales con huecos
            if random.random() > 0.3:  # 70% probabilidad de pared
                longitud = random.randint(2, 5)
                for dy in range(longitud):
                    if y+dy < alto-2:
                        mapa[y+dy][x] = '#'
            
            # Paredes horizontales con huecos
            if random.random() > 0.3:
                longitud = random.randint(4, 10)
                for dx in range(longitud):
                    if x+dx < ancho-2:
                        mapa[y][x+dx] = '#'
    
    # Posición inicial (S) y final (G)
    mapa[1][1] = 'S'
    mapa[alto-2][ancho-2] = 'G'
    
    # Elementos especiales ($)
    for _ in range(ancho*alto//500):  # Aproximadamente 27-28 elementos $
        x, y = random.randint(1, ancho-2), random.randint(1, alto-2)
        if mapa[y][x] == ' ':
            mapa[y][x] = '$'
    
    return mapa

def guardar_mapa(mapa, nombre_archivo):
    with open(nombre_archivo, 'w') as f:
        for fila in mapa:
            f.write(''.join(fila) + '\n')

# Generar y guardar el mapa
random.seed(42)  # Semilla para reproducibilidad
mapa_170x170 = generar_map()
guardar_mapa(mapa_170x170, "map.txt")
