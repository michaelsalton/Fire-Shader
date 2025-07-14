#include "Core/GameManager.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
    : renderer(nullptr), textureLoader(nullptr), fireShader(nullptr), initialized(false) {
    Initialize();
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
        delete instance;
        instance = nullptr;
    }
}

bool GameManager::Initialize() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT, "TheRealSlimShader");
    textureLoader = new TextureLoader();
    
    renderer->setFramerateLimit(60);
        
    initialized = true;
    return true;
}

void GameManager::SetFireShader(FireShader* shader) {
    fireShader = shader;
    if (fireShader && !fireShader->initialize()) {
        std::cerr << "Warning: Failed to initialize fire shader" << std::endl;
    }
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
    if (!initialized) {
        std::cerr << "GameManager not initialized!" << std::endl;
        return;
    }
    
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
    static sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
}

void GameManager::Render() {
    renderer->clear(sf::Color::Black);
    
    if (fireShader) {
        fireShader->render(renderer->getWindow());
    }
    
    renderer->display();
}