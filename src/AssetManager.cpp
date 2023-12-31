#include"AssetManager.h"



AssetManager* AssetManager::instance=nullptr;
// AssetManager manager;


AssetManager::AssetManager() //确保AssetManager只有一个实例
{
    assert(instance==nullptr);
    instance=this;
}

sf::Texture& AssetManager::getTexture(const std::string &filename) 
{
    auto& loadedTextures=instance->loadedTextures;
    auto check=loadedTextures.find(filename);
    if(check!=loadedTextures.end()) //若该资源已读取，则直接返回已读取的texture
    {
        return (*check).second;
    }
    else //若该资源未读取，则新建一个
    {
        auto& texture=loadedTextures[filename];
        if(!texture.loadFromFile(filename)) std::cout<<"fail to open"<<filename<<std::endl;
       // assert(texture.loadFromFile(filename)); 
        return texture;
    }
    
}

sf::SoundBuffer& AssetManager::getSoundbuffer(const std::string &filename) 
{
    auto& loadedSbuffers=instance->loadedSbuffers;
    auto check=loadedSbuffers.find(filename);
    if(check!=loadedSbuffers.end()) //若该资源已读取，则直接返回已读取的SoundBuffer
    {
        return (*check).second;
    }
    else //若该资源未读取，则新建一个
    {
        auto& sbuffer=loadedSbuffers[filename];
      //  assert(sbuffer.loadFromFile(filename));
       if(!sbuffer.loadFromFile(filename)) std::cout<<"fail to open "<<filename<<std::endl;
        return sbuffer;
    }
}

sf::Font& AssetManager::getFont(const std::string &filename) 
{
    auto& loadedFonts=instance->loadedFonts;
    auto check=loadedFonts.find(filename);
    if(check!=loadedFonts.end()) //若该资源已读取，则直接返回已读取的font
    {
        return (*check).second;
    }
    else //若该资源未读取，则新建一个
    {
        auto& font=loadedFonts[filename];
     //   assert(font.loadFromFile(filename));
        if(!font.loadFromFile(filename)) std::cout<<"fail to open "<<filename<<std::endl;
        return font;
    }
}

