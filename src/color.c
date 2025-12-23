// X11 libraries
#include <X11/Xft/Xft.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/X.h>

#include "def.h"
#include "color.h"

#include <stdlib.h>
#include <err.h>

static void createColor(
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

static void constructColorResources() {
    for(int i = 0; i < COLOR_COUNT; i++) {
        // They will be freed from the main header file upon termination.
        colorResources[i] = (XftColor*) malloc(sizeof(XftColor));
        createColor(colorResources[i], colorCodes[i]);
    }
}

static void destroyColorResources() {
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