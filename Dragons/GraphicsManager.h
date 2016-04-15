#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H
#include <vector>
#include "SFML\Graphics.hpp"
enum TextureID{
	TILE_TEXTURE
};
class GraphicsManager{
private:
	std::vector<sf::Texture*> m_all_textures;
	static GraphicsManager* m_instance;
	GraphicsManager();
	
public:
	~GraphicsManager();
	static GraphicsManager* instance();
	const sf::Texture* get_texture(TextureID texId);
};
#endif