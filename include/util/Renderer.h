#pragma once

#include <SFML/Graphics.hpp>

class Renderer {
private:
    sf::RenderWindow window;
    
public:
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    ~Renderer();
    
    bool isOpen() const;
    void clear();
    void draw(const sf::Drawable& drawable, const sf::RenderStates* states = nullptr);
    void display();
    void setFramerateLimit(unsigned int limit);
    
    sf::RenderWindow& getWindow();
};