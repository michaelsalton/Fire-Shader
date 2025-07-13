#include "shaders/FireShader.h"
#include <iostream>

FireShader::FireShader(TextureLoader* texLoader) 
    : fireMaterial(std::make_unique<MFire>(texLoader)),
      textureLoader(texLoader) {
    
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
    
    // Initialize the fire material
    if (!fireMaterial->initialize()) {
        std::cerr << "Failed to initialize fire material" << std::endl;
        return false;
    }
    
    // Set the texture on the rectangle after material is initialized
    sf::Texture* noiseTexture = textureLoader->getTexture("perlin");
    if (noiseTexture) {
        fireRect.setTexture(noiseTexture);
    }
    
    std::cout << "Fire shader initialized successfully" << std::endl;
    return true;
}

void FireShader::update() {
    // Update is now handled by the material
    fireMaterial->update(0.0f); // deltaTime not used in current implementation
}

void FireShader::render(sf::RenderWindow& window) {
    if (fireMaterial && fireMaterial->getNativeShader()) {
        // Update the material uniforms
        update();
        
        // Set up render states with the material's shader
        sf::RenderStates states;
        states.shader = fireMaterial->getNativeShader();
        states.blendMode = sf::BlendAlpha;
        
        // Get the noise texture from material
        sf::Texture* noiseTexture = textureLoader->getTexture("perlin");
        if (noiseTexture) {
            states.texture = noiseTexture;
            // Set the current texture uniform
            fireMaterial->getNativeShader()->setUniform("noise_texture", sf::Shader::CurrentTexture);
        }
        
        window.draw(fireRect, states);
    } else {
        std::cerr << "Fire material not loaded!" << std::endl;
    }
}

const FireShader::FireColors& FireShader::getColors() const {
    static FireColors colors;
    // For compatibility, return default colors
    colors.outer = sf::Glsl::Vec4(1.0f, 0.196f, 0.071f, 1.0f);
    colors.middle = sf::Glsl::Vec4(1.0f, 0.647f, 0.0f, 1.0f);
    colors.inner = sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f);
    return colors;
}

const FireShader::FireParameters& FireShader::getParameters() const {
    static FireParameters params;
    // For compatibility, return default parameters
    params.animationSpeed = 0.5f;
    params.yOffset = 0.5f;
    params.redBandThreshold = 0.2f;
    params.orangeBandThreshold = 0.5f;
    params.yellowBandThreshold = 0.7f;
    params.alphaThreshold = 0.2f;
    return params;
}

sf::Glsl::Vec4 FireShader::getOuterColor() const {
    return getColors().outer;
}

sf::Glsl::Vec4 FireShader::getMiddleColor() const {
    return getColors().middle;
}

sf::Glsl::Vec4 FireShader::getInnerColor() const {
    return getColors().inner;
}

float FireShader::getAnimationSpeed() const {
    return getParameters().animationSpeed;
}

float FireShader::getYOffset() const {
    return getParameters().yOffset;
}

float FireShader::getRedBandThreshold() const {
    return getParameters().redBandThreshold;
}

float FireShader::getOrangeBandThreshold() const {
    return getParameters().orangeBandThreshold;
}

float FireShader::getYellowBandThreshold() const {
    return getParameters().yellowBandThreshold;
}

float FireShader::getAlphaThreshold() const {
    return getParameters().alphaThreshold;
}

void FireShader::setColors(const FireColors& newColors) {
    if (fireMaterial) {
        fireMaterial->setFireColors(newColors.outer, newColors.middle, newColors.inner);
    }
}

void FireShader::setParameters(const FireParameters& newParams) {
    if (fireMaterial) {
        fireMaterial->setAnimationSpeed(newParams.animationSpeed);
        // Other parameters can be set if MFire is extended to support them
    }
}

void FireShader::setAnimationSpeed(float speed) {
    if (fireMaterial) {
        fireMaterial->setAnimationSpeed(speed);
    }
}