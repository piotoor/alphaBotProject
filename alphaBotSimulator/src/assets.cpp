#include "assets.h"

std::map<std::string, std::unique_ptr<sf::Texture>> assets::textures;

assets::assets()
{
    //ctor
}

assets::~assets()
{
    //dtor
}

sf::Texture* assets::getTexture(const std::string name)
{
    return textures[name].get();
}

void assets::loadTextures(std::string assetsFolder)
{
    assetsFolder.append("/");

    textures["car"] = std::make_unique<sf::Texture>();
    if (!textures["car"]->loadFromFile(assetsFolder + "car.png"))
    {
        std::cout << "wyjebalo texture" << std::endl;
    }
}
