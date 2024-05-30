#include "Level.h"
#include "Character.h"
#include <iostream>
using namespace std;

vector<vector<Tile *> > Level::getTiles() const
{
    return tiles;
}

void Level::setPortalSettings()
{
    /*
    Portal* p1 = new Portal("o",1,1);
    Portal* p2 = new Portal("o",7,1);
    tiles[1][1] = p1;
    tiles[7][1] = p1;*/

    // obtaning and storing the position of the portals
    Portal* p1 = static_cast<Portal*>(tiles[1][1]);
    Portal* p2 = static_cast<Portal*>(tiles[7][1]);

    //setting portal destinations
    p1->setDestination(p2);
    p2->setDestination(p1);
    portals.push_back(p1);
    portals.push_back(p2);
}

Level::Level() : width(10),height(10),tiles()
{

    const string l = {
                      "##########"
                      "#O.......#"
                      "#........#"
                      "#........#"
                      "#........#"
                      "#........#"
                      "##########"
                      "#O.......#"
                      "#........#"
                      "##########"
    };
    int row = -1;
    int column = 0;
    //initialising tiles with nullptr
    for(int i=0;i<width;i++){
        vector<Tile*> v;
        for(int j=0;j<height;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // creating tiles
    for(int i=0;i<l.size();i++){
        if (i % 10 == 0){
            row++;
        }
        column = (i%10);

        Tile * a = new Floor(".",1,1);
        if(l[i] == '.'){
            a = new Floor(".",row,column);
        }
        else if(l[i] == 'O'){
            a = new Portal("o",row,column);
        }
        else if(l[i] == '#'){
            a = new Wall("#",row,column);
        }
        tiles.at(row).at(column) = a;

    }
    // printing level
    for (int i=0;i<width;i++){
        for(int j=0; j<height; j++){
            cout << tiles[i][j]->getTexture();
        }
        cout << endl;
    }
    cout << endl;

}

Level::~Level()
{
    // deletin tiles from heap
    for (auto  v : tiles){
        for(auto t : v){
            delete t;
        }
    }

}

Tile *Level::getTile(int row, int col)
{
    /*for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(i==row && j == col){
                return tiles[i][j];
            }
        }
    }*/
    return tiles[row][col];
    //return nullptr;
}

void Level::placeCharacter(Character *c, int row, int col)
{
    Tile* theTile = getTile(row,col);
    c->setTile(theTile);
    theTile->setCharacter(c);
}

void Level::printLevel()
{
    for (int i=0;i<width;i++){
        for(int j=0; j<height; j++){
            cout << tiles[i][j]->getTexture();
        }
        cout << endl;
    }
    cout << endl;
}









