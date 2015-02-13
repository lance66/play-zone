#ifndef CG_PIECE_H
#define CG_PIECE_H

#include <QObject>
#include <QString>
enum Color { White, Black };
typedef int Rank;
enum File { a=1, b, c, d, e, f, g, h };

class CG_piece : public QObject
{
    Q_OBJECT

public:
    virtual bool move(File f_to, Rank r_to,
              File f_from, Rank r_from) = 0;
    virtual bool captured() = 0;

    CG_piece(Color pieceColor, QString pieceName) : m_pieceColor(pieceColor), m_pieceName(pieceName)
    {

    }

    QString getPieceName()
    {
        return m_pieceName;
    }

    Color getPieceColor()
    {
        return m_pieceColor;
    }

private:
    Color m_pieceColor;
    QString m_pieceName;
};

#endif // CG_PIECE_H
