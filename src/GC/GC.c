#include <X11/X.h>
#include <err.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>

#include "../def.h"
#include "GC.h"
#include "../window.h"
#include "../color.h"

GC createGraphicContent(
    unsigned int lineWidth, 
    Window win,
    unsigned long fgColor, 
    unsigned long bgColor
) {
    // So far, win doesn't do anything
    XGCValues xgcValues = {

        // Drawing attributes
        .line_style = LINE_STYLE,
        .line_width = lineWidth,
        .cap_style  = CAP_STYLE,
        .join_style = JOIN_STYLE,
        .fill_style = FILL_STYLE,

        // Colors
        .foreground = fgColor,        
        .background = bgColor
    };           
    unsigned long long 
    valueMask = GCForeground | 
                GCBackground | 
                GCFillStyle | 
                GCLineStyle  | 
                GCLineWidth  | 
                GCCapStyle   | 
                GCJoinStyle;

    GC graphicContent = XCreateGC(disp, win, valueMask, &xgcValues);
    return graphicContent;
}

GC takeGraphicContentInput(Window win) {
    unsigned int lineWidth;
    printf("Enter the width of the line: ");
    scanf("%u", &lineWidth);

    // Default color: Red foreground, Blue background
    GC graphicContent = createGraphicContent(lineWidth, win, 
                        colorResources[COLOR_RED]->pixel, 
                        colorResources[COLOR_BLUE]->pixel);

    printf("Graphic Content created with line width: %u\n", lineWidth);

    return graphicContent;
}

/*
    @brief: Creates a default graphic content
    with predefined attributes.
*/
GC openDefaultGraphicContent(Window win) {
    return createGraphicContent(LINE_WIDTH, win, 
                    colorResources[COLOR_RED]->pixel,   
                    colorResources[COLOR_BLUE]->pixel 
    );
}
