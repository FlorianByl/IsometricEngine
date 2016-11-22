#ifndef _TILEMAP_
#define _TILEMAP_

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "TMXParser.h"
#include "Tileset.h"
#include "Coord.h"

typedef struct
{
  int id;
  sf::Texture texture;
  int width, height;
}Tile;

class TileMap : public sf::Drawable, public sf::Transformable
{
  private:

    ISOENG::UTILS::TMXParser * m_parser;

    /* TMX DATA */
    ISOENG::UTILS::S_Map * m_map;
    std::vector< ISOENG::UTILS::S_Layer * > m_layers;

    /* DATA MAP */
    ISOENG::CORE::Tileset * m_tileset;

    sf::Texture * m_texture;
    std::vector<sf::Sprite> m_sprites;

    void LoadData(const char * file);
    void CreateMap();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  public:
    TileMap();
    bool Load(const char * tmxFile);

};

#endif
