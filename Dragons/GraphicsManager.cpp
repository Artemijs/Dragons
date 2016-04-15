#include "GraphicsManager.h"
#include "Macros.h"
#include <iostream>
GraphicsManager* GraphicsManager::m_instance = 0;
GraphicsManager::GraphicsManager(){
	sf::Texture* t = new sf::Texture();
	if (!t->loadFromFile("square.png", sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT)))
	{
		std::cout<<"failed loading tile texture \n";
	}
	m_all_textures.push_back(t);
}
	

GraphicsManager::~GraphicsManager(){
	std::cout<<" deleting graphics manager \n";
	for (std::vector< sf::Texture * >::iterator it = m_all_textures.begin() ; it != m_all_textures.end(); ++it)
	{
		delete (*it);
	} 
	m_all_textures.clear();
}
GraphicsManager* GraphicsManager::instance(){
	if(m_instance == 0)
		m_instance = new GraphicsManager();
	return m_instance;
}
const sf::Texture* GraphicsManager::get_texture(TextureID texId){
	return m_all_textures[texId];
}