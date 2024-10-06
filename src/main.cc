#include "internal/lex_run.hh"
#include "internal/log.hh"

#include <fstream>
#include <iostream>
#include <sstream>

std::stringstream source;

static void handle_checks(const char* str) {
    Logger::log(LOG_LEVEL::INFO, "Handling checks");
    const std::string t(str);
    if (t.rfind(".plr") != t.length() - 4) {
        std::cerr << "File must end with .plz" << std::endl;
	exit(-1);
    }
    else if (t.size() >= 100'000) {
        std::cerr << "File Too big" << std::endl;
	exit(-1);
    }
}

auto main(int argc, char** argv) -> int {
    if (argc != 2) {
        std::cerr << "USAGE: " << "./plz <src.plr>" << "\n";
        exit(-1);
    }

    Logger::log(LOG_LEVEL::INFO, "Ok Start");

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        Logger::log(LOG_LEVEL::INFO, "Over here");
        std::cerr << "FAILED opening file" << std::endl;
    }
    else {
        Logger::log(LOG_LEVEL::INFO, "Streaming the buffer");
        handle_checks(argv[1]);
        source << file.rdbuf();
    }

    file.close();
    Logger::log(LOG_LEVEL::INFO, "File closed, trying to print");
    std::cout << source.str() << std::endl;
    ::parse(source);

    return 0;
}
