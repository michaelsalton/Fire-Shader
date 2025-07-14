#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include "Core/GameManager.h"
#include "Shaders/FireShader.h"

int main(int argc, char* argv[])
{
    std::cout << "Welcome to TheRealSlimShader!" << std::endl;
    std::cout << "\nAvailable shaders:" << std::endl;
    std::cout << "  1. fire - Animated fire effect" << std::endl;
    std::cout << "  2. sun - Solar effect (coming soon)" << std::endl;
    std::cout << "\nEnter shader name or number: ";
    
    std::string shaderChoice;
    std::getline(std::cin, shaderChoice);
    
    // Convert to lowercase
    for (char& c : shaderChoice) {
        c = std::tolower(c);
    }
    
    GameManager* game = GameManager::Instance();
    
    if (shaderChoice == "fire" || shaderChoice == "1") {
        std::cout << "Loading fire shader..." << std::endl;
        FireShader* fireShader = new FireShader(game->GetTextureLoader());
        game->SetFireShader(fireShader);
        game->Run();
        delete fireShader;
    } else if (shaderChoice == "sun" || shaderChoice == "2") {
        std::cout << "Sun shader not yet implemented. Loading fire shader instead..." << std::endl;
        FireShader* fireShader = new FireShader(game->GetTextureLoader());
        game->SetFireShader(fireShader);
        game->Run();
        delete fireShader;
    } else {
        std::cout << "Unknown shader. Loading default fire shader..." << std::endl;
        FireShader* fireShader = new FireShader(game->GetTextureLoader());
        game->SetFireShader(fireShader);
        game->Run();
        delete fireShader;
    }
    
    GameManager::Release();
    game = nullptr;
    
    return 0;
}