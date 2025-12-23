#include <X11/Xlib.h>
#include <stdio.h>
#include <err.h>

// estallish connection with display serer 
static Display* dpy;

// Number of screen
static int screen_number;

// Root from which the windows start
static Window root;

/*
MACROS
*/

/*
    @brief: Creates a window from the specified dimensions

    @details: The background is white, border is black. 
    Event mask is buttonPress: program stops whenever a 
    button is pressed.

    It uses XCreateWindow instead of XCreateSimpleWindow.
*/
static Window createWindow(int posx, int posy, int width, int height, int border) {

    // Specifications for the Window
    XSetWindowAttributes xattr; 

    xattr.background_pixel  = WhitePixel(dpy, screen_number);
    xattr.border_pixel      = BlackPixel(dpy, screen_number);
    xattr.event_mask        = ButtonPress;

    // Creates a window as a subwindow of root.
    /*
    Syntax: XCreateWindow(display, root_window, x, y, w, h, b
                depth, class (inputOutput/InputOnly), visual,
                mask, xattribute)
    */
    Window win = XCreateWindow(dpy, root, posx, posy, width, height, border,
                 DefaultDepth(dpy, screen_number), InputOutput,
                 DefaultVisual(dpy, screen_number),
                 CWBackPixel | CWBorderPixel | CWEventMask,
                 &xattr
                );
    return win;
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
    return win;
}

/*
    @brief: Runs the window till the next event.
*/
static void run() {
    XEvent ev;

    while(XNextEvent(dpy, &ev) == 0) {
        switch(ev.type) {
            case ButtonPress:
                return;

        }
    }
}

/*
    @brief: Frees the resources
*/
void freeWindows(Window* win) {
    XUnmapWindow(dpy, *win);
    XDestroyWindow(dpy, *win);

    //Close connection with X11
    XCloseDisplay(dpy);
}


int main(/* int argc, char** argv */) {
    

    // Establish connection with X11, and check if 
    // estabilshed properly.
    
    dpy = XOpenDisplay(NULL);
    if((dpy = XOpenDisplay(NULL)) == NULL) {
        errx(1, "Can't open display.\n");
    }

    // Get default screen and root widow
    screen_number = DefaultScreen(dpy);
    root = RootWindow(dpy, screen_number); 

    // Window input 
    Window win = takeWindowInput();

    // Map our widow to display Server
    XMapWindow(dpy, win);

    run();

    freeWindows(&win);
}