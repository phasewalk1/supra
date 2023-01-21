# saleen
`saleen` is a toolkit that attempts to offer modernized development workflows to C++ developers. If you're familiar with `cargo` or `npm`, then `saleen` will feel right at home in your toolbelt.

## Features
`saleen` attempts to incorporate many of the widely loved features from Rusts amazing package manager/development tooling kit, `cargo`. Hence, `saleen` plans on implementing the following features

- [x] `saleen new` - Initializes a new C++ project with `src/`, `tests/`, a "hello world" file in `src/main.cpp`, and a `Makefile` for custom builds. After creating these files and directories, `saleen` instantiates the new workspace as a git repository.
- [ ] `saleen test` - Runs through the `tests/` directory and executes any test that is defined. Outputting information in a clear and concise manner. Output ceases on failure while pointing to which test failed.
- [ ] `saleen bench` - Executes all benchmarks defined in `benches/`, outputting their results.
- [ ] `saleen add` - Adds a package to the _saleen manifest_, `saleen.toml`. The _saleen manifest_ is a file that describes your project, its version, dependencies, and dev dependencies (dependencies needed only to compile tests/benches)

## Install
From the root directory, build the binary for `saleen` by running `make`. Once you have the `saleen` binary, copy it to somewhere in your shell's path, such as
```sh
sudo cp saleen /usr/local/bin/saleen
```

You can now use `saleen` to instantiate new C++ projects
```sh
saleen new my_project
```
This will create a new workspace entitled `my_project` with the following directory structure
* .git/
* bin/
* build/
* include/
* src/
  * main.cpp
* tests/
* Makefile

The default Makefile will look like this:
```Makefile
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

NAME = my_project

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
```
Thus, build files (`.o`) will be outputted to the `build` directory, while the final executable will be sent to `bin`.

`saleen new` can be run in `bench` mode to support the inclusion of an additional directory, `benches` which will, in the future, be used to run integrated benchmarks with `saleen bench`.