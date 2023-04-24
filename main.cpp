#include <iostream>
#include <oatpp/network/Server.hpp>

int main() {
	oatpp::base::Environment::init();
	std::cout << "\nEnvironment:\n";
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
	return 0;
}