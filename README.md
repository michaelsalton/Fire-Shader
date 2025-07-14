# TheRealSlimShader

A lightweight C++ material and shader support library built on top of SFML, designed to make shader management and material application simple and intuitive.

![slimshader](https://github.com/user-attachments/assets/e1d853fe-f8ec-4ae3-883a-02fda035e5cd)

## Overview

TheRealSlimShader provides a clean, object-oriented approach to working with shaders in SFML applications. Instead of manually managing shader uniforms and textures, TheRealSlimShader abstracts this complexity into reusable Material classes that can be easily applied to any drawable object.

## Key Features

- **Material System**: High-level abstraction for shaders with built-in parameter management
- **Modular Design**: Clean separation between rendering, texture loading, and shader management
- **Easy Integration**: Simple API that works seamlessly with existing SFML projects
- **Extensible**: Create custom materials by inheriting from the base Material class
- **Resource Management**: Automatic texture loading and caching system

## Architecture

TheRealSlimShader is built around several core components:

### Core Classes

- **Material**: Base class that wraps shaders with parameter management
- **Shader**: SFML shader wrapper with simplified uniform setting
- **TextureLoader**: Texture loading and caching system
- **Render**: Window management and rendering operations
- **RenderableObject**: Combines drawables with materials for easy rendering

### Specialized Materials

- **MFire**: Animated fire effect with customizable colors and parameters
- *More materials coming soon...*

## Quick Start

### Basic Setup

```cpp
#include "GameManager.h"
#include "MFire.h"

int main() {
    GameManager* game = GameManager::Instance();
    
    MFire* mFire = new MFire(&textureLoader);
    mFire->initialize();
    mFire->setFireColors(
        sf::Glsl::Vec4(1.0f, 0.2f, 0.1f, 1.0f),
        sf::Glsl::Vec4(1.0f, 0.6f, 0.0f, 1.0f),
        sf::Glsl::Vec4(1.0f, 1.0f, 0.0f, 1.0f)
    );
    
    game->SetMFire(mFire);
    game->Run();
    
    GameManager::Release();
    return 0;
}
```

### Creating Custom Materials

```cpp
class MWater : public Material {
private:
    float waveSpeed;
    float waveHeight;
    
public:
    MWater() {
        waveSpeed = 1.0f;
        waveHeight = 0.1f;
    }
    
    bool initialize() {
        if (!loadShader("shaders/vertex.glsl", "shaders/water.glsl")) {
            return false;
        }
        
        setFloat("wave_speed", waveSpeed);
        setFloat("wave_height", waveHeight);
        return true;
    }
    
    void update(float deltaTime) override {
        setFloat("time", clock.getElapsedTime().asSeconds());
        apply();
    }
};
```

### Applying Materials to Objects

```cpp
// Create your SFML drawable
sf::Sprite waterSprite(waterTexture);

// Create a renderable object with your custom material
RenderableObject waterObject(&waterSprite, mWater);

// In your game loop
waterObject.update(deltaTime);
waterObject.render(window);
```

## Building

### Prerequisites

- C++17 or later
- SFML 2.5+
- CMake (optional)

### Build Instructions

Using Make:
```bash
make clean
make
make run
```

Using CMake:
```bash
mkdir build
cd build
cmake ..
make
```

## Examples

Check out the `examples/` directory for:
- Basic fire effect setup
- Custom material creation
- Multi-object rendering
- Real-time parameter adjustment

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built on top of the excellent [SFML](https://www.sfml-dev.org/) library
- Inspired by modern game engine material systems
- Special thanks to the shader programming community for techniques and inspiration
