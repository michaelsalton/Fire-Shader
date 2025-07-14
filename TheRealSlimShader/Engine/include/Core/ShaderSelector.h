#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>
#include <memory>
#include "Material/Material.h"

struct ShaderInfo {
    std::string name;
    std::string fragmentPath;
    std::string vertexPath;
    std::string displayName;
    sf::Texture previewTexture;
    bool hasPreview = false;
};

class ShaderSelector {
private:
    std::vector<ShaderInfo> availableShaders;
    sf::Font font;
    sf::RenderWindow* window;
    
    // UI Elements
    std::vector<sf::RectangleShape> shaderButtons;
    std::vector<sf::Text> shaderLabels;
    std::vector<sf::Sprite> previewSprites;
    sf::Text titleText;
    sf::RectangleShape background;
    sf::RectangleShape closeButton;
    sf::Text closeButtonText;
    
    // State
    int selectedIndex = -1;
    int hoveredIndex = -1;
    bool isVisible = true;
    
    // Layout constants
    static constexpr float BUTTON_WIDTH = 280.0f;
    static constexpr float BUTTON_HEIGHT = 80.0f;
    static constexpr float BUTTON_SPACING = 10.0f;
    static constexpr float PREVIEW_SIZE = 60.0f;
    static constexpr float MARGIN = 20.0f;

public:
    ShaderSelector(sf::RenderWindow* window);
    ~ShaderSelector();
    
    bool initialize();
    void scanShaderDirectory(const std::string& shaderPath = "shaders/");
    void createUI();
    
    // Event handling
    bool handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void render();
    
    // Getters
    bool isShaderSelected() const { return selectedIndex >= 0; }
    std::string getSelectedShaderName() const;
    std::string getSelectedFragmentPath() const;
    std::string getSelectedVertexPath() const;
    bool isOpen() const { return isVisible; }
    
    // Control
    void show() { isVisible = true; selectedIndex = -1; }
    void hide() { isVisible = false; }
    void reset() { selectedIndex = -1; hoveredIndex = -1; }
    
private:
    void loadPreviewTextures();
    std::string formatShaderName(const std::string& filename);
    sf::Vector2f calculateButtonPosition(int index);
    bool isPointInButton(const sf::Vector2f& point, int buttonIndex);
    void updateHover(const sf::Vector2f& mousePos);
};