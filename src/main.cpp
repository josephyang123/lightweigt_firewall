#include <iostream>
#include <string>
#include <vector>
#include <fstream> //files
#include <sstream> // string stream
#include <iomanip> //setw and setfill
#include <cstring>      // For memset
#include <limits>       //Ignore newline in function Menu
#include <openssl/sha.h>
#include <openssl/evp.h>

void writeFile(std::string Id,std::string Password);
std::string readFile();
std::string hashPassword(std::string& password);
void Register();
void Menu();
bool logIn(std::string Id,std::string Password);

bool logIn(std::string Id,std::string Password){

    std::vector<std::string> result;
    std::stringstream ss(readFile());
    std::string item;
    while(std::getline(ss,item,' ')){
        result.push_back(item);
    }
    if(hashPassword(Id)==result[0]&&hashPassword(Password)==result[1])
        return true;
    else return false;
}

void writeFile(std::string Id,std::string Password){

    std::ofstream writeF(".credentials.txt");
    writeF << hashPassword(Id) << " " << hashPassword(Password) << std::endl;
}

std::string readFile(){

    std::string line;
    std::ifstream readF(".credentials.txt");
    if(!readF)
        return "";
    if(std::getline(readF,line))
        return line;
    else return "Error";
}

std::string hashPassword( std::string& password) {
    password=password+"salt";
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength;
    
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, password.c_str(), password.length());
    EVP_DigestFinal_ex(mdctx, hash, &hashLength);
    EVP_MD_CTX_free(mdctx);
    
    std::stringstream ss;
    for (unsigned int i = 0; i < hashLength; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

void Register(){

    std::string enterId, enterPassword,rePassword;

    std::cout << std::string(50,'=') << std::endl;
    std::cout << std::string(18,' ') << "Register menu" << std::endl;
    std::cout << std::string(50,'=') << std::endl;

    std::cout << "User  ID:";
    std::getline(std::cin,enterId);
    std::cout << "Password:";
    std::getline(std::cin,enterPassword);
    std::cout << "Re-enter Password:";
    std::getline(std::cin,rePassword);

    if(enterPassword==rePassword)
        writeFile(enterId,enterPassword);
    else Register();

    Menu();

}

// A normal login menu
// but if User Id is 1 and there is no user credential stored
// call Register to create a new account
void Menu(){

    std::string enterId, enterPassword;

    std::cout << std::string(50,'=') << std::endl;
    std::cout << std::string(20,' ') << "Login menu" << std::endl;
    std::cout << std::string(50,'=') << std::endl;

    if(readFile()=="")
        Register();
    else{
        std::cout << "User  ID:";
        std::getline(std::cin,enterId);
        std::cout << "Password:";
        std::getline(std::cin,enterPassword);
        
        if(logIn(enterId,enterPassword))
            std::cout << "Welcome to Firewall" << std::endl;
        else std::cout << "Invalid Login" << std::endl;
    }
    
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Ignore the newline character, if any
    

}



int main() {

    std::cout << "Lightweight Firewall Started" << std::endl;
    Menu();
    
    
    return 0;
}
