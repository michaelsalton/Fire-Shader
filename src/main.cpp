#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Fire Shader");
    window.setFramerateLimit(60);
    
    sf::Texture noiseTexture;
    if (!noiseTexture.loadFromFile("textures/perlin.png")) {
        std::cerr << "Failed to load noise texture!" << std::endl;
        return -1;
    }

    noiseTexture.setRepeated(true);

    sf::Sprite fullscreenQuad(noiseTexture);
    fullscreenQuad.setScale({
        static_cast<float>(WINDOW_WIDTH) / noiseTexture.getSize().x,
        static_cast<float>(WINDOW_HEIGHT) / noiseTexture.getSize().y
    });

    sf::Shader fireShader;
    if (!fireShader.loadFromFile("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        std::cerr << "Failed to load shaders!" << std::endl;
        return -1;
    }
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        float time = clock.getElapsedTime().asSeconds();
        float animationSpeed = 0.5;
        sf::Glsl::Vec4 flameColorOuter(1.0, 0.2, 0.1, 0.7);
        sf::Glsl::Vec4 flameColorMiddle(1.0, 0.6, 0.0, 0.7);
        sf::Glsl::Vec4 flameColorInner(1.0, 1.0, 0.0, 0.7);

        fireShader.setUniform("noise_texture", noiseTexture);
        fireShader.setUniform("time", time);
        fireShader.setUniform("animation_speed", animationSpeed);
        fireShader.setUniform("flame_color_outer", flameColorOuter);
        fireShader.setUniform("flame_color_middle", flameColorMiddle);
        fireShader.setUniform("flame_color_inner", flameColorInner);
        
        window.clear();
        window.draw(fullscreenQuad, &fireShader);
        window.display();
    }
    
    return 0;
}