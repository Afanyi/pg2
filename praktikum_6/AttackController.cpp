#include "AttackController.h"
#include <iostream>
#include <vector>

Level *AttackController::getLevel() const
{
    return level;
}

void AttackController::setLevel(Level *newLevel)
{
    level = newLevel;
}

Character *AttackController::getCharacter() const
{
    return character;
}

void AttackController::setCharacter(Character *newCharacter)
{
    character = newCharacter;
}

Character *AttackController::getZombie() const
{
    return zombie;
}

void AttackController::setZombie(Character *newZombie)
{
    zombie = newZombie;
}

AttackController::AttackController(Level *level, Character *character, Character *zombie)
    : level(level), character(character), zombie(zombie)
{}

Input AttackController::move() {
    std::cout << std::endl;
    //std::cout << " $$$Attacker move init" << std::endl;
    std::cout << std::endl;
    Position pos = {zombie->getTile()->getRow(), zombie->getTile()->getColumn()};
    Position destPos;
    if (character) {
        destPos = {character->getTile()->getRow(), character->getTile()->getColumn()};
    } else {
        destPos = {1, 1}; // Default position if character is not set
    }

    std::vector<Position> path = level->getPath(pos, destPos);

    if (path.empty() || path.size() < 2) {
        std::cout << "No valid path found or already at destination." << std::endl;
        return Input::still; // Stay still if no path is found or already at destination
    }

    //std::cout << "Attacker move path:" << std::endl;
    for (auto p : path) {
        std::cout << p.x << "  " << p.y << std::endl;
    }
    Position newPos = path[1];
    int y = newPos.x - pos.x;
    int x = newPos.y - pos.y;
    std::cout << std::endl;
    std::cout << " charecter at " << newPos.x <<" " << newPos.x << std::endl;
    std::cout << " zombie at " << pos.x <<" " << pos.x << std::endl;
    std::cout << "Attacker move delta: (" << x << ", " << y << ")" << std::endl;
    std::cout << std::endl;
    Input input = Input::still;
    if (x == 0 && y == 0) {
        input = Input::center;
    } else if (x == -1 && y == -1) {
        input = Input::upleft;
    } else if (x == 0 && y == -1) {
        input = Input::up;
    } else if (x == 1 && y == -1) {
        input = Input::upright;
    } else if (x == -1 && y == 0) {
        input = Input::left;
    } else if (x == 1 && y == 0) {
        input = Input::right;
    } else if (x == -1 && y == 1) {
        input = Input::downleft;
    } else if (x == 0 && y == 1) {
        input = Input::down;
    } else if (x == 1 && y == 1) {
        input = Input::downright;
    }
    std::cout << "Attacker move determined input: " << static_cast<int>(input) << std::endl;
    return input;
}
