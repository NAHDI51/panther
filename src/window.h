#ifndef __WINDOW_H
#define __WINDOW_H 1

/*
    inclusions
*/
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "def.h"    

/*
    Window properties
*/

typedef enum {
    POSX = 500,
    POSY = 500,
    WIDTH = 500,
    HEIGHT = 500,
    BORDER = 10,
} DefaultWindowProperties;

static Window createWindow(
    int x, // posX
    int y, // posY
    int w, // width
    int h, // height
    int b, // border
    unsigned long bgColor,
    unsigned long borderColor
);
/*
    @brief: Takes input of x,y,width,height, border, and 
    uses them to create a window
*/
Window takeWindowInput();

/*
    @brief: Creates a default window with predefined
    attributes.
*/
Window openDefaultWindow();

/*
    @brief: Sets the sizes within which the 
    window can be resized. 

    @details: 
        minWidth: Minimum width of the window
        minHeight: Minimum height of the window
        maxWidth: Maximum width of the window
        maxHeight: Maximum height of the window
    
        @ If maxWidth or maxHeight is set to 0,
        then there is no maximum limit on resizing

        @ If maxWidth < minWidth or maxHeight < minHeight,
        then the function will not set any maximum limits.

        @ If maxWidth == minWidth and maxHeight == minHeight,
        then the window will not be resizable.
*/

static void setWindowSizeHints(
    Window win, 
    int minWidth, int minHeight,
    int maxWidth, int maxHeight
);

/*
    @brief: Sets a fixed size for the window
*/
static void setFixedWindowSize(
    Window win, 
    int width, 
    int height
);



#endif // __WINDOW_H