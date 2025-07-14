#include "Core/Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode({width, height}), title) {
}

Renderer::~Renderer() {
}

bool Renderer::isOpen() const {
    return window.isOpen();
}

void Renderer::clear() {
    window.clear();
}

void Renderer::clear(sf::Color color) {
    window.clear(color);
}

void Renderer::draw(const sf::Drawable& drawable, const sf::RenderStates* states) {
    if (states) {
        window.draw(drawable, *states);
    } else {
        window.draw(drawable);
    }
}

void Renderer::display() {
    window.display();
}

void Renderer::setFramerateLimit(unsigned int limit) {
    window.setFramerateLimit(limit);
}

sf::RenderWindow& Renderer::getWindow() {
    return window;
}