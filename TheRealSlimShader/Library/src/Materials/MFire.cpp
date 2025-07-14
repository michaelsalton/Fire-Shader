#include "Materials/MFire.h"
#include <iostream>

MFire::MFire(TextureLoader* texLoader) : textureLoader(texLoader) {
    config.outerColor = sf::Glsl::Vec4(1.0f, 0.196f, 0.071f, 1.0f);
    config.middleColor = sf::Glsl::Vec4(1.0f, 0.647f, 0.0f, 1.0f);
    config.innerColor = sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f);
    config.animationSpeed = 0.5f;
    config.yOffset = 0.5f;
    config.redBandThreshold = 0.2f;
    config.orangeBandThreshold = 0.5f;
    config.yellowBandThreshold = 0.7f;
    config.alphaThreshold = 0.2f;
}

MFire::~MFire() {
}

bool MFire::initialize() {
    if (!loadShader("TheRealSlimShader/assets/shaders/fire/vertex.glsl", "TheRealSlimShader/assets/shaders/fire/fragment.glsl")) {
        std::cerr << "Failed to load fire shader" << std::endl;
        return false;
    }
    
    if (!textureLoader->loadTexture("perlin", "TheRealSlimShader/assets/textures/perlin.png")) {
        std::cerr << "Failed to load perlin noise texture" << std::endl;
        return false;
    }
    
    sf::Texture* noiseTexture = textureLoader->getTexture("perlin");
    if (noiseTexture) {
        noiseTexture->setRepeated(true);
        setTexture("noise_texture", noiseTexture);
    }
    
    setVec4("flame_color_outer", config.outerColor);
    setVec4("flame_color_middle", config.middleColor);
    setVec4("flame_color_inner", config.innerColor);
    setFloat("animation_speed", config.animationSpeed);
    
    std::cout << "Fire material initialized successfully" << std::endl;
    return true;
}

void MFire::update(float deltaTime) {
    float time = clock.getElapsedTime().asSeconds();
    setFloat("time", time);
    
    setVec4("flame_color_outer", config.outerColor);
    setVec4("flame_color_middle", config.middleColor);
    setVec4("flame_color_inner", config.innerColor);
    setFloat("animation_speed", config.animationSpeed);
    
    apply();
}

void MFire::setFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner) {
    config.outerColor = outer;
    config.middleColor = middle;
    config.innerColor = inner;
}

void MFire::setAnimationSpeed(float speed) {
    config.animationSpeed = speed;
}

void MFire::setBandThresholds(float red, float orange, float yellow) {
    config.redBandThreshold = red;
    config.orangeBandThreshold = orange;
    config.yellowBandThreshold = yellow;
}