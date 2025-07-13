#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Shader {
private:
    sf::Shader shader;
    bool loaded;
    
public:
    Shader();
    ~Shader();
    
    bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const sf::Glsl::Vec4& value);
    void setUniform(const std::string& name, const sf::Texture& texture);
    
    sf::Shader* getNativeShader();
    bool isLoaded() const;
};