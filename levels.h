#pragma once
#include <SFML\Graphics.hpp>
#include <string>
using namespace sf;
void setTileMap(int i, String text[]);
void setTileMapDefault();
String getTileMap(int i, int j);
void setTileMap(int i, std::string text[]);
extern String TileMap[12][20];