/**************************************************************
*	  Purpose:  Returns the appropriate size the chessboard
*               should be.
*
*     Entry:    User has entered a game.
*
*     Exit:     The chessboard is set to the appropriate size.
****************************************************************/

function getBoardSize()
{
    if (!isLandscape())
        return getBackgroundWidth()
    else
        return getBackgroundHeight()
}

/******************************************************************
*	  Purpose:  Returns the height of each banner in the game
*               window. (Each player has a banner for info / Clock)
*
*     Entry:    User has entered a game.
*
*     Exit:     Each banner is set to the appropriate height.
*******************************************************************/

function getBannerHeight()
{
    if (!isLandscape())
        return (getBackgroundHeight() - getBackgroundWidth()) / 3
    else
        return getBackgroundHeight() / 2
}

/******************************************************************
*	  Purpose:  Returns the width of each banner in the game
*               window. (Each player has a banner for info / Clock)
*
*     Entry:    User has entered a game.
*
*     Exit:     Each banner is set to the appropriate width.
*******************************************************************/

function getBannerWidth()
{
    if (!isLandscape())
        return getBackgroundWidth()
    else
        return (getBackgroundWidth() - getBackgroundHeight()) / 2
}
