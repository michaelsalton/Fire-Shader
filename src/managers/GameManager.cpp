#include "GameManager.h"
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
        delete instance->fireShader;
        delete instance;
        instance = nullptr;
    }
}

bool GameManager::Initialize() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    
    // Initialize systems
    renderer = new Render(WINDOW_WIDTH, WINDOW_HEIGHT, "Fire Shader");
    textureLoader = new TextureLoader();
    fireShader = new FireShader(renderer, textureLoader, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Configure renderer
    renderer->setFramerateLimit(60);
    
    // Initialize fire shader
    if (!fireShader->initialize()) {
        std::cerr << "Failed to initialize fire shader!" << std::endl;
        return false;
    }
    
    initialized = true;
    return true;
}

void GameManager::SetFireColors(const sf::Glsl::Vec4& outer, const sf::Glsl::Vec4& middle, const sf::Glsl::Vec4& inner) {
    if (fireShader) {
        fireShader->setFireColors(outer, middle, inner);
    }
}

void GameManager::SetAnimationSpeed(float speed) {
    if (fireShader) {
        fireShader->setAnimationSpeed(speed);
    }
}

void GameManager::Run()