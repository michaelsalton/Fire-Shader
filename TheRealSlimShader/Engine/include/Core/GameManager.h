#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Renderer.h"
#include "Utils/TextureLoader.h"
#include "Shaders/FireShader.h"

class GameManager {
private:
    static GameManager* instance;
    
    Renderer* renderer;
    TextureLoader* textureLoader;
    FireShader* fireShader;
    
    bool initialized;
    
    // Private constructor for singleton
    GameManager();
    
    bool Initialize();
    void Update();
    void Render();
    void HandleEvents();
    
public:
    static GameManager* Instance();
    static void Release();
    
    void Run();
    
    // Public configuration methods
    void SetFireShader(FireShader* shader);
    void SetFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner);
    void SetAnimationSpeed(float speed);
    
    TextureLoader* GetTextureLoader() { return textureLoader; }
    
    // Prevent copying
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
};