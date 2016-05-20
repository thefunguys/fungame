#include "sfml.h"
#include "shadermanager.h"

sf::Shader* initGoShader() {
    sf::Shader* tmp = new sf::Shader;
    tmp->loadFromFile("shader.frag", sf::Shader::Fragment);
    return tmp;
}

sf::Shader* ShaderManager::goShader = initGoShader();
