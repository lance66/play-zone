#ifndef CG_PIECE_H
#define CG_PIECE_H

#include <QObject>
#include <QString>


//Definitions
typedef enum CG_Color { WHITE = 0, BLACK } CG_Color;
typedef int Rank;
enum File { a=1, b, c, d, e, f, g, h };

class CG_piece : public QObject
{
    Q_OBJECT

public:
    //Constructors
    CG_piece(CG_Color pieceColor, QString pieceName);

    //Pure virtual methods
    virtual bool move(File f_to, Rank r_to, File f_from, Rank r_from) = 0;
    //virtual bool captured() = 0;

    //Mutators
    QString getPieceName();
    CG_Color getPieceColor();

private:
    CG_Color m_pieceColor;
    QString m_pieceName;
};

#endif // CG_PIECE_H
