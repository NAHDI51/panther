// X11 libraries
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "def.h"
#include "window.h"
#include "color.h"

#include <stdlib.h>
#include <err.h>

//Extern variable definitions
XftColor* colorResources[COLOR_COUNT];
ColorCode colorCodes[COLOR_COUNT] = {
    [COLOR_BLACK]   = "#000000",
    [COLOR_WHITE]   = "#FFFFFF",
    [COLOR_BLUE]    = "#0000FF",
    [COLOR_GREEN]   = "#00FF00",
    [COLOR_RED]     = "#FF0000",
    [COLOR_YELLOW]  = "#FFFF00",
    [COLOR_CYAN]    = "#00FFFF",
    [COLOR_MAGENTA] = "#FF00FF"
};

const unsigned long COLOR_SEMIBLACK    = 0x7F7F7F;
const unsigned long COLOR_SEMISKYBLUE  = 0x87CEEB;

ColorButton colorButtons[COLOR_COUNT];


void createColor(
    XftColor* colorResource, 
    ColorCode colorCode
) {
    int okay = XftColorAllocName(
        disp,
        mainVisual,
        DefaultColormap(disp, screenNum),
        colorCode,
        colorResource
    );

    if(!okay) {
        errx(1, "Failed to allocate color: %s\n", colorCode);
        exit(1);
    }

    // printf("Successfully created color: %s\n", colorName);
    return;
}

void constructColorResources() {
    for(int i = 0; i < COLOR_COUNT; i++) {
        // They will be freed from the main header file upon termination.
        colorResources[i] = (XftColor*) malloc(sizeof(XftColor));
        createColor(colorResources[i], colorCodes[i]);
    }
    printf("Constructed the color resources.\n");
}

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
            .posx   = startX + (COLORBOX_PAD * (i+1)) + (COLORBOX_SIZE * (i)),
            .posy   = (COLORBOX_PAD),
            .width  = COLORBOX_SIZE,
            .height = COLORBOX_SIZE,
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
        .width  = toolbarWidth,
        .height = toolbarHeight,

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

void drawColorboxToolbar(Toolbar toolbar, GC graphicContent, Window win) {

    // Fill toolbar pixmap with background (white)
    XSetForeground(
        disp, 
        graphicContent, 
        COLOR_SEMIBLACK
    );

    XFillRectangle(
        disp, 
        toolbar.pixmap, 
        graphicContent, 
        0, 0, 
        toolbar.width, toolbar.height);

    for(int i = 0; i < COLOR_COUNT; i++) {
        XSetForeground(
            disp, 
            graphicContent, 
            colorButtons[i].code
        );

        // This creates circular buttons
        XFillArc(
            disp, 
            toolbar.pixmap,
            graphicContent,
            colorButtons[i].posx,
            colorButtons[i].posy,
            colorButtons[i].width,
            colorButtons[i].height,
            0, 
            360 * 64
        );

        // This is for square buttons
        /*
        XFillRectangle(
            disp, 
            toolbar.pixmap,
            graphicContent,
            colorButtons[i].posx,
            colorButtons[i].posy,
            colorButtons[i].width,
            colorButtons[i].height
        );
        */
        // printf("Drawn color button %d at pos (%d, %d)\n", 
        //        i, colorButtons[i].posx, colorButtons[i].posy
        // );
    }

    // Finally, copy from pixmap to win
    XCopyArea(
        disp,
        toolbar.pixmap,
        win,
        graphicContent,
        0, 0,
        toolbar.width, toolbar.height,
        // This places the toolbar on the bottom-left corner.
        // 2 so that the placement is slightly above the bottom edge.
        // COLORBOX_X_OFFSET, COLORBOX_Y_OFFSET

        // Much convenient
        toolbar.offsetX, toolbar.offsetY
    );
    printf("Made drawcolorboxtoolbar.\n");
}

int clickedColorButton(
    int mouseX,
    int mouseY,
    Toolbar colorbox
) {
    // CASE 1: -2 -> if outside colorbox.
    int startX = (WIDTH - colorbox.width) / 2;
    int endX   = startX + colorbox.width;
    int endY   = colorbox.offsetY + colorbox.height;

    if(mouseX < startX ||
       mouseX > endX   ||
       mouseY < colorbox.offsetY ||
       mouseY > endY) {
        return -2;  
    }

    // Translated Coordinates of the colorbox toolbar.
    int localX = mouseX - colorbox.offsetX;
    int localY = mouseY - colorbox.offsetY;

    // CASE 2: index if inside a color box.
    for(int i = 0; i < COLOR_COUNT; i++) {

        // Centers of the color Boxes.
        int cx = colorButtons[i].posx + colorButtons[i].width / 2;
        int cy = colorButtons[i].posy + colorButtons[i].height / 2;

        // Radius
        int r = colorButtons[i].width / 2;

        // Mouse position relative to the circle.
        int dx = localX - cx;
        int dy = localY - cy;

        // Within radius equation
        if(dx*dx + dy*dy - r*r <= 0) {
            return i;
        }
    }

    // CASE 3: -1 -> if inside colorbox but not on any button.
    return -1;
}

void destroyColorResources() {
    for(int i = 0; i < COLOR_COUNT; i++) {
        XftColorFree(
            disp,
            mainVisual,
            DefaultColormap(disp, screenNum),
            colorResources[i]
        );
        free(colorResources[i]);
    }
}