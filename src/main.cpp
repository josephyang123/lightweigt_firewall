#include <iostream>
#include <string>
#include <cstring>      // For memset
#include <limits>



void Register(){

    std::cout << std::string(50,'=') << std::endl;
    std::cout << std::string(18,' ') << "Register menu" << std::endl;
    std::cout << std::string(50,'=') << std::endl;

}

// A normal login menu
// but if User Id is 1 and there is no user credential stored
// call Register to create a new account
void Menu(){

    std::string enterId, enterPassword;

    std::cout << std::string(50,'=') << std::endl;
    std::cout << std::string(20,' ') << "Login menu" << std::endl;
    std::cout << std::string(50,'=') << std::endl;

    std::cout << "User  ID:";
    std::getline(std::cin,enterId);
    std::cout << "Password:";
    std::getline(std::cin,enterPassword);
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Ignore the newline character, if any
    // if(enterId == "1")
    Register();

}



int main() {

    std::cout << "Lightweight Firewall Started" << std::endl;
    Menu();
    return 0;
}
