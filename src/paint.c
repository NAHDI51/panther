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

void run(GC graphicContent) {
    XEvent event;
    int prevX = 0, prevY = 0;
    bool pointInit = false;

    // printf("reached runGraphicContent\n");

    while(!(XNextEvent(disp, &event))) {
        // printf("Reached inside event loop\n");

        switch(event.type) {
            case ButtonPress:
                // printf("Reached button press\n");


                // Color red
                if(event.xbutton.button == Button1) {
                    // printf("reached button 1\n"); 
                    XSetForeground(disp, graphicContent, colorResources[COLOR_RED]->pixel);
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                               event.xbutton.x, event.xbutton.y
                    );
                } 
                // Color blue
                else if(event.xbutton.button == Button3) {
                    XSetForeground(disp, graphicContent, colorResources[COLOR_BLUE]->pixel);
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                               event.xbutton.x, event.xbutton.y
                    );
                }

                break;

            
            case MotionNotify:
                // printf("Reached motion notify\n");

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

                break;
            
            case ButtonRelease:
                // printf("reached button release\n");
                pointInit = false;
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
    run(graphicContent);
    destroyDisplay(&mainWindow, &graphicContent);

    return 0;
}