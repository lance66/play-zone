#ifndef CG_SQUARE_H
#define CG_SQUARE_H

#include <QObject>
#include "CG_piece.h"
//typedef int Rank;
//enum File { a=1, b, c, d, e, f, g, h };

class CG_square : public QObject
{
    Q_OBJECT
public:
    CG_square();
private:
    File m_file;
    Rank m_rank;
    bool m_clicked;
    CG_piece * m_piece;
};

#endif // CG_SQUARE_H
