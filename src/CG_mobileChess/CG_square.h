#ifndef CG_SQUARE_H
#define CG_SQUARE_H

#include <QObject>
#include <QString>

#include "CG_rook.h"
#include "CG_bishop.h"
#include "CG_queen.h"
#include "CG_king.h"
#include "CG_knight.h"
#include "CG_pawn.h"

#ifndef nullptr
#define nullptr 0
#endif

class CG_square : public QObject
{
    Q_OBJECT
public:
    //Default constructor
    CG_square();

    //Mutators
    File getFile();
    Rank getRank();
    void setFile(File file);
    void setRank(Rank rank);
    void setSquare(File file, Rank rank);

    QString getPieceName() const
    {
        QString temp_name = "";

        if(m_piece != 0)
        {
            temp_name = m_piece->getPieceName();
        }

        return temp_name;
    }
    CG_piece * getPiece() const
    {
        return m_piece;
    }

    void setPiece(CG_piece * piece)
    {
        m_piece = piece;
    }

    void setPiece(CG_Color color, QString name)
    {
        if ( m_piece != nullptr )
        {
            delete m_piece;
        }

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

private:
    File m_file;
    Rank m_rank;

    CG_piece * m_piece;
};

#endif // CG_SQUARE_H
