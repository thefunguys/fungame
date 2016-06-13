#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include "sfml.h"

class ShaderManager {
  public:
    sf::Shader* goShader;
    sf::Shader* pShader;
    sf::Shader* whiteShader;
    sf::Shader* blurryShader;

    std::vector<sf::Shader*> shaders;
    static ShaderManager* instance();
  private:
    ShaderManager();
    static ShaderManager* inst;
    sf::Shader* initShader(std::string);
};


#endif
