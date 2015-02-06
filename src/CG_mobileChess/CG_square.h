#ifndef CG_SQUARE_H
#define CG_SQUARE_H

#include <QObject>

#include "CG_define.h"

//typedef int Rank;

//enum File { a = 1, b, c, d, e, f, g, h };
//enum Color { White, Black };

class CG_square : public QObject
{
public:
    CG_square();
private:
    File m_file;
    Rank m_rank;
    Color m_color;
    bool m_clicked;
};

#endif // CG_SQUARE_H
