CC=g++

LIBS=sdl2 SDL2_image SDL2_ttf

CFLAGS=-Wall -Wextra -pedantic `pkgconf --cflags $(LIBS)` -std=c++11
LDFLAGS=`pkgconf --libs $(LIBS)`

SRC_DIR=src
HDR_DIR=src 
OBJ_DIR=obj

BIN_DIR=bin
BIN_DEBUG_DIR=$(BIN_DIR)/debug
BIN_RELEASE_DIR=$(BIN_DIR)/release

SRC_FILES=$(wildcard $(SRC_DIR)/**/*.cc $(SRC_DIR)/*.cc)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET=pong

TARGET_DEBUG=$(BIN_DEBUG_DIR)/$(TARGET)
TARGET_RELEASE=$(BIN_RELEASE_DIR)/$(TARGET)

.PHONY: debug release clean

all: debug release

debug: CFLAGS += -g
debug: $(BIN_DEBUG_DIR) $(OBJ_DIR) $(TARGET_DEBUG)

release: CFLAGS += -O2 -DNDEBUG
release: $(BIN_RELEASE_DIR) $(OBJ_DIR) $(TARGET_RELEASE)

$(TARGET_DEBUG): $(OBJ_FILES) 
	$(CC) $(CFLAGS) $^ -I$(HDR_DIR) -o $@ $(LDFLAGS)

$(TARGET_RELEASE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -I$(HDR_DIR) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CC_FLAGS) -c $^ -I$(HDR_DIR) -o $@

$(OBJ_DIR):
	mkdir $@

$(BIN_DEBUG_DIR):
	mkdir -p $@

$(BIN_RELEASE_DIR):
	mkdir -p $@

clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)
