#include "managers/GameManager.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
    : renderer(nullptr), textureLoader(nullptr), fireShader(nullptr), initialized(false) {
}

GameManager* GameManager::Instance() {
    if (instance == nullptr) {
        instance = new GameManager();
    }
    return instance;
}

void GameManager::Release() {
    if (instance != nullptr) {
        delete instance->renderer;
        delete instance->textureLoader;
        // fireShader is now managed by main
        delete instance;
        instance = nullptr;
    }
}

bool GameManager::Initialize() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    // Initialize systems
    renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "Fire Shader");
    textureLoader = new TextureLoader();
    // fireShader will be set via SetFireShader
    
    // Configure renderer
    renderer->setFramerateLimit(60);
    
    // Fire shader initialization moved to main
    
    initialized = true;
    return true;
}

void GameManager::SetFireShader(FireShader* shader) {
    fireShader = shader;
}

void GameManager::SetFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner) {
    if (fireShader) {
        FireShader::FireColors colors;
        colors.outer = outer;
        colors.middle = middle;
        colors.inner = inner;
        fireShader->setColors(colors);
    }
}

void GameManager::SetAnimationSpeed(float speed) {
    if (fireShader) {
        fireShader->setAnimationSpeed(speed);
    }
}

void GameManager::Run() {
    if (!Initialize()) {
        std::cerr << "Failed to initialize GameManager!" << std::endl;
        return;
    }
    
    // Main game loop
    while (renderer->isOpen()) {
        HandleEvents();
        Update();
        Render();
    }
}

void GameManager::HandleEvents() {
    sf::RenderWindow& window = renderer->getWindow();
    
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        
        // Handle other events as needed
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }
    }
}

void GameManager::Update() {
    // Update game logic here
    static sf::Clock clock;
    [[maybe_unused]] float deltaTime = clock.restart().asSeconds();
    
    // Update animations, physics, etc.
    // deltaTime can be used for frame-independent movement
}

void GameManager::Render() {
    renderer->clear();
    
    // Render fire shader effect or other content
    if (fireShader) {
        // Apply shader and render
        // This is where you'd typically draw your fire effect
    }
    
    renderer->display();
}