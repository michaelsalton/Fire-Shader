#include "ShaderSelector.h"
#include <iostream>
#include <algorithm>

ShaderSelector::ShaderSelector(sf::RenderWindow* window) : window(window) {}

ShaderSelector::~ShaderSelector() {}

bool ShaderSelector::initialize() {
    // Load font
    if (!font.loadFromFile("TheRealSlimShader/assets/fonts/font.ttf")) {
        std::cerr << "Warning: Could not load font. Using default font." << std::endl;
        // Continue without font - SFML will handle it
    }
    
    // Scan for shaders
    scanShaderDirectory("TheRealSlimShader/assets/shaders");
    
    if (availableShaders.empty()) {
        std::cerr << "No shaders found in shaders directory!" << std::endl;
        return false;
    }
    
    // Create UI elements
    createUI();
    loadPreviewTextures();
    
    return true;
}

void ShaderSelector::scanShaderDirectory(const std::string& shaderPath) {
    availableShaders.clear();
    
    try {
        if (!std::filesystem::exists(shaderPath)) {
            std::cerr << "Shader directory does not exist: " << shaderPath << std::endl;
            return;
        }
        
        // Scan subdirectories for shaders
        for (const auto& entry : std::filesystem::directory_iterator(shaderPath)) {
            if (entry.is_directory()) {
                std::string shaderName = entry.path().filename().string();
                std::string vertexPath = entry.path().string() + "/vertex.glsl";
                std::string fragmentPath = entry.path().string() + "/fragment.glsl";
                
                // Check if both vertex and fragment shaders exist
                if (std::filesystem::exists(vertexPath) && std::filesystem::exists(fragmentPath)) {
                    ShaderInfo info;
                    info.name = shaderName;
                    info.fragmentPath = fragmentPath;
                    info.vertexPath = vertexPath;
                    info.displayName = formatShaderName(shaderName);
                    
                    availableShaders.push_back(info);
                    std::cout << "Found shader: " << shaderName << std::endl;
                }
            }
        }
        
        std::cout << "Found " << availableShaders.size() << " shaders total" << std::endl;
        
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error scanning shader directory: " << e.what() << std::endl;
    }
}

void ShaderSelector::createUI() {
    sf::Vector2u windowSize = window->getSize();
    
    // Background
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black
    
    // Title
    titleText.setFont(font);
    titleText.setString("Select a Shader");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        (windowSize.x - titleBounds.width) / 2,
        MARGIN
    );
    
    // Close button
    closeButton.setSize(sf::Vector2f(100, 40));
    closeButton.setFillColor(sf::Color(200, 50, 50));
    closeButton.setPosition(windowSize.x - 120, MARGIN);
    
    closeButtonText.setFont(font);
    closeButtonText.setString("Close");
    closeButtonText.setCharacterSize(18);
    closeButtonText.setFillColor(sf::Color::White);
    sf::FloatRect closeBounds = closeButtonText.getLocalBounds();
    closeButtonText.setPosition(
        closeButton.getPosition().x + (closeButton.getSize().x - closeBounds.width) / 2,
        closeButton.getPosition().y + (closeButton.getSize().y - closeBounds.height) / 2
    );
    
    // Create buttons for each shader
    shaderButtons.clear();
    shaderLabels.clear();
    previewSprites.clear();
    
    for (size_t i = 0; i < availableShaders.size(); ++i) {
        // Button
        sf::RectangleShape button;
        button.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
        button.setPosition(calculateButtonPosition(i));
        button.setFillColor(sf::Color(60, 60, 60));
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color(100, 100, 100));
        shaderButtons.push_back(button);
        
        // Label
        sf::Text label;
        label.setFont(font);
        label.setString(availableShaders[i].displayName);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        
        sf::Vector2f buttonPos = button.getPosition();
        sf::FloatRect labelBounds = label.getLocalBounds();
        label.setPosition(
            buttonPos.x + PREVIEW_SIZE + 15,
            buttonPos.y + (BUTTON_HEIGHT - labelBounds.height) / 2
        );
        shaderLabels.push_back(label);
        
        // Preview sprite (placeholder for now)
        sf::Sprite preview;
        preview.setPosition(buttonPos.x + 10, buttonPos.y + 10);
        previewSprites.push_back(preview);
    }
}

void ShaderSelector::loadPreviewTextures() {
    // Try to load preview images for each shader
    for (size_t i = 0; i < availableShaders.size(); ++i) {
        std::string previewPath = "assets/previews/" + availableShaders[i].name + ".png";
        
        if (availableShaders[i].previewTexture.loadFromFile(previewPath)) {
            availableShaders[i].hasPreview = true;
            previewSprites[i].setTexture(availableShaders[i].previewTexture);
            
            // Scale to fit preview area
            sf::Vector2u textureSize = availableShaders[i].previewTexture.getSize();
            float scale = std::min(
                PREVIEW_SIZE / textureSize.x,
                PREVIEW_SIZE / textureSize.y
            );
            previewSprites[i].setScale(scale, scale);
        } else {
            // Create a simple placeholder rectangle
            availableShaders[i].hasPreview = false;
        }
    }
}

