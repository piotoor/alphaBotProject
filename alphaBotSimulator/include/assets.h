#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include <memory>

class assets
{
    public:
        assets();
        virtual ~assets();
        static sf::Texture* getTexture(std::string name);
        static void loadTextures(const std::string assetsFolder);
        static void disposeTextures();

    protected:
        static std::map<std::string, std::unique_ptr<sf::Texture>> textures;

};

#endif // ASSETS_H
