#pragma once
#include <SFML/Graphics.hpp>
#include "Material.h"

class Entity {
protected:
    sf::Drawable* drawable;
    Material* material;
    
public:
    Entity(sf::Drawable* obj = nullptr, Material* mat = nullptr);
    virtual ~Entity();
    
    void setDrawable(sf::Drawable* obj);
    void setMaterial(Material* mat);
    
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    
    Material* getMaterial() const;
    sf::Drawable* getDrawable() const;
};