#include "CG_board.h"

CG_board::CG_board() : m_board()
{
    for ( int rank = 1; rank <= 8; rank++)
    {
        for ( int file = 1; file <= 8; file++)
        {
            //m_board[file][rank].SetFile(file);
            //m_board[file][rank].SetRow(row);

            if((rank % 2 == 1 && file % 2 == 1) ||
               (rank % 2 == 0 && file % 2 == 0))
            {
               // m_board[file][rank].SetColor(Black);
            }
            else
            {
                //m_board[file][rank].SetColor(White);
            }

            //m_board[file][rank].SetClicked(false);
        }
    }
}
