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
    File getFile() const;
    Rank getRank() const;
    void setFile(File file);
    void setRank(Rank rank);
    void setSquare(File file, Rank rank);

    QString getPieceName() const;

    CG_piece * getPiece() const;

    void setPiece(CG_piece * piece);

    void setPiece(CG_Color color, QString name);

private:
    File m_file;
    Rank m_rank;

    CG_piece * m_piece;
};

#endif // CG_SQUARE_H
