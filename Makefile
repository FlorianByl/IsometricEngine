LINK=-lsfml-graphics -lsfml-window -lsfml-system -std=c++11


all:TileMap TinyXML TMXParser Coord Tileset Stringutils main
	g++ *.o $(LINK)

main:main.cc
	g++ -c main.cc -o main.o $(LINK)

TileMap:TileMap.cc
	g++ -c TileMap.cc -o tilemap.o $(LINK)

TinyXML:tinyxml2.cpp
	g++ -c tinyxml2.cpp -o tinyxml.o $(LINK)

TMXParser:TMXParser.cc
	g++ -c TMXParser.cc -o tmxparser.o $(LINK)

Stringutils:StringUtils.cc
	g++ -c StringUtils.cc -o stringutils.o $(LINK)

Coord:Coord.cc
	g++ -c Coord.cc -o coord.o $(LINK)

Tileset:Tileset.cc
	g++ -c Tileset.cc -o tileset.o $(LINK)
