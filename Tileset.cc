#include "Tileset.h"
using namespace ISOENG::CORE;

Tileset::Tileset(ISOENG::UTILS::TMXParser * parserTmx)
{
  //Verification du pointeur
  if(parserTmx != nullptr)
    m_parserTMX = parserTmx;
  else{
    std::cerr << "Error TMXFile" << std::endl;
    exit(-1);
  }

  //Recuperation des informations issu du parser
  std::vector<ISOENG::UTILS::S_Tileset> TMX_Tilesets = m_parserTMX->GetTilesetData();

  for(int i = 0; i < TMX_Tilesets.size(); ++i)
  {
    //Controle s'il s'agit d'une collection d'images ou d'un tileset unique
    if(TMX_Tilesets[i].unique) //Si Tileset unique
    {
        S_DATAU * datau;
        datau->id_s = TMX_Tilesets[i].firstgid;
        datau->id_e = TMX_Tilesets[i].tilecount - datau->id_s;
        datau->tile_width = TMX_Tilesets[i].tilewidth;
        datau->tile_height = TMX_Tilesets[i].tileheight;

        datau->path = TMX_Tilesets[i].tileset_path;
        datau->texture = new sf::Texture();
        datau->texture->loadFromFile(datau->path);

        datau->tileset_width = datau->texture->getSize().x;
        datau->tileset_height = datau->texture->getSize().y;

        m_pictureUnique.push_back(datau);
    }
    else{ //Tileset en collection d'images
      for(int j = 0; j < TMX_Tilesets[i].collectionPictures.size(); ++j)
      {
        S_DATAC * datac = new S_DATAC();
        datac->id =TMX_Tilesets[i].collectionPictures_id[j];
        datac->width = TMX_Tilesets[i].collectionPictures_Width[j];
        datac->height = TMX_Tilesets[i].collectionPictures_Height[j];
        datac->path = TMX_Tilesets[i].collectionPictures[j];

        datac->texture = new sf::Texture();
        datac->texture->loadFromFile(datac->path);

        m_pictureCollection.push_back(datac);
      }
    }
  }
}

S_DATAC * Tileset::GetDataC(int tileNumber)
{
  for(int i = 0 ; i < m_pictureCollection.size(); ++i)
  {
    if(tileNumber = m_pictureCollection[i]->id)
    return m_pictureCollection[i];
  }

  return NULL;
}
S_DATAU * Tileset::GetDataU(int tileNumber)
{
  for(int i = 0 ; i < m_pictureUnique.size(); ++i)
  {
    if(tileNumber >= m_pictureUnique[i]->id_s && tileNumber <= m_pictureUnique[i]->id_e)
    return m_pictureUnique[i];
  }

  return NULL;
}

sf::Texture * Tileset::GetTexture(int tileNumber)
{
  if(GetDataC(tileNumber) != NULL)
    return GetDataC(tileNumber)->texture;
  if(GetDataU(tileNumber) != NULL)
    return GetDataU(tileNumber)->texture;


  return NULL;
}

sf::IntRect Tileset::GetTextureCoordonate(int tileNumber)
{
  ISOENG::UTILS::Coord TextureSize;
  TextureSize.x = GetTexture(tileNumber)->getSize().x;
  TextureSize.y = GetTexture(tileNumber)->getSize().y;

  ISOENG::UTILS::Coord TileSize = GetTileSize(tileNumber);

  ISOENG::UTILS::Coord TextureCoord;
  TextureCoord.x = tileNumber % (TextureSize.x / TileSize.x);
  TextureCoord.y = tileNumber / (TextureSize.x / TileSize.x);

  return sf::IntRect((TextureCoord.x - 1) * TileSize.x, TextureCoord.y * TileSize.y, TileSize.x, TileSize.y);


}


ISOENG::UTILS::Coord Tileset::GetTileSize(int tileNumber)
{
  ISOENG::UTILS::Coord retour;

  if(GetDataC(tileNumber) != NULL){
    retour.x = GetDataC(tileNumber)->width;
    retour.y = GetDataC(tileNumber)->height;
  }
  if(GetDataU(tileNumber) != NULL){
    retour.x = GetDataU(tileNumber)->tile_width;
    retour.y = GetDataU(tileNumber)->tile_height;
  }

  return retour;
}
