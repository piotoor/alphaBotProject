#include "assets.h"

std::map<std::string, sf::Texture*> assets::textures;

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
    return textures[name];
}

void assets::loadTextures(std::string assetsFolder)
{
    assetsFolder.append("/");

    textures["car"] = new sf::Texture();
    if (!textures["car"]->loadFromFile(assetsFolder + "car.png"))
    {
        std::cout << "wyjebalo texture" << std::endl;
    }
}


void assets::disposeTextures()
{
    for(auto it = textures.begin(); it != textures.end(); it++)
    {
        delete it->second;
    }
}
