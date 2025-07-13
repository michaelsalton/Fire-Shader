#include "shaders/FireShader.h"

FireShader::FireShader() {

    colors.outer = sf::Glsl::Vec4(1.0f, 0.196f, 0.071f, 1.0f);
    colors.middle = sf::Glsl::Vec4(1.0f, 0.647f, 0.0f, 1.0f);
    colors.inner = sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f);
    
    parameters.animationSpeed = 0.5f;
    parameters.yOffset = 0.5f;
    parameters.redBandThreshold = 0.2f;
    parameters.orangeBandThreshold = 0.5f;
    parameters.yellowBandThreshold = 0.7f;
    parameters.alphaThreshold = 0.2f;
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