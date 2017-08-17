//Copyright (C) 2017  Dakota Walsh

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

// run a command and get output as a string
std::string exec(const char* cmd) {
	// create a buffer
    std::array<char, 128> buffer;
	// create result string
    std::string result;
	// use popen to run the passed in command
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	// throw and error on fail
    if (!pipe) throw std::runtime_error("popen() failed!");
	// put output into buffer then pass to result until the end
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

int main(int argc, char *argv[]) {
	// get the first argument and print it for testing
	std::cout << argv[1] << std::endl;
	
	// create a string from the first argument
	std::string file_name = argv[1];

	// create a string for the base command
	const std::string base_cmd = "curl -F c=@- https://ptpb.pw < ";

	// combine the command and the file name
	std::string system_s = base_cmd + file_name;
	
	// run the command on the system
	// also convert it from string to char array so it can be used with system()
	std::string system_o = exec(system_s.c_str());
	std::cout << system_o << std::endl;
	return 0;
}
