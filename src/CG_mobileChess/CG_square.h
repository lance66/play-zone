#ifndef CG_SQUARE_H
#define CG_SQUARE_H

#include <QObject>
#include <QString>
#include "CG_piece.h"
#include "CG_rook.h"

class CG_square : public QObject
{
    Q_OBJECT
public:
    CG_square();
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

private:
    File m_file;
    Rank m_rank;
    CG_piece * m_piece;
};

#endif // CG_SQUARE_H
