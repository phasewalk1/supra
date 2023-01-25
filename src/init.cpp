/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:38 by kat               #+#    #+#             */
/*   Updated: 2023/01/24 22:43:34 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/init.hpp"
#include "cmd/tester.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using testing::TestWriter;

/**
 * @brief Construct a new Init:: Initializer object
 * @dev Throws an error if the directory exists and is not empty
 */
Initializer::Initializer(std::string path, bool force) {
  if (fs::exists(path) && !(fs::is_empty(path)) && !(force)) {
    std::string err =
        "Error: Directory already exists and is not empty. Rerun with 'saleen "
        "new " +
        path + " --force' to overwrite.";
    throw std::runtime_error(err);
  } else {
    this->path = path;
  }
}

/**
 * @brief: Creates a new project directory and its subdirectories
 *
 * @param bench_mode(bool): Whether or not to create a bench/ directory
 */
void Initializer::spinup(bool bench_mode) {
  try {
    // create top level directory
    fs::create_directory(this->path);
    // create directories
    this->build_dir(bench_mode);
    // populate src/
    this->hello_world();
    // populate tests/
    this->init_test();
    // create Makefile
    this->makefile();
    // create git repo
    this->make_git();
    // create manifest
    this->manifest();
    std::cout << "Created directory " << this->path << std::endl;
  } catch (const fs::filesystem_error& e) {
    std::cout << e.what() << std::endl;
  }

  return;
}

/**
 * @brief: Creates necessary subdirectories
 * @dev: This is ran after the top level directory is created, within the
 * spinup() function
 */
void Initializer::build_dir(bool with_benches) {
  fs::create_directory(this->path + "/src");
  fs::create_directory(this->path + "/tests");
  fs::create_directory(this->path + "/include");
  fs::create_directory(this->path + "/build");
  fs::create_directory(this->path + "/bin");
  if (with_benches) {
    fs::create_directory(this->path + "/benches");
  }
}

/**
 * @brief: Creates a hello world file in src/main.cpp
 */
void Initializer::hello_world() {
  // create src file
  std::string src_file_path = this->path + "/src" + "/main.cpp";
  std::ofstream ofs(src_file_path);
  ofs << "#include <iostream>\n\nint main() {\n  "
         "std::cout << \"Hello World\" << std::endl;\n  return 0;\n}\n";
  ofs.close();
}

/**
 * @brief: Creates a test file in tests/try_main.cpp
 */
void Initializer::init_test() {
  testing::TestWriter::write("try_main", true, this->path + "/tests");
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
  } else {
    std::cout << "Error: Failed to initialize git repository in " << this->path
              << std::endl;
  }
  std::ofstream ofs(this->path + "/.gitignore");
  ofs << "/build\n/bin";
  ofs.close();
}

/**
 * @brief: Creates a manifest file in the project directory
 */
void Initializer::manifest() {
  std::ofstream ofs(this->path + "/supra.toml");
  ofs << "[package]\n"
         "name = \""
      << this->path
      << "\"\n"
         "version = \"0.1.0\"\n\n"
         "[tests]\n"
         "main = \"/tests/try_main.cpp\"";
}

inline void Initializer::new_test(std::string name) { TestWriter::write(name); }