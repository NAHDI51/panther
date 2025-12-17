#include <X11/X.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <stdbool.h>

#define POSX    500
#define POSY    500
#define WIDTH   500
#define HEIGHT  500
#define BORDER  10
#define LINE    2

static Display* disp;
static int screenNum;
static Window rootWindow;

static Window createWindow(int x, int y, int w, int h, int b) {

    XSetWindowAttributes xattr = {
        .background_pixel = WhitePixel(disp, screenNum),
        .border_pixel     = BlackPixel(disp, screenNum),
        .event_mask       = Button1MotionMask | ButtonPressMask | 
                            ButtonReleaseMask | KeyPressMask
    };

    Window win = XCreateWindow(disp, rootWindow, x, y, w, h, b,
                 DefaultDepth(disp, screenNum), InputOutput,
                 DefaultVisual(disp, screenNum), 
                 CWEventMask | CWBackPixel | CWBorderPixel,
                 &xattr
                );
    
    return win;
}

static GC createGraphicContent(unsigned int lineWidth, Window win) {

    // So far, win doesn't do anything
    XGCValues xgcValues = {

        // Drawing attributes
        .line_style = LineSolid,
        .line_width = lineWidth,
        .cap_style  = CapButt,
        .join_style = JoinMiter,
        .fill_style = FillSolid,

        // Colors
        .foreground = BlackPixel(disp, screenNum),
        .background = WhitePixel(disp, screenNum)
    };

    unsigned long long valueMask = GCForeground | GCBackground | GCFillRule | 
                    GCLineStyle  | GCLineWidth  | GCCapStyle   | GCJoinStyle;

    GC graphicContent = XCreateGC(disp, rootWindow, valueMask, &xgcValues);

    return graphicContent;
}

/*
    @brief: Takes input of x,y,width,height, border, and 
    uses them to create a window
*/
Window takeWindowInput() {
    /*
    Last two variables: Border and Background
    */
    printf("Enter the dimensions (x,y,width,height,border): ");
    int x, y;
    unsigned int width, height, border;
    scanf("%d %d %u %u %u", &x, &y, &width, &height, &border);

    Window win = createWindow(x, y, width, height, border);

    printf("Window created at (%d,%d) with dimensions %ux%u and border %u\n",
           x, y, width, height, border
    );

    return win;
}
//
/*
    @brief Takes input of lineWidth from the user
*/
GC takeGraphicContentInput(Window win) {
    unsigned int lineWidth;
    printf("Enter the width of the line: ");
    scanf("%u", &lineWidth);

    GC graphicContent = createGraphicContent(lineWidth, win);

    printf("Graphic Content created with line width: %u\n", lineWidth);

    return graphicContent;
}

/*
    @brief Sets the necessary globat attributes with
    proper value.
*/

void constructDisplay() {

    if(!(disp = XOpenDisplay(NULL))) {
        errx(1, "Can't open display!\n");
        exit(1);
    }
    screenNum = DefaultScreen(disp);
    rootWindow = RootWindow(disp, screenNum);

    return;
}

/*
    @brief: Frees the resources
*/
void destroyDisplay(Window* win, GC* gc) {
    XUnmapWindow(disp, *win);
    XDestroyWindow(disp, *win);
    XFreeGC(disp, *gc);

    //Close connection with X11
    XCloseDisplay(disp);
}


void runGraphicContent(GC graphicContent) {
    XEvent event;
    int prevX = 0, prevY = 0;
    bool pointInit = false;

    printf("reached runGraphicContent\n");

    while(!(XNextEvent(disp, &event))) {
        // printf("Reached inside event loop\n");

        switch(event.type) {

            case ButtonPress:
                if(event.xbutton.x == Button1) {
                    XDrawPoint(disp, event.xbutton.window, graphicContent,
                               event.xbutton.x, event.xbutton.y
                    );
                } 
                break;
            
            case MotionNotify:
                if(pointInit) {
                    XDrawLine(disp, event.xbutton.window, graphicContent,
                              prevX          , prevY,
                              event.xbutton.x, event.xbutton.y
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
                pointInit = false;
                break;
            
            case KeyPress:
                if(XkbKeycodeToKeysym(disp, event.xkey.keycode, 0, 0) == XK_q) {
                    return; 
                }
                break;

        }

    }

}

int main() {

    constructDisplay();
    Window mainWindow = takeWindowInput();
    XMapWindow(disp, mainWindow);
    GC graphicContent = takeGraphicContentInput(mainWindow);
    runGraphicContent(graphicContent);
    destroyDisplay(&mainWindow, &graphicContent);

    return 0;
}