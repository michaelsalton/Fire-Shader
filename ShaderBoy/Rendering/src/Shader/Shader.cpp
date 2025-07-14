#include "Shader/Shader.h"
#include <iostream>

Shader::Shader() : loaded(false) {
}

Shader::~Shader() {
}

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    if (!shader.loadFromFile(vertexPath, fragmentPath)) {
        std::cerr << "Failed to load shader from " << vertexPath << " and " << fragmentPath << std::endl;
        loaded = false;
        return false;
    }
    loaded = true;
    return true;
}

void Shader::setUniform(const std::string& name, float value) {
    shader.setUniform(name, value);
}

void Shader::setUniform(const std::string& name, const sf::Glsl::Vec4& value) {
    shader.setUniform(name, value);
}

void Shader::setUniform(const std::string& name, const sf::Texture& texture) {
    shader.setUniform(name, texture);
}

sf::Shader* Shader::getNativeShader() {
    return &shader;
}

bool Shader::isLoaded() const {
    return loaded;
}