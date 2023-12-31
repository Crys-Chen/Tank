#ifndef ASSET
#define ASSET

#include<SFML\Audio.hpp>
#include<SFML\Graphics.hpp>
#include<map>
#include<assert.h>
#include<iostream>


//加入资源管理器AssetManager，以管理已读取的资源，确保好资源既不会被意外销毁，也不会被重复读取，提高安全性和运行效率。
class AssetManager
{
    public:
        AssetManager();
        static sf::Texture& getTexture(const std::string &filename);
        static sf::SoundBuffer& getSoundbuffer(const std::string &filename);
        static sf::Font& getFont(const std::string &filename);
        
    private:
        std::map<std::string, sf::Texture> loadedTextures;
        std::map<std::string, sf::SoundBuffer> loadedSbuffers;
        std::map<std::string, sf::Font> loadedFonts;
        static AssetManager* instance;

};


#endif