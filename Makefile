# Chemins vers les répertoires SDL
SDL_PATH = SDL2
INCLUDE_PATH = $(SDL_PATH)/include
LIB_PATH = $(SDL_PATH)/lib

# Compilateur et options
CC = gcc
CFLAGS = -I$(INCLUDE_PATH)
LDFLAGS = -L$(LIB_PATH) -lmingw32 -lSDL2main -lSDL2

# Fichiers source et cible
SRCS = src/physics.c src/init.c src/process_inputs.c src/goomba.c src/player.c src/main.c
TARGET = src/mario.exe

# Règles
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	cd src && start mario.exe

clean:
	rm -f $(TARGET)
