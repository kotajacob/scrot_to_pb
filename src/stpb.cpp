//Copyright (C) 2017  Dakota Walsh

#include <cstdio>
#include <iostream>
#include <fstream>
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
	// make strings for scrot and rm commands
	const std::string scrot_cmd = "scrot -q 100 scrot.png";
	const std::string xclip_cmd = "xclip -in -selection c clp";
	const std::string rm_s_cmd = "rm scrot.png";
	const std::string rm_c_cmd = "rm clp";

	// take screenshot
	system(scrot_cmd.c_str());

	// create a string for the base command
	std::string pb_cmd = "curl -F c=@- https://ptpb.pw < ";
	// combine the command and the file name
	pb_cmd = pb_cmd + "scrot.png";
	// run the command on the system
	// also convert it from string to char array so it can be used with system()
	std::string system_o = exec(pb_cmd.c_str());
	std::cout << system_o << std::endl;

	// now we can remove the file to clean up
	exec(rm_s_cmd.c_str());
	
	// now we must strip system_o of all but the url
	// first part
	std::size_t found_h = system_o.find("http");
	system_o.erase(0, found_h);
	// second part
	std::size_t found_u = system_o.find("uuid");
	std::size_t end_length = system_o.length() - found_u;
	system_o.erase(found_u, end_length);
	system_o.erase(system_o.length()-1);

	// send it to a file
	std::ofstream myfile;
	myfile.open ("clp");
	myfile << system_o;
	myfile << ".png";
	myfile.close();

	// send it to the clipboard
	system(xclip_cmd.c_str());
	
	// now we can remove the file to clean up
	exec(rm_c_cmd.c_str());

	// start firefox with that url
	std::string firefox_cmd = "firefox ";
	firefox_cmd = firefox_cmd + system_o;
	firefox_cmd = firefox_cmd + ".png";
	
	system(firefox_cmd.c_str());
	return 0;
}
