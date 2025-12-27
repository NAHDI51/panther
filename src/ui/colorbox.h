#ifndef __COLORBOX_H
#define __COLORBOX_H 

/*
    inclusions
*/

#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include "../def.h"
#include "../window.h"

#include "../color.h"
#include "../shapes/circle.h"

/*
    Some additional color to handle other things.
*/

// 50% opacity black color.
extern const unsigned long COLOR_SEMIBLACK; 
// 50% opacity sky-blue
extern const unsigned long COLOR_SEMISKYBLUE;
// Overlay colors on click
extern const unsigned long COLOR_PRIMARY_OVERLAY;
extern const unsigned long COLOR_SECONDARY_OVERLAY;

/*
    @brief: Color box dimensions
*/
typedef enum {
    COLORBOX_SIZE   = 32,
    COLORBOX_PAD    = 12,
    COLORBOX_BORDER = 4,

    /*
        Mappings used in order to copy the toolbar pixmap to the
        main window.

        These coordinates are calculated using oddly specific ways
        and they will be used in order to make the buttonpress 
        functionality better.
    */

    COLORBOX_X_OFFSET = WIDTH/2 - 
                        ((COLOR_COUNT * COLORBOX_SIZE) + 
                        ((COLOR_COUNT + 1) * COLORBOX_PAD )) / 2,
    
    COLORBOX_Y_OFFSET = HEIGHT - ((COLORBOX_SIZE + (1*COLORBOX_PAD)) * 2)

} ColorBoxProperties;

/*
    @brief: For the menubar color option buttons.
*/
typedef struct {
    Circle button;
    unsigned long code;
} ColorButton;

// Initially support for only few colors defined.
extern ColorButton colorButtons[COLOR_COUNT];

// Constructs with proper xpox ypos and width heigth
void constructColorButtons();
void destroyColorButtons();

/*
    @brief: Checks whether the user has clicked on 
    the color button or not. 

    @return 
        -1 if no button is clicked, but within the colorbox 
        -2 if no button is clicked, and outside the colorbox
        else, returns the index of the color.

*/
int clickedColorButton(
    Point mouseP,
    Toolbar colorbox
);

/* 
    @brief: Simply creates the toolbar with appropriate dimensions.
    however, nothing is drawn on it yet.
*/
Toolbar createColorboxToolbar(Window win);

/* 
    @brief: now, it draws the colors onto the toolbar. 
    It sets up everything properly.
*/
void drawColorboxToolbar(
    Toolbar toolbar, 
    GC graphicContent,
    Window win,
    unsigned long primaryColor,
    unsigned long secondaryColor
);

#endif // __COLORBOX_H