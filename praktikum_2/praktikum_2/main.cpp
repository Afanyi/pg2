#include <iostream>
#include "DungeonCrawler.h"

using namespace std;

int main()
{
    DungeonCrawler d = DungeonCrawler();
    d.turn();
    /*Character* c = new Character("c");
    Level l = Level();
    l.placeCharacter(c,4,4);
    l.printLevel();
    vector<pair<int,int>> positions;
    const string l = {
        "####"
        "#..#"
        "#.o#"
        "####"
    };
    int j = 0;
    int k;
    for(int i=0; i<=l.size(); i++){
        if (i % 4 == 0){
            j++;
            cout << endl;
        }
        k = i % 4;
        pair<int,int>pairPosition = {k,j};
        positions.push_back(pairPosition);
        cout << l[i];
    }
    //cout << l << endl;*/
    //cout << true << endl;
    return 0;
}
