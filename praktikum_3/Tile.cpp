#include "Tile.h"
#include "Character.h"

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

bool Tile::hasCharacter()
{
    if(character != nullptr){
        return true;
    }
    return false;
}
