#include <X11/X.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <stdbool.h>

#include "def.h"
#include "GC.h"
#include "window.h"
#include "color.h"
#include "colorbox.h"

void run(Window mainWindow, GC graphicContent, Toolbar colorbox) {
    XEvent event;
    int prevX = 0, prevY = 0;
    bool pointInit = false;
    bool clickedOnCanvas = false;

    /*
        Primary and secondary colors
        DEFAULT: BLACK and BLUE
    */
    unsigned long primaryColor   = colorResources[COLOR_BLACK]->pixel;
    unsigned long secondaryColor = colorResources[COLOR_BLUE]->pixel;

    drawColorboxToolbar(colorbox, graphicContent, mainWindow, primaryColor, secondaryColor);

    // printf("reached runGraphicContent\n");

    while(!(XNextEvent(disp, &event))) {
        // printf("Reached inside event loop\n");

        switch(event.type) {
            case ButtonPress:
                // printf("Reached button press\n");

                // If clicked on colorbox, change color, else do nothing.
                int clickedIndex = clickedColorButton(
                    event.xbutton.x,
                    event.xbutton.y,
                    colorbox
                );

                // Outside border implementation: draw

                int clickedButton = event.xbutton.button;

                if(clickedIndex == -2) {
                    /*
                        Only this case turns clickedOnCanvus to true.
                        All other options turn it to false.
                    */
                    clickedOnCanvas = true;

                    if(clickedButton == Button1) 
                        XSetForeground(disp, graphicContent, primaryColor);
            
                    else if(clickedButton == Button3) 
                        XSetForeground(disp, graphicContent, secondaryColor);
    
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                                event.xbutton.x, event.xbutton.y
                    );

                } 
                // Change color.
                // If -1 happens, don't do anything.
                else if(clickedIndex != -1) {

                    clickedOnCanvas = false;

                    // Change the color hexcode based on click.
                    if(clickedButton == Button1) 
                        primaryColor = colorButtons[clickedIndex].code;
                    
                    else if(clickedButton == Button3)
                        secondaryColor = colorButtons[clickedIndex].code;
                    
                    drawColorboxToolbar(
                        colorbox, graphicContent, mainWindow,
                        primaryColor, secondaryColor
                    );

                } else {
                    // -1
                    clickedOnCanvas = false;
                }

                break;

            
            case MotionNotify:
                // printf("Reached motion notify\n");

                // Do something only upon clickedOnCanvas, otherwise no need

                if(clickedOnCanvas) {
                    if(pointInit) {
                        XDrawLine(disp, event.xbutton.window, graphicContent,
                                prevX          , prevY,           /* From */
                                event.xbutton.x, event.xbutton.y  /* To */
                        );
                    } else {
                        XDrawPoint(disp, event.xbutton.window, graphicContent,
                                event.xbutton.x, event.xbutton.y
                        );
                        pointInit = true;
                    } 

                    prevX = event.xbutton.x;
                    prevY = event.xbutton.y;
                }

                break;
            
            case ButtonRelease:
                // printf("reached button release\n");
                pointInit = false;
                break;
            
            case Expose:
                // Redraw 
                drawColorboxToolbar(
                    colorbox, graphicContent, mainWindow,
                    primaryColor, secondaryColor
                );
                break;
            
            case KeyPress:
                // printf("reached button key press\n");
                if(XkbKeycodeToKeysym(disp, event.xkey.keycode, 0, 0) == XK_q) {
                    return; 
                }
                break;

        }

    }

}

int main() {
    constructDisplay();
    // Window mainWindow = takeWindowInput();
    Window mainWindow = openDefaultWindow();
    
    // GC graphicContent = takeGraphicContentInput(mainWindow);
    GC graphicContent = openDefaultGraphicContent(mainWindow);
    Toolbar colorbox = createColorboxToolbar(mainWindow);

    // Colorbox is usable for now.
    run(mainWindow, graphicContent, colorbox);
    destroyDisplay(&mainWindow, &graphicContent, &colorbox);

    return 0;
}