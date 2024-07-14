# Définir les constantes
NUM_LINES = 5000
RECT_WIDTH = 32
RECT_HEIGHT = 32
START_X = 0
START_Y = 480

# Ouvrir le fichier en mode écriture
with open("../map/ground.txt", "w") as file:
    x = START_X
    y = START_Y

    # Générer et écrire les lignes dans le fichier
    for _ in range(NUM_LINES):
        file.write(f"{x},{y},{RECT_WIDTH},{RECT_HEIGHT}\n")
        x += RECT_WIDTH

print(f"File level.txt created with {NUM_LINES} lines.")
