import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow
{
    id: background
    width: 640
    height: 480
    visible: true    
    color: "#448ed3"

    Loading
    {

    }

    /**************************************************************
    *	  Purpose:  Get the background width of the app for all
    *               that need access to it.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the width of the application.
    ****************************************************************/

    function getBackgroundWidth()
    {
        return background.width
    }

    /**************************************************************
    *	  Purpose:  Get the background height of the app for all
    *               that need access to it.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the height of the application.
    ****************************************************************/

    function getBackgroundHeight()
    {
        return background.height
    }

    /**************************************************************
    *	  Purpose:  Get the smallest orientation for scalability
    *               purposes, whether it's the portrait or landscape
    *               orientation.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the smallest orientation of the
    *               application.
    ****************************************************************/

    function getSmallestOrientation()
    {
        return background.width < background.height ? background.width : background.height
    }
}
