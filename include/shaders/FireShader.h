#pragma once

#include <SFML/Graphics.hpp>

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
    
public:
    FireShader();
    
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
};