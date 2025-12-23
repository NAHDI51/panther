#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "def.h"   
#include "color.h"
#include "window.h"

Window createWindow(
    int x, // posX
    int y, // posY
    int w, // width
    int h, // height
    int b, // border
    unsigned long bgColor,
    unsigned long borderColor
) {
        

    unsigned long long 
    eventMask = Button1MotionMask | 
                Button3MotionMask | 
                ButtonPressMask   |
                ButtonReleaseMask | 
                Button1Mask       | 
                Button3Mask       | 
                KeyPressMask;


    XSetWindowAttributes xattr = {
        .background_pixel = bgColor,
        // .border_pixel     = WhitePixel(disp, screenNum),
        .border_pixel     = borderColor,
        .event_mask       = eventMask
    };

    unsigned long long 
    createWindowMask = CWBackPixel   | 
                       CWBorderPixel | 
                       CWEventMask;

    Window win = XCreateWindow(disp, rootWindow, x, y, w, h, b,
                 DefaultDepth(disp, screenNum), InputOutput,
                 DefaultVisual(disp, screenNum), 
                 createWindowMask,
                 &xattr
                );
            
    // Colormap colormap = DefaultColormap(disp, screenNum);
    
    return win;
}

void setWindowSizeHints(
    Window win, 
    int minWidth, 
    int minHeight,
    int maxWidth,
    int maxHeight) 
{
    XSizeHints sizeHints = {
        .flags = PMinSize | PMaxSize,
        .min_width  = minWidth,
        .min_height = minHeight,
        .max_width  = maxWidth,
        .max_height = maxHeight
    };
    XSetSizeHints(disp, win, &sizeHints, XA_WM_NORMAL_HINTS);
}

/*
    @brief: Sets a fixed size for the window
*/
void setFixedWindowSize(Window win, int width, int height) {
    setWindowSizeHints(win, width, height, width, height);
}



Window takeWindowInput() {
    /*
    Last two variables: Border and Background
    */
    printf("Enter the dimensions (x,y,width,height,border): ");
    int x, y;
    unsigned int width, height, border;
    scanf("%d %d %u %u %u", &x, &y, &width, &height, &border);

    char windowName[128];
    printf("Enter the name of the Window: ");
    scanf("%[^\n]s", windowName);

    // For the time being, default color = white background, red border
    Window win = createWindow(x, y, width, height, border,
                                colorResources[COLOR_WHITE]->pixel,
                                colorResources[COLOR_RED]->pixel
    );
    XStoreName(disp, win, windowName);
    XMapWindow(disp, win);

    // For the time being, setting fixed window size.
    setFixedWindowSize(win, width, height);



    printf("Window created at (%d,%d) with dimensions %ux%u and border %u\n",
           x, y, width, height, border
    );

    return win;
}

Window openDefaultWindow() {
    // For the time being, default color = white background, red border
    Window mainWindow = createWindow(POSX, POSY, WIDTH, HEIGHT, BORDER,
                                     colorResources[COLOR_WHITE]->pixel,
                                     colorResources[COLOR_RED]->pixel      
    );
    XStoreName(disp, mainWindow, "Default Paint Window");
    XMapWindow(disp, mainWindow);

    // For the time being, setting fixed window size.
    setFixedWindowSize(mainWindow, WIDTH, HEIGHT);
    return mainWindow;
}