#pragma once

#include <SFML/Graphics.hpp>
#include "Render.h"
#include "TextureLoader.h"
#include "Shader.h"

class FireShader {
private:
    Render* renderer;
    TextureLoader* textureLoader;
    Shader shader;
    
    sf::Sprite fullscreenQuad;
    sf::Clock clock;
    
    // Fire properties
    float animationSpeed;
    sf::Glsl::Vec4 outerColor;
    sf::Glsl::Vec4 middleColor;
    sf::Glsl::Vec4 innerColor;
    
    unsigned int windowWidth;
    unsigned int windowHeight;
    
    void setupQuad();
    void updateUniforms();
    
public:
    FireShader(Render* render, TextureLoader* texLoader, unsigned int width, unsigned int height);
    
    bool initialize();
    void update();
    void render();
    
    // Configuration
    void setAnimationSpeed(float speed);
    void setFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner);
};