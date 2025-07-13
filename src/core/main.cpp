#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "managers/GameManager.h"
#include "shaders/FireShader.h"

int main(int argc, char* argv[])
{
    FireShader* fireShader = new FireShader();
    
    GameManager* game = GameManager::Instance();
    game->SetFireShader(fireShader);
    game->Run();
    
    GameManager::Release();
    delete fireShader;
    game = nullptr;
    
    return 0;
}