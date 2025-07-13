#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureLoader {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    
public:
    bool loadTexture(const std::string& name, const std::string& filepath);
    sf::Texture* getTexture(const std::string& name);
    void setTextureRepeated(const std::string& name, bool repeated);
    bool hasTexture(const std::string& name) const;
};