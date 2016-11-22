#ifndef _TMXPARSEUR_
#define _TMXPARSEUR_

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "tinyxml2.h"
#include "StringUtils.h"

using namespace tinyxml2;

/*J'suis nervous breakdown*/

namespace ISOENG
{
  namespace UTILS
  {

    //MAP : Structure representant les information sur la balise map
    typedef struct{
      std::string version, orientation, renderorder;
      int width, height, tilewidth, tileheight, nextobjectid;
    }S_Map;

    //LAYER : Structure contenant les informations sur les couches de map
    typedef struct{
      std::string name;
      int width, height;

      std::vector<int> data;
    }S_Layer;

    //TILESET : Structure contenant les information du Tileset
    typedef struct{
      bool unique;  //Determine si tileset unique ou en collection images
      int firstgid; //Identifiant de la première tile
      std::string name; //Nom de tileset
      int tilewidth, tileheight;  //Largeur, hauteur d'une tile
      int tilecount;  //Nombre de tiles
      std::string tileset_path; //chemin vers tileset

      /* Si Collection images */
      std::vector<std::string> collectionPictures;  //chemin vers chaques img
      std::vector<int> collectionPictures_Width;  //Largeur image
      std::vector<int> collectionPictures_Height; //Hauteur image
      std::vector<int> collectionPictures_id; //Identifiant de la tile
    }S_Tileset;


    class TMXParser
    {
      private:


        S_Map * _map;
        std::vector< S_Layer * > _layers;
        std::vector<S_Tileset> _tilesets;

        bool Open(const char * path, XMLDocument &doc);
        void Parse_map(XMLDocument &doc);
        void Parse_tileset(XMLDocument &doc);
        void Parse_layers(XMLDocument &doc);
      public:
        bool Load(const char * path);

        std::vector<S_Tileset> GetTilesetData();
        std::vector<S_Layer *> GetLayersData();
        S_Map * GetMapData();

    };
  }
}

#endif
