#pragma once
#include "util/Material.h"
#include "util/TextureLoader.h"

class MFire : public Material {
private:
    sf::Clock clock;
    TextureLoader* textureLoader;
    
    // Fire-specific parameters
    struct FireConfig {
        sf::Glsl::Vec4 outerColor;
        sf::Glsl::Vec4 middleColor;
        sf::Glsl::Vec4 innerColor;
        float animationSpeed;
        float yOffset;
        float redBandThreshold;
        float orangeBandThreshold;
        float yellowBandThreshold;
        float alphaThreshold;
    } config;
    
public:
    MFire(TextureLoader* texLoader);
    ~MFire();
    
    bool initialize();
    void update(float deltaTime) override;
    
    // Fire-specific configuration
    void setFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner);
    void setAnimationSpeed(float speed);
    void setBandThresholds(float red, float orange, float yellow);
};