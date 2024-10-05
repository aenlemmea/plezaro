#include "internal/log.hh"

auto main(int argc, char** argv) -> int {
  Logger::log(LOG_LEVEL::INFO, "Hi from main!");
	return 0;
}
