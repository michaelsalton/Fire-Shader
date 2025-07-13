#include "util/TextureLoader.h"

TextureLoader::TextureLoader() {
}

TextureLoader::~TextureLoader() {
    // Clean up any loaded textures
    textures.clear();
}

bool TextureLoader::loadTexture(const std::string& name, const std::string& filepath) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filepath)) {
        return false;
    }
    textures[name] = std::move(texture);
    return true;
}

sf::Texture* TextureLoader::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        return it->second.get();
    }
    return nullptr;
}

void TextureLoader::setTextureRepeated(const std::string& name, bool repeated) {
    auto it = textures.find(name);
    if (it != textures.end()) {
        it->second->setRepeated(repeated);
    }
}

bool TextureLoader::hasTexture(const std::string& name) const {
    return textures.find(name) != textures.end();
}