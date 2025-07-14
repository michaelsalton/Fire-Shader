#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "Core/GameManager.h"
#include "Shaders/FireShader.h"

int main(int argc, char* argv[])
{
    GameManager* game = GameManager::Instance();
    
    FireShader* fireShader = new FireShader(game->GetTextureLoader());
    
    game->SetFireShader(fireShader);
    game->Run();
    
    GameManager::Release();
    delete fireShader;
    game = nullptr;
    
    return 0;
}