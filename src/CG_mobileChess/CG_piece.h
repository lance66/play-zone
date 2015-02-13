#ifndef CG_PIECE_H
#define CG_PIECE_H

#include <QObject>
enum Color { White, Black };
typedef int Rank;
enum File { a=1, b, c, d, e, f, g, h };

class CG_piece : public QObject
{
    Q_OBJECT

public:
    virtual bool move(File f_to, Rank r_to,
              File f_from, Rank r_from) = 0;
    bool captured();
private:
    Color m_pieceColor;
};

#endif // CG_PIECE_H
