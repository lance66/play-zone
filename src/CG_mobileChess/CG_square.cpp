#include "CG_square.h"

//Default Constructor
CG_square::CG_square()
    : m_file(a), m_rank(1), m_piece(nullptr)
{

}

//Sets the CG_square's File.
void CG_square::setFile(File file)
{
    m_file = file;
}

//Sets the CG_square's Rank.
void CG_square::setRank(Rank rank)
{
    m_rank = rank;
}

//Sets the CG_square's File and Rank.
void CG_square::setSquare(File file, Rank rank)
{
    this->setFile(file);
    this->setRank(rank);
}

//Returns the name of the CG_piece in the CG_square.
//If the pointer is null, it returns an empty string.
QString CG_square::getPieceName() const
{
    QString temp_name = "";

    if(m_piece != 0)
    {
        temp_name = m_piece->getPieceName();
    }

    return temp_name;
}

//Returns the pointer to the CG_piece in CG_square.
CG_piece * CG_square::getPiece() const
{
    return m_piece;
}

//This sets the CG_piece pointer to that of another pointer.
void CG_square::setPiece(CG_piece * piece)
{
    m_piece = piece;
}

//This sets the CG_piece pointer based on a CG_Color and QString.
//Of the two setPiece's, this one's purpose is to actually allocate
//the data for that particular piece.
void CG_square::setPiece(CG_Color color, QString name)
{
    if ( m_piece != nullptr )
    {
        delete m_piece;
    }

    //Depending on the piece name, this makes the pointer
    //become a particular piece with the specified color.
    if ( name == "Pawn" )
    {
        m_piece = new CG_pawn(color);
    }
    else if ( name == "Rook" )
    {
        m_piece = new CG_rook(color);
    }
    else if ( name == "Knight" )
    {
        m_piece = new CG_knight(color);
    }
    else if ( name == "Bishop" )
    {
        m_piece = new CG_bishop(color);
    }
    else if ( name == "Queen" )
    {
        m_piece = new CG_queen(color);
    }
    else
    {
        m_piece = new CG_king(color);
    }
}


File CG_square::getFile() const
{
    return m_file;
}
Rank CG_square::getRank() const
{
    return m_rank;
}

CG_square &CG_square::operator=(const CG_square & rhs)
{
    //Check for self-assignment
    if(this != &rhs)
    {
        CG_piece ** temp = nullptr;

        //Delete old data
        delete [] m_piece;

        //Make deep copy of new data
        m_file = rhs.m_file;
        m_rank = rhs.m_rank;

        temp = new CG_piece *[sizeof rhs];
         m_piece = *temp;
    }

    //Return self-invoking object
    return *this;
}
