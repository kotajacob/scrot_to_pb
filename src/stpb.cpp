//Copyright (C) 2017  Dakota Walsh

#include <iostream>

int main(int argc, char *argv[]) {
	// get the first argument and print it for testing
	std::cout << argv[1] << std::endl;
	
	// create a string from the first argument
	std::string file_name = argv[1];

	// create a string for the base command
	std::string base_cmd = "curl -F c=@- https://ptpb.pw < ";

	// combine the command and the file name
	std::string system_s = base_cmd + file_name;
	
	// run the command on the system
	// also convert it from string to char array so it can be used with system()
	system(system_s.c_str());
	return 0;
}
