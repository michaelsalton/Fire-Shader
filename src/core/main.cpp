#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "GameManager.h"

int main(int argc, char* argv[])
{
    GameManager* game = GameManager::Instance();
    
    game->SetFireColors(
        sf::Glsl::Vec4(1.0f, 0.196f, 0.071f, 1.0f),  // Red (outer)
        sf::Glsl::Vec4(1.0f, 0.647f, 0.0f, 1.0f),    // Orange (middle)
        sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f)       // Yellow (inner)
    );
    game->SetAnimationSpeed(0.5f);
    
    game->Run();
    GameManager::Release();
    game = nullptr;
    
    return 0;
}