#include "shaders/FireShader.h"
#include <iostream>

FireShader::FireShader() 
    : shader(std::make_unique<Shader>()),
      noiseTexture(std::make_unique<sf::Texture>()) {
    
    colors.outer = sf::Glsl::Vec4(1.0f, 0.196f, 0.071f, 1.0f);
    colors.middle = sf::Glsl::Vec4(1.0f, 0.647f, 0.0f, 1.0f);
    colors.inner = sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f);
    
    parameters.animationSpeed = 0.5f;
    parameters.yOffset = 0.5f;
    parameters.redBandThreshold = 0.2f;
    parameters.orangeBandThreshold = 0.5f;
    parameters.yellowBandThreshold = 0.7f;
    parameters.alphaThreshold = 0.2f;
    
    // Set up the fire rectangle
    fireRect.setSize(sf::Vector2f(800, 600));
    fireRect.setPosition(sf::Vector2f(0, 0));
    fireRect.setFillColor(sf::Color::White);
    
    // Set texture rect to ensure proper UV coordinates
    fireRect.setTextureRect(sf::IntRect({0, 0}, {800, 600}));
}

FireShader::~FireShader() {
}

bool FireShader::initialize() {
    // Check if shaders are available
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are not available on this system!" << std::endl;
        return false;
    }
    
    if (!shader->loadFromFile("shaders/fire/vertex.glsl", "shaders/fire/fragment.glsl")) {
        std::cerr << "Failed to load fire shader" << std::endl;
        return false;
    }
    
    // Load noise texture
    if (!noiseTexture->loadFromFile("textures/perlin.png")) {
        std::cerr << "Failed to load noise texture" << std::endl;
        return false;
    }
    noiseTexture->setRepeated(true);
    
    // Set the texture on the rectangle
    fireRect.setTexture(noiseTexture.get());
    
    std::cout << "Fire shader initialized successfully" << std::endl;
    return true;
}

void FireShader::update() {
    // Update shader uniforms
    float time = animationClock.getElapsedTime().asSeconds();
    
    shader->setUniform("time", time);
    shader->setUniform("animation_speed", parameters.animationSpeed);
    shader->setUniform("flame_color_outer", colors.outer);
    shader->setUniform("flame_color_middle", colors.middle);
    shader->setUniform("flame_color_inner", colors.inner);
    shader->setUniform("noise_texture", *noiseTexture);
}

void FireShader::render(sf::RenderWindow& window) {
    if (shader->isLoaded()) {
        update();
        
        sf::RenderStates states;
        states.shader = shader->getNativeShader();
        
        window.draw(fireRect, states);
    } else {
        std::cerr << "Shader not loaded!" << std::endl;
    }
}

const FireShader::FireColors& FireShader::getColors() const {
    return colors;
}

const FireShader::FireParameters& FireShader::getParameters() const {
    return parameters;
}

sf::Glsl::Vec4 FireShader::getOuterColor() const {
    return colors.outer;
}

sf::Glsl::Vec4 FireShader::getMiddleColor() const {
    return colors.middle;
}

sf::Glsl::Vec4 FireShader::getInnerColor() const {
    return colors.inner;
}

float FireShader::getAnimationSpeed() const {
    return parameters.animationSpeed;
}

float FireShader::getYOffset() const {
    return parameters.yOffset;
}

float FireShader::getRedBandThreshold() const {
    return parameters.redBandThreshold;
}

float FireShader::getOrangeBandThreshold() const {
    return parameters.orangeBandThreshold;
}

float FireShader::getYellowBandThreshold() const {
    return parameters.yellowBandThreshold;
}

float FireShader::getAlphaThreshold() const {
    return parameters.alphaThreshold;
}

void FireShader::setColors(const FireColors& newColors) {
    colors = newColors;
}

void FireShader::setParameters(const FireParameters& newParams) {
    parameters = newParams;
}

void FireShader::setAnimationSpeed(float speed) {
    parameters.animationSpeed = speed;
}