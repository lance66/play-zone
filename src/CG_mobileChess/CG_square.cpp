#include "CG_square.h"

//Default Constructor
CG_square::CG_square()
    : m_file(a), m_rank(1), m_piece(nullptr)
{

}

void CG_square::setFile(File file)
{
    m_file = file;
}

void CG_square::setRank(Rank rank)
{
    m_rank = rank;
}

void CG_square::setSquare(File file, Rank rank)
{
    this->setFile(file);
    this->setRank(rank);
}
