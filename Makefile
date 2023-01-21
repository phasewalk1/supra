CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

NAME = saleen

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

wipe:
	rm $(BIN_DIR)/$(NAME)

fclean: clean
	rm -f $(BIN_DIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
