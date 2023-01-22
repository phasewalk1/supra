#include "init.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Initializer::Initializer(std::string path) { this->path = path; }

/**
 * @brief: Creates a new project directory and its subdirectories
 * @dev: If this->path already exists, throws an error
 * 
 * @param bench_mode(bool): Whether or not to create a bench/ directory
 */
void Initializer::init_dir(bool bench_mode) {
  if (fs::exists(this->path) && !(fs::is_empty(this->path))) {
    throw std::runtime_error("Error: Directory already exists");
  }
  else {
    try {
      // create top level directory
      fs::create_directory(this->path);

      // create directories
      std::string src_path = this->path + "/src";
      std::string tests_path = this->path + "/tests";
      std::string incl_path = this->path + "/include";
      std::string build_path = this->path + "/build";
      std::string bin_path = this->path + "/bin";
      fs::create_directory(src_path);
      fs::create_directory(tests_path);
      fs::create_directory(incl_path);
      fs::create_directory(build_path);
      fs::create_directory(bin_path);

      if (bench_mode) {
        std::string bench_path = this->path + "/bench";
        fs::create_directory(bench_path);
      }

      // create src file
      std::string src_file_path = src_path + "/main.cpp";
      std::ofstream ofs(src_file_path);
      ofs << "#include <iostream>\n\nint main() {\n  "
        "std::cout << \"Hello World\" << std::endl;\n  return 0;\n}\n";
      ofs.close();

      // create Makefile
      this->makefile();

      // create git repo
      this->make_git();

      std::cout << "Created directory " << this->path << std::endl;
    }
    catch (const fs::filesystem_error& e) {
      std::cout << e.what() << std::endl;
    }
  }

  return;
}

/**
 * @brief: Creates a Makefile in the project directory
 * TODO: Make this more robust and customizable
 */
void Initializer::makefile() {
  std::ofstream ofs(this->path + "/Makefile");
  ofs << "NAME = " << this->path
    << "\n\n"
    "CC = g++\n"
    "CFLAGS = -Wall -Wextra -Werror -std=c++17\n\n"
    "SRC_DIR = src\n"
    "INC_DIR = include\n"
    "OBJ_DIR = build\n"
    "BIN_DIR = bin\n\n"
    "SRC = $(wildcard $(SRC_DIR)/*.cpp)\n"
    "OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)\n\n"
    "all: $(BIN_DIR)/$(NAME)\n\n"
    "$(BIN_DIR)/$(NAME): $(OBJ)\n"
    "\t$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(OBJ)\n\n"
    "$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp\n"
    "\t@mkdir -p $(OBJ_DIR)\n"
    "\t$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@\n\n"
    "clean:\n"
    "\trm -f $(OBJ_DIR)\n\n"
    "fclean: clean\n"
    "\trm -f $(NAME)\n\n"
    "re: fclean all\n\n"
    ".PHONY: all clean fclean re\n";
}

/**
 * @brief: Initializes a git repository in the project directory
 * @dev: If git is not installed, this will fail silently
 */
void Initializer::make_git() {
  std::string cmd = "git init " + this->path + "> /dev/null 2>&1";
  int result = std::system(cmd.c_str());
  if (result == 0) {
    std::cout << "Initialized git repository in " << this->path << std::endl;
  }
  else {
    std::cout << "Error: Failed to initialize git repository in " << this->path
      << std::endl;
  }
}