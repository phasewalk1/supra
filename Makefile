CC = g++
CFLAGS = -Wall -Wextra -Wno-switch-bool -std=c++17

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

INCLUDE_DIRS = -I $(INC_DIR)/cmd -I $(INC_DIR)/extern -I $(INC_DIR)/util -I /usr/local/include

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

NAME = supra

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

wipe:
	rm $(BIN_DIR)/$(NAME)

fclean: clean
	rm -f $(BIN_DIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
