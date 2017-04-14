#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <iostream>
#include <string>

int main()
{
	ydclient client{ "token" };

	auto data = client.info();
	bool is_error = data.find("error") != data.end();

	if (is_error) {
		std::cout << "Error occured: " << data["message"].get<std::string>() << std::endl;
	}
	else {
		std::cout << "Total space: " << data["total_space"].get<std::size_t>() << std::endl;
		std::cout << "Trash size: "  << data["trash_size"].get<std::size_t>()  << std::endl;
		std::cout << "Used space: "  << data["used_space"].get<std::size_t>()  << std::endl;
	}
	return 0;
}
