#ifndef _TILESET_
#define _TILESET_

#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TMXParser.h"
#include "Coord.h"


namespace ISOENG
{
  namespace CORE
  {
    //Structure pour les tileset en collection d'images
    typedef struct
    {
      int id; //identifiant de la tile
      int width, height;  //Largeur et hauteur de l'image de la tile (px)
      std::string path; //Chemin vers l'image de la tile

      sf::Texture * texture; //Texture du tileset
    }S_DATAC;

    //Structure pour les tileset en une image
    typedef struct
    {
      int id_s, id_e; //Identifiant de première et de dernière tile
      int tile_width, tile_height;  //Largeur et hauteur des tiles (px)
      int tileset_width, tileset_height; //Largeur et hauteur du tileset (px)
      std::string path; //Chemin vers le tileset

      sf::Texture * texture;  //Texture du tileset
    }S_DATAU;

    class Tileset
    {
      private:
        ISOENG::UTILS::TMXParser * m_parserTMX; //Parseur du fichier de map
        std::vector<S_DATAC * > m_pictureCollection; //Liste des images tiles
        std::vector<S_DATAU * > m_pictureUnique;  //Liste des tileset

        S_DATAC * GetDataC(int tileNumber);
        S_DATAU * GetDataU(int tileNumber);
      public:
        Tileset(ISOENG::UTILS::TMXParser * parserTmx);
        sf::Texture * GetTexture(int tileNumber);
        sf::IntRect GetTextureCoordonate(int tileNumber);
        ISOENG::UTILS::Coord GetTileSize(int tileNumber);
    };

  }//CORE NAMESPACE
}//ISOENG NAMESPACE

#endif
