#pragma once

#include <SFML/Graphics.hpp>
#include "util/Shader.h"
#include <memory>

class FireShader {
public:
    struct FireColors {
        sf::Glsl::Vec4 outer;
        sf::Glsl::Vec4 middle;
        sf::Glsl::Vec4 inner;
    };
    
    struct FireParameters {
        float animationSpeed;
        float yOffset;
        float redBandThreshold;
        float orangeBandThreshold;
        float yellowBandThreshold;
        float alphaThreshold;
    };

private:
    FireColors colors;
    FireParameters parameters;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<sf::Texture> noiseTexture;
    sf::RectangleShape fireRect;
    sf::Clock animationClock;
    
public:
    FireShader();
    ~FireShader();
    
    bool initialize();
    
    const FireColors& getColors() const;
    const FireParameters& getParameters() const;
    sf::Glsl::Vec4 getOuterColor() const;
    sf::Glsl::Vec4 getMiddleColor() const;
    sf::Glsl::Vec4 getInnerColor() const;
    float getAnimationSpeed() const;
    float getYOffset() const;
    float getRedBandThreshold() const;
    float getOrangeBandThreshold() const;
    float getYellowBandThreshold() const;
    float getAlphaThreshold() const;
    
    void setColors(const FireColors& newColors);
    void setParameters(const FireParameters& newParams);
    void setAnimationSpeed(float speed);
    
    void update();
    void render(sf::RenderWindow& window);
};