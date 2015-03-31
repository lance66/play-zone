#ifndef CG_PIECE_H
#define CG_PIECE_H

#include <QObject>
#include <QString>

//Definitions
typedef enum CG_Color { WHITE = 0, BLACK } CG_Color;
typedef int Rank;
enum File { a=0, b, c, d, e, f, g, h };

class CG_piece : public QObject
{
    Q_OBJECT

public:
    //Constructors
    CG_piece(CG_Color pieceColor, QString pieceName);
    //CG_piece & operator=(CG_piece & rhs );

    //Virtual methods
    virtual bool move(File f_to, Rank r_to, File f_from, Rank r_from);
    virtual void UpdatePiece();

    //Mutators
    QString getPieceName() const;
    int getPieceColor() const;

    virtual void ToggleDirection();

private:
    CG_Color m_pieceColor;
    QString m_pieceName;

protected:
};

#endif // CG_PIECE_H
