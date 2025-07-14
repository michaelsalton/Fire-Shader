#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Shader/Shader.h"

class Material {
protected:
    Shader* shader;
    std::unordered_map<std::string, float> floatUniforms;
    std::unordered_map<std::string, sf::Glsl::Vec4> vec4Uniforms;
    std::unordered_map<std::string, sf::Texture*> textureUniforms;
    
public:
    Material();
    virtual ~Material();
    
    // Shader management
    bool loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void setShader(Shader* newShader);
    
    // Uniform setters
    void setFloat(const std::string& name, float value);
    void setVec4(const std::string& name, const sf::Glsl::Vec4& value);
    void setTexture(const std::string& name, sf::Texture* texture);
    
    // Apply material to rendering
    virtual void apply();
    virtual void update(float deltaTime) {}
    
    sf::Shader* getNativeShader() const;
};