bool ShaderSelector::handleEvent(const sf::Event& event) {
    if (!isVisible) return false;
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            
            // Check close button
            if (closeButton.getGlobalBounds().contains(mousePos)) {
                hide();
                return true;
            }
            
            // Check shader buttons
            for (size_t i = 0; i < shaderButtons.size(); ++i) {
                if (isPointInButton(mousePos, i)) {
                    selectedIndex = i;
                    hide(); // Auto-close after selection
                    return true;
                }
            }
        }
    }
    
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        updateHover(mousePos);
    }
    
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            hide();
            return true;
        }
    }
    
    return true; // Consume all events when visible
}

void ShaderSelector::update(float deltaTime) {
    if (!isVisible) return;
    
    // Update any animations or effects here
}

void ShaderSelector::render() {
    if (!isVisible) return;
    
    // Draw background
    window->draw(background);
    
    // Draw title
    window->draw(titleText);
    
    // Draw close button
    window->draw(closeButton);
    window->draw(closeButtonText);
    
    // Draw shader buttons
    for (size_t i = 0; i < shaderButtons.size(); ++i) {
        // Highlight hovered button
        if (hoveredIndex == (int)i) {
            shaderButtons[i].setFillColor(sf::Color(80, 80, 80));
            shaderButtons[i].setOutlineColor(sf::Color::White);
        } else {
            shaderButtons[i].setFillColor(sf::Color(60, 60, 60));
            shaderButtons[i].setOutlineColor(sf::Color(100, 100, 100));
        }
        
        window->draw(shaderButtons[i]);
        window->draw(shaderLabels[i]);
        
        // Draw preview if available
        if (availableShaders[i].hasPreview) {
            window->draw(previewSprites[i]);
        } else {
            // Draw placeholder rectangle
            sf::RectangleShape placeholder;
            placeholder.setSize(sf::Vector2f(PREVIEW_SIZE, PREVIEW_SIZE));
            placeholder.setPosition(previewSprites[i].getPosition());
            placeholder.setFillColor(sf::Color(40, 40, 40));
            placeholder.setOutlineThickness(1);
            placeholder.setOutlineColor(sf::Color(80, 80, 80));
            window->draw(placeholder);
        }
    }
}

std::string ShaderSelector::getSelectedShaderName() const {
    if (selectedIndex >= 0 && selectedIndex < availableShaders.size()) {
        return availableShaders[selectedIndex].name;
    }
    return "";
}

std::string ShaderSelector::getSelectedFragmentPath() const {
    if (selectedIndex >= 0 && selectedIndex < availableShaders.size()) {
        return availableShaders[selectedIndex].fragmentPath;
    }
    return "";
}

std::string ShaderSelector::getSelectedVertexPath() const {
    if (selectedIndex >= 0 && selectedIndex < availableShaders.size()) {
        return availableShaders[selectedIndex].vertexPath;
    }
    return "";
}

std::string ShaderSelector::formatShaderName(const std::string& filename) {
    std::string formatted = filename;
    
    // Convert underscores to spaces
    std::replace(formatted.begin(), formatted.end(), '_', ' ');
    
    // Capitalize first letter of each word
    bool capitalizeNext = true;
    for (char& c : formatted) {
        if (capitalizeNext && std::isalpha(c)) {
            c = std::toupper(c);
            capitalizeNext = false;
        } else if (c == ' ') {
            capitalizeNext = true;
        }
    }
    
    return formatted;
}

sf::Vector2f ShaderSelector::calculateButtonPosition(int index) {
    sf::Vector2u windowSize = window->getSize();
    
    // Calculate grid layout
    int buttonsPerRow = (windowSize.x - 2 * MARGIN) / (BUTTON_WIDTH + BUTTON_SPACING);
    if (buttonsPerRow < 1) buttonsPerRow = 1;
    
    int row = index / buttonsPerRow;
    int col = index % buttonsPerRow;
    
    float startX = (windowSize.x - (buttonsPerRow * (BUTTON_WIDTH + BUTTON_SPACING) - BUTTON_SPACING)) / 2;
    float startY = 100; // Below title
    
    return sf::Vector2f(
        startX + col * (BUTTON_WIDTH + BUTTON_SPACING),
        startY + row * (BUTTON_HEIGHT + BUTTON_SPACING)
    );
}

bool ShaderSelector::isPointInButton(const sf::Vector2f& point, int buttonIndex) {
    if (buttonIndex < 0 || buttonIndex >= shaderButtons.size()) return false;
    return shaderButtons[buttonIndex].getGlobalBounds().contains(point);
}

void ShaderSelector::updateHover(const sf::Vector2f& mousePos) {
    hoveredIndex = -1;
    
    for (size_t i = 0; i < shaderButtons.size(); ++i) {
        if (isPointInButton(mousePos, i)) {
            hoveredIndex = i;
            break;
        }
    }
}