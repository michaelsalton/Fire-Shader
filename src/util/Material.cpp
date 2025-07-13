#include "util/Material.h"

Material::Material() : shader(nullptr) {
}

Material::~Material() {
    // Note: We don't delete the shader here as it might be shared
}

bool Material::loadShader(const std::string& vertexPath, const std::string& fragmentPath) {
    shader = new Shader();
    if (!shader->loadFromFile(vertexPath, fragmentPath)) {
        delete shader;
        shader = nullptr;
        return false;
    }
    return true;
}

void Material::setShader(Shader* newShader) {
    shader = newShader;
}

void Material::setFloat(const std::string& name, float value) {
    floatUniforms[name] = value;
}

void Material::setVec4(const std::string& name, const sf::Glsl::Vec4& value) {
    vec4Uniforms[name] = value;
}

void Material::setTexture(const std::string& name, sf::Texture* texture) {
    textureUniforms[name] = texture;
}

void Material::apply() {
    if (!shader || !shader->isLoaded()) {
        return;
    }
    
    // Apply all uniforms
    for (const auto& [name, value] : floatUniforms) {
        shader->setUniform(name, value);
    }
    
    for (const auto& [name, value] : vec4Uniforms) {
        shader->setUniform(name, value);
    }
    
    for (const auto& [name, texture] : textureUniforms) {
        if (texture) {
            shader->setUniform(name, *texture);
        }
    }
}

sf::Shader* Material::getNativeShader() const {
    return shader ? shader->getNativeShader() : nullptr;
}