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

class CG_square
{
public:
    // Default constructor
    CG_square();

    // Copy constructor
    CG_square(const CG_square & copy);

    // Mutators
    File getFile() const;
    Rank getRank() const;
    void setFile(File file);
    void setRank(Rank rank);
    void setSquare(File file, Rank rank);

    QString getPieceName() const;

    CG_piece * getPiece() const;

    void setPiece(CG_piece * piece = nullptr);

    void setPiece(CG_Color color, QString name);
    CG_square &operator=(const CG_square & rhs);

private:
    File m_file;
    Rank m_rank;

    CG_piece * m_piece;
};

#endif // CG_SQUARE_H
