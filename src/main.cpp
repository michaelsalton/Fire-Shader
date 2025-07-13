#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fire Shader");
    window.setFramerateLimit(60);
    
    sf::RectangleShape fullscreenQuad(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fullscreenQuad.setFillColor(sf::Color::White);
    
    sf::Shader fireShader;
    if (!fireShader.loadFromFile("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        std::cerr << "Failed to load shaders!" << std::endl;
        return -1;
    }
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        float time = clock.getElapsedTime().asSeconds();
        fireShader.setUniform("time", time);
        fireShader.setUniform("resolution", sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        
        window.clear();
        window.draw(fullscreenQuad, &fireShader);
        window.display();
    }
    
    return 0;
}