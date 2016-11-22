#include "TileMap.h"

TileMap::TileMap()
{
  m_texture = new sf::Texture();
}

bool TileMap::Load(const char * tmxFile)
{

  LoadData(tmxFile);
  // CreateMap();
  return true;
}

void TileMap::LoadData(const char * file)
{
  
  m_parser = new ISOENG::UTILS::TMXParser();
  if(!m_parser->Load(file))
    exit(-1);

  m_tileset = new ISOENG::CORE::Tileset(m_parser);

  m_map = m_parser->GetMapData();
  m_layers = m_parser->GetLayersData();
  // m_tileset = m_parser->get_tilesets();


}

void TileMap::CreateMap()
{
  std::cout << "Nombre de calques : " << m_layers.size() << std::endl;
  for(int i = 0 ; i < m_layers.size(); ++i)
  {
    //Recuperation du Layer et des données liées a la taille de la map
    ISOENG::UTILS::S_Layer * CurrentLayer = m_layers[i];
    ISOENG::UTILS::Coord MapSize(CurrentLayer->width, CurrentLayer->height);

    //Parcour de la map
    for(int x = 0; x < MapSize.x; ++x)
    {
      for(int y = 0; y < MapSize.y; ++y)
      {
        //Sprite édité pour ce tour de boucle
        sf::Sprite CurrentSprite;
        int TileNumber = CurrentLayer->data[x + (y * MapSize.x)];

        //Position le sprite
        ISOENG::UTILS::Coord SpritePosition(x, y);
        SpritePosition = SpritePosition.ToIso(ISOENG::UTILS::Coord(m_map->tilewidth, m_map->tileheight));
        CurrentSprite.setPosition(SpritePosition.x / 2, SpritePosition.y / 2);

        //Nouvelle recuperation texture
        sf::Texture * currentTexture = m_tileset->GetTexture(TileNumber);

        //Cible et applique la texture
        if(TileNumber != 0)
          CurrentSprite.setTexture(*currentTexture);
        CurrentSprite.setTextureRect(m_tileset->GetTextureCoordonate(TileNumber));

        //Application de parametre autres sur le sprite


        //On ajoute le sprite au vecteur
        m_sprites.push_back(CurrentSprite);

      }
    }
  }

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  //Applique la transformation
  states.transform *= getTransform();


  //Applique la texture du ts
  // states.texture = m_texture;




  //Dessine la map
  for(int i = 0 ; i < m_sprites.size(); ++i)
  {
    target.draw(m_sprites[i], states);
  }

}
