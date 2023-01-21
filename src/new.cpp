#include "new.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

Initializer::Initializer(std::string path) { this->path = path; }

void Initializer::init_dir() {
  if (fs ::exists(this->path) && !(fs ::is_empty(this->path))) {
    throw std::runtime_error("Error: Directory already exists");
  } else {
    try {
      fs ::create_directory(this->path);
      std::cout << "Created directory " << this->path << std::endl;
    } catch (const fs ::filesystem_error& e) {
      std::cout << e.what() << std::endl;
    }
  }

  return;
}