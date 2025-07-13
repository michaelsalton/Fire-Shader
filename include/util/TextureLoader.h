#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

class TextureLoader {
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    
public:
    TextureLoader();
    ~TextureLoader();
    
    bool loadTexture(const std::string& name, const std::string& filepath);
    sf::Texture* getTexture(const std::string& name);
    void setTextureRepeated(const std::string& name, bool repeated);
    bool hasTexture(const std::string& name) const;
};