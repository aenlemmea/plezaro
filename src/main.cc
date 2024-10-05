#include <iostream>
#include <fstream>
#include <sstream>

std::stringstream source;

static void handle_checks(const char* str) {
  const std::string t(str);
  if  (t.rfind(".plr") != t.length() - 4) {
    std::cerr << "File must end with .plz" << std::endl;
  } else if (t.size() >= 100'000) {
    std::cerr << "File Too big" << std::endl;
  }
  exit(-1);
}

auto main(int argc, char **argv) -> int {
    if(argc != 2) {
      std::cerr << "USAGE: " << "./plz <src.plr>" << "\n";
      exit(-1);
    }
  
    std::ifstream file(argv[1]);

    if (!file.is_open()) {
      std::cerr << "FAILED opening file" << std::endl;
    } else {
      handle_checks(argv[1]);
      source << file.rdbuf();
    }

    file.close();
    return 0;
}
