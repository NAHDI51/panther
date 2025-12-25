// X11 libraries
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "def.h"
#include "window.h"
#include "color.h"
#include "colorbox.h"
#include "GC.h"
#include "GC_snapshot.h"

#include "shapes/shapes.h"

#include <stdlib.h>
#include <stdbool.h>
#include <err.h>


const unsigned long COLOR_SEMIBLACK         = 0x7F7F7F;
const unsigned long COLOR_SEMISKYBLUE       = 0x87CEEB;
const unsigned long COLOR_PRIMARY_OVERLAY   = 0x404040;
const unsigned long COLOR_SECONDARY_OVERLAY = 0x202020;

ColorButton colorButtons[COLOR_COUNT];


void constructColorButtons() {
    /*
        Center Alignment of color buttons in the toolbar
    */
   /*
    Another idea: maybe I can copy to display in this coordinate
    and create the main thing as a simple left-aligned toolbar.

    Advantage: Calculation is simpler, and I can now use fixed width 
    for the toolbar instead of full width.
   */
  /*
    int startX = WIDTH/2 - 
                 ((COLOR_COUNT * COLORBOX_SIZE) + 
                ( (COLOR_COUNT + 1) * COLORBOX_PAD )) / 2;
    */
    int startX = 0;

    for(int i = 0; i < COLOR_COUNT; i++) {
        /*
            posx: overall how many buttons covered + how many buttons padded
        */
        colorButtons[i] = (ColorButton) {
            .button = createCircle(
                        createPoint(
                            startX + ((COLORBOX_PAD) * (i+1)) + (COLORBOX_SIZE * i), 
                            COLORBOX_PAD
                        ),
                        COLORBOX_SIZE, COLORBOX_SIZE,
                        COLORBOX_BORDER
                    ),
            .code   = colorResources[i]->pixel    // Red, green, blue etc
        }; 
    }
}

void destroyColorButtons() {
    for(int i = 0; i < COLOR_COUNT; i++) {
        // No dynamic memory allocated inside ColorButton struct
        // So, nothing to free here for now.
    }
}

/* 
    @brief: Simply creates the toolbar with appropriate dimensions.
    however, nothing is drawn on it yet.
*/

Toolbar createColorboxToolbar(Window win) {
    int toolbarWidth  = (COLORBOX_SIZE * COLOR_COUNT) +
                        ((COLORBOX_PAD * (COLOR_COUNT + 1)));
    // int toolbarWidth  = WIDTH;  // Full width toolbar

    int toolbarHeight = COLORBOX_SIZE + (2*COLORBOX_PAD);

    Toolbar bar = (Toolbar) {
        .bar = createRectangle(
                   createPoint(0, 0),
                   toolbarWidth, toolbarHeight,
                   COLORBOX_BORDER
                ),

        .offsetX = COLORBOX_X_OFFSET,
        .offsetY = COLORBOX_Y_OFFSET,

        .pixmap = XCreatePixmap (
            disp,
            win,
            toolbarWidth,
            toolbarHeight,
            DefaultDepth(disp, screenNum)
        )
    };
    
    return bar;
}

void drawColorboxToolbar(
    Toolbar toolbar, 
    GC graphicContent, 
    Window win,
    unsigned long primaryColor,
    unsigned long secondaryColor 
) {

    GCSnapshot toolbarColorSnap = gcSetForeground(graphicContent, COLOR_SEMIBLACK);
    drawRectangle(toolbar.pixmap, graphicContent, toolbar.bar, false);
    gcRestore(graphicContent, toolbarColorSnap);

    for(int i = 0; i < COLOR_COUNT; i++) {
        unsigned long curColor = colorButtons[i].code;

        /*
            Check for primary and secondary colors.
        */
        bool primaryOrSecondary = false;
        GCSnapshot overlayColorSnap;

        if(curColor == primaryColor) {
            overlayColorSnap = gcSetForeground(graphicContent, COLOR_PRIMARY_OVERLAY);
            primaryOrSecondary |= true;

        }
        else if(curColor == secondaryColor) {
            overlayColorSnap = gcSetForeground(graphicContent, COLOR_SECONDARY_OVERLAY);
            primaryOrSecondary |= true;
        }
        if(primaryOrSecondary) {
            drawCircle(
                toolbar.pixmap, graphicContent, 
                colorButtons[i].button, true
            );
            gcRestore(graphicContent, overlayColorSnap);
        }

        // Finally, fill normal colors.
        GCSnapshot buttonColorSnap = gcSetForeground(graphicContent, curColor);
        drawCircle(
            toolbar.pixmap, graphicContent, 
            colorButtons[i].button, false
        );
        gcRestore(graphicContent, buttonColorSnap);
    }

    // Finally, copy from pixmap to win
    XCopyArea(
        disp,
        toolbar.pixmap,
        win,
        graphicContent,
        toolbar.bar.p.posX, toolbar.bar.p.posY,
        toolbar.bar.width, toolbar.bar.height,
        // This places the toolbar on the bottom-left corner.
        // 2 so that the placement is slightly above the bottom edge.
        // COLORBOX_X_OFFSET, COLORBOX_Y_OFFSET

        // Much convenient
        toolbar.offsetX, toolbar.offsetY
    );
    // printf("Made drawcolorboxtoolbar.\n");
}

int clickedColorButton(
    Point mouseP,
    Toolbar colorbox
) {

    // Translated Coordinates of the colorbox toolbar.
    Point localP = createPoint(
        mouseP.posX - colorbox.offsetX,
        mouseP.posY - colorbox.offsetY
    );
    // CASE 1: -2 -> if outside colorbox.
    if(!pointInsideRectangle(localP, colorbox.bar))
        return -2;
    // CASE 2: index if inside a color box.
    for(int i = 0; i < COLOR_COUNT; i++) {
        if(pointInsideCircle(localP, colorButtons[i].button))
            return i;
    }

    // CASE 3: -1 -> if inside colorbox but not on any button.
    return -1;
}