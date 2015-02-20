#include "match.h"

//Constructors
Match::Match()
    :turn(WHITE)
{

}

Match::~Match()
{

}

void Match::toggleTurn()
{
    turn = !turn;
}

//Mutators
bool Match::getTurn()
{
    return this->turn;
}
