
#include <iostream>
#include <SFML/Graphics.hpp>

#include "TileMap.h"

// #include "tinyxml2.h"

bool Test();

int main(int argc, char const *argv[])
{
  // if(!sf::Shader::isAvailable())
  //   exit(-1);


  //SHADER
  // sf::Shader shader;
  // if(!shader.loadFromFile("outline.frag", sf::Shader::Fragment))
  // {
  //   std::cerr << "Shader not load" << std::endl;
  //   exit(-1);
  // }
  //
  // shader.setParameter("border_width", 1.0f);
  // shader.setParameter("aspect", 1.0f);
  // shader.setParameter("texCoord", sf::Vector2f(50.0, 50.0));


  std::cout << "HERE" << std::endl;
  TileMap  * tilemap = new TileMap();
  // if(!tilemap.Load("roadTiles.png",sf::Vector2f(172,110), map, 10 , 5))
  if(!tilemap->Load("Assets/map_4.tmx"))
    return -1;



  sf::RenderWindow window(sf::VideoMode(1280,720), "Test");
  sf::View view = window.getView();
  view.setCenter(view.getCenter().x - view.getCenter().x, view.getCenter().y - (view.getCenter().y / 2 ));
  view.setSize(896,504);
  window.setView(view);

  window.setFramerateLimit(30);
  while(window.isOpen())
  {
    /** Gestion des entrées **/
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }



    /** ESSAIS **/
    sf::Color Sky_color;
    Sky_color.r = 116;
    Sky_color.g = 208;
    Sky_color.b = 241;
    window.clear(Sky_color);

    // sf::VertexArray triangle(sf::Quads, 4);
    //
    // triangle[0].position = sf::Vector2f(10,10);
    // triangle[1].position = sf::Vector2f(100,10);
    // triangle[2].position = sf::Vector2f(100,100);
    // triangle[3].position = sf::Vector2f(10,100);
    //
    // triangle[0].color = sf::Color::Red;
    // triangle[1].color = sf::Color::Blue;
    // triangle[2].color = sf::Color::Green;
    // triangle[3].color = sf::Color::Yellow;
    // tilemap.setRotation(45.0f);

    window.draw(*tilemap);

    window.display();



  }



  return 0;
}


bool Test()
{
  tinyxml2::XMLDocument xml_doc;

  tinyxml2::XMLError eResult = xml_doc.LoadFile("Assets/map.tmx");
  if (eResult != tinyxml2::XML_SUCCESS) return false;

  tinyxml2::XMLNode* root = xml_doc.FirstChildElement("map");
  if (root == nullptr) return false;

  tinyxml2::XMLElement* element = root->FirstChildElement("tileset");
  if (element == nullptr) return false;

  std::cout << "TEST" << element->Attribute("source") << std::endl;

  return true;
}
