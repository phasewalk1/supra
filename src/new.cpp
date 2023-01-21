#include "new.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Initializer::Initializer(std::string path) { this->path = path; }

void Initializer::init_dir() {
  if (fs ::exists(this->path) && !(fs ::is_empty(this->path))) {
    throw std::runtime_error("Error: Directory already exists");
  } else {
    try {
      // create top level directory
      fs ::create_directory(this->path);

      // create src and tests directories
      std::string src_path = this->path + "/src";
      std::string tests_path = this->path + "/tests";
      fs ::create_directory(src_path);
      fs ::create_directory(tests_path);

      // create src file
      std::string src_file_path = src_path + "/main.cpp";
      std::ofstream ofs(src_file_path);
      ofs << "#include <iostream>\n\nint main() {\n  "
             "std::cout << \"Hello World\" << std::endl;\n  return 0;\n}\n";
      ofs.close();

      // create makefile
      std::string makefile_path = this->path + "/Makefile";
      ofs.open(makefile_path);
      ofs << "NAME = " << this->path
          << "\n\nSRC = src/main.cpp\n\nOBJ = "
             "$(SRC:.cpp=.o)\n\nCXX = clang++\nCXXFLAGS = -Wall -Wextra "
             "-Werror "
             "-std=c++98\n\nall: $(NAME)\n\n$(NAME): $(OBJ)\n\t$(CXX) "
             "$(CXXFLAGS) "
             "-o $(NAME) $(OBJ)\n\n%.o: %.cpp\n\t$(CXX) $(CXXFLAGS) -c $< -o "
             "$@\n\n"
             "clean:\n\trm -f $(OBJ)\n\nfclean: clean\n\trm -f $(NAME)\n\nre: "
             "fclean all\n\n.PHONY: all clean fclean re\n";
      ofs.close();

      std::cout << "Created directory " << this->path << std::endl;
    } catch (const fs ::filesystem_error& e) {
      std::cout << e.what() << std::endl;
    }
  }

  return;
}