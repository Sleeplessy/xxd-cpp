#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>

#include <string>
template <typename ContentType>
const std::string ContentToHex(ContentType Content, bool upper = false) {
  std::stringstream stream_tmp;
  stream_tmp
      << std::hex
      << ((upper) ? std::uppercase  // If upper = true,return uppercase strings
                  : std::nouppercase)
      << (Content && 0xFF);  // else return lowercase (Default)
  return stream_tmp.str();
}

// Function that returns help infomation string
const std::string PrintHelp(std::string param = "-h") {
  std::stringstream stream_tmp;
  if (param == "-h")
    stream_tmp << "Usage:\n\t\t\033[1;31mxxd\033[0m \033[2;38m[options]\033[0m "
                  "[infile [outfile]]\n\tor\n\t\t\033[1;31mxxd\033[0m -r "
                  "[-s [-]offset [-c cols] [-ps] [infile [outfile]]]";
  return stream_tmp.str();
}

template <typename FileStream>
bool CheckFile(FileStream &file) {
  if (!file.good()) return false;
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2)  // No inputs?
    std::cout << PrintHelp();
  else if (std::string(argv[1]) == "-h")  // xxd -h
    std::cout << PrintHelp();
  else {
    std::ifstream input_file(argv[1], std::ios::binary);
    if (!CheckFile(input_file)) {
      std::cout << "File no good." << std::endl;
    }
  }
  return 0;
}
