#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
static const char *option_string = "s:abc:EeghHil:ouv";
std::string ContentToHex(char Content, bool upper = false) {
  std::stringstream stream_tmp;
  stream_tmp
      << std::hex
      << ((upper) ? std::uppercase  // If upper = true,return uppercase strings
                  : std::nouppercase)
      << (Content & 0xFF);  // else return lowercase (Default)
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

inline bool CheckFileExist(char *&file_name) {
  return (access(file_name, F_OK) != -1);
}

const std::string ConvertToHex(std::ifstream &input_file,
                               bool upper = false,int width = 16) {
  std::string file_contents;  // String to store file contents
  input_file.seekg(0, std::ios::end);
  long file_length = input_file.tellg();
  file_contents.resize(file_length);  // read file sieze
  input_file.seekg(0, std::ios::beg);
  input_file.read(&file_contents[0],
                  file_contents.size());  // read file buff to string
  // now start converting
  std::stringstream hex_stream;
  for (auto byte_content : file_contents) {
    hex_stream << ContentToHex(byte_content, upper);  // Convert byte-to-byte
  }
  return hex_stream.str();
}

std::string ConvertToHex(std::stringstream user_input) {
  // catch stdin
}

int main(int argc, char **argv) {
  std::ifstream input_file;
  std::ofstream output_file;
  int seek=0;
  if (argc < 2)  // No inputs?
    std::cout << PrintHelp();
  else {
    int params = 0;
    bool upper = false;
    params = getopt(argc, argv, option_string); // parse command options
    while (params != -1) {
      switch (params) {
        case 'H':case 'h':case '?':
          std::cout << PrintHelp();
		  return 0;
          break;
        case 'u':
          upper = true;
		  break;
		case 's':
		  seek=optind;
		  break;
		case 'o':
		  output_file.open(argv[optind],std::ios::binary);
		  break;
      }
      params = getopt(argc, argv, option_string);
    }
    if (!CheckFileExist(argv[optind])) {
      std::cout << "xxd: " << argv[1] << ": No such file or directory."
                << std::endl;  // file not exist
	  return -1;
    }
	if(input_file.good())
    input_file.open(argv[optind], std::ios::binary);
	std::string hexdump = ConvertToHex(input_file,upper);
	if(output_file.is_open())
			output_file<<hexdump;
	else
			std::cout<<hexdump;

  }
  return 0;
}
