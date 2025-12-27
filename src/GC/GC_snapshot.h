#ifndef __GC_SNAPSHOT_H
#define __GC_SNAPSHOT_H

#include <X11/Xlib.h>
#include "GC.h"

/*
    Sometimes, you'll need to edit lineAttributes or 
    foreground in order to do something unrelated to the GC. 
    In those cases, after doing so, you'll need to revert 
    the lineAttributes.

    in these cases, we can write some helper functions "set"
    and "revert" functions. 

    set: takes parameter of new xGCValues, returns old XGCValues
    revert: takes old XGCValues and sets them back.
*/

typedef struct {
    unsigned long mask; // Save mask
    XGCValues values;
} GCSnapshot;

GCSnapshot gcSnapshotCreate(GC gc, unsigned long mask);
void gcRestore(GC gc, GCSnapshot snap);

/*
    Some common state changes. Note that these changes
    do nothing but the specified changes.
*/

GCSnapshot gcSetLineWidth(GC gc, int lineWidth);
GCSnapshot gcSetLineStyle(GC gc, int lineStyle);
GCSnapshot gcSetForeground(GC gc, unsigned long colorCode);


#endif // __GC_SNAPSHOT_H