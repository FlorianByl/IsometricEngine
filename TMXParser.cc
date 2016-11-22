#include "TMXParser.h"
using namespace ISOENG::UTILS;

bool TMXParser::Load(const char * path)
{
  XMLDocument doc;

  //Ouverture du fichier XML et contrôle d'erreur
  if(!Open(path, doc))
    return false;

  _map = new S_Map();

  Parse_map(doc);
  Parse_tileset(doc);
  Parse_layers(doc);



  return true;
}

/*!
   \brief Try to open XML File
   \param Path : Path to XML File
   \param doc  : odc if open succes
   \return Result of oppening
*/
bool TMXParser::Open(const char * path, XMLDocument &doc)
{
  //Ouverture du fichier XML et contrôle d'erreur
  XMLError eResult = doc.LoadFile(path);
  if(eResult != XML_SUCCESS)
    return false;

  return true;
}

/*!
   \brief analyse the S_Map node and extract all attrib
   \param doc :  Document node
*/
void TMXParser::Parse_map(XMLDocument &doc)
{
  XMLNode * root = doc.FirstChildElement("map");
  if(root == nullptr)
    exit(-1);

  XMLElement * element = root->ToElement();
  _map->version = element->Attribute("version");
  _map->orientation = element->Attribute("orientation");
  _map->renderorder = element->Attribute("renderorder");


  _map->width = atoi(element->Attribute("width"));
  _map->height = atoi(element->Attribute("height"));
  _map->tilewidth = atoi(element->Attribute("tilewidth"));
  _map->tileheight = atoi(element->Attribute("tileheight"));
  // _map->nextobjectid = atoi(element->Attribute("nextobjectid"));

}


void TMXParser::Parse_tileset(XMLDocument &doc)
{
  XMLNode * root = doc.FirstChildElement("map");
  if(root == nullptr)
    exit(-1);

  //Parcour tous les tileset presents dans le TMX
  XMLElement * element;
  for(element = root->FirstChildElement("tileset"); element; element = element->NextSiblingElement("tileset"))
  {
    //Creation d'une structure tileset temporaire
    S_Tileset current_ts;

    //Remplit la structure temporaire
    current_ts.firstgid = atoi(element->Attribute("firstgid")); //FIRST ID DS LE TS
    // current_ts.tilecount = atoi(element->Attribute("tilecount")); //Nb TILES
    current_ts.tilewidth = atoi(element->Attribute("tilewidth"));//Tile width
    current_ts.tileheight = atoi(element->Attribute("tileheight"));//Tile height

    //Verifie s'il y a des enfant se nommant tile
    XMLElement * tile = element->FirstChildElement("tile");
    if(tile == nullptr) //Si non, alors il s'agit d'un tileset unique
      current_ts.unique = true;
    else  //Sinon il s'agit d'une collection d'images
      current_ts.unique = false;

    //Si tileset unique alors on recupère juste la source du tileset
    if(current_ts.unique)
      current_ts.tileset_path = element->FirstChildElement("image")->Attribute("source");//Chemin vers le tileset
    else{ //Sinon on analyse chaque tile (image individuelle)
      for(tile = element->FirstChildElement("tile"); tile; tile = tile->NextSiblingElement("tile"))
      {
        XMLElement * image = tile->FirstChildElement("image");

        //Chemin vers image courante
        current_ts.collectionPictures.push_back(image->Attribute("source"));
        //Largeur image courante
        current_ts.collectionPictures_Width.push_back(atoi(image->Attribute("width")));
        //Hauteur image courante
        current_ts.collectionPictures_Height.push_back(atoi(image->Attribute("height")));
        //Identifiant de l'image courante
        current_ts.collectionPictures_id.push_back(atoi(tile->Attribute("id")));
      }
    }

    //Sauvegarde la structure temporaire S_Tileset dans la structure de la l'instance
    _tilesets.push_back(current_ts);
  }

}


void TMXParser::Parse_layers(XMLDocument &doc)
{
  XMLNode * root = doc.FirstChildElement("map");
  if(root == nullptr)
    exit(-1);

  XMLElement * layer;

  //Parse le layer courant
  for(layer = root->FirstChildElement("layer"); layer; layer = layer->NextSiblingElement("layer"))
  {
    S_Layer * current_layer = new S_Layer();

    current_layer->name = layer->Attribute("name");
    current_layer->width = atoi(layer->Attribute("width"));
    current_layer->height = atoi(layer->Attribute("height"));

    XMLElement * current_data = layer->FirstChildElement("data");


    std::vector<std::string> data_expl = utils::StringUtils::explode(current_data->GetText(), ",");
    std::vector<int> data_ok;
    for(int i = 0 ; i< data_expl.size(); ++i)
      data_ok.push_back(atoi(data_expl[i].c_str()));

    /*
      current_layer : Stock les information general du layer
      data_ok : Tableau a 1 dimension qui contient les données du layer
    */
    current_layer->data = data_ok;
    _layers.push_back(current_layer);

  }
}

std::vector<S_Tileset> TMXParser::GetTilesetData()
{
  return _tilesets;
}

std::vector<S_Layer *> TMXParser::GetLayersData()
{
  return _layers;
}

S_Map * TMXParser::GetMapData()
{
  return _map;
}
