#include "Tile.h"
#include "Character.h"
#include <iostream>

Character *Tile::getCharacter() const
{
    return character;
}

void Tile::setCharacter(Character *newCharacter)
{
    character = newCharacter;
}



int Tile::getRow() const
{
    return row;
}

int Tile::getColumn() const
{
    return column;
}

Tile::~Tile()
{

}
// initialising atributes
Tile::Tile(string texture, int row, int column) : texture(texture),
    character(nullptr),
    row(row),
    column(column)
{}

Tile &Tile::operator=(const Tile &t)
{
    texture = t.texture;
    row = t.row;
    column = t.column;
    return *this;
}

bool Tile::moveTo(Tile *destTile, Character *who)
{
    if (who == nullptr || destTile == nullptr) {
        std::cerr << "Error: Character or destination tile is null." << std::endl;
        return false;
    }
    Tile* currentTile = who->getTile();
    auto [enterResult, portalTile] = destTile->onEnter(who);
    if (portalTile != nullptr) {
        destTile = portalTile;
        std::cout << "Portal detected, moving to: "<< destTile->getRow() << ", " << destTile->getColumn() << std::endl;
    }
    if (currentTile != nullptr) {
        currentTile->setCharacter(nullptr);
    }

    destTile->setCharacter(who); // Place character on the destination tile
    who->setTile(destTile);      // Update the character's tile reference

    return true;
}
bool Tile::hasCharacter()
{
    if(character != nullptr){
        return true;
    }
    return false;
}
