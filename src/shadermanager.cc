#include <stdio.h>
#include "sfml.h"
#include "shadermanager.h"

ShaderManager* ShaderManager::inst;

sf::Shader* ShaderManager::initShader(std::string shader) {
    sf::Shader* tmp = new sf::Shader;

    if (!tmp->loadFromFile(shader, sf::Shader::Fragment)) {
        printf("failed to load shader %s\n", shader.c_str());
        tmp = nullptr;
    }
    shaders.push_back(tmp);
    return tmp;
}

ShaderManager::ShaderManager() {
    goShader = initShader("shaders/goshader.frag");
    pShader = initShader("shaders/pshader.frag");
}

ShaderManager* ShaderManager::instance() {
    if (ShaderManager::inst == nullptr) {
        ShaderManager::inst = new ShaderManager;
    }
    return ShaderManager::inst;
}
