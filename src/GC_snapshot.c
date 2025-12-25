#include <X11/Xlib.h>
#include "GC.h"
#include "GC_snapshot.h"
#include "def.h"

GCSnapshot gcSnapshotCreate(GC gc, unsigned long mask) {
    GCSnapshot snap;
    snap.mask = mask;
    XGetGCValues(disp, gc, mask, &snap.values);
    return snap;
}

void gcRestore(GC gc, GCSnapshot snap) {
    XChangeGC(disp, gc, snap.mask, &snap.values);
}

GCSnapshot gcSetLineWidth(GC gc, int lineWidth) {
    GCSnapshot snap = gcSnapshotCreate(gc, GCLineWidth);
    XChangeGC(
        disp, gc, GCLineWidth, 
        &(XGCValues){ .line_width = lineWidth }
    );
    return snap;
}

GCSnapshot gcSetLineStyle(GC gc, int lineStyle) {
    GCSnapshot snap = gcSnapshotCreate(gc, GCLineStyle);
    XChangeGC(
        disp, gc, GCLineStyle,
        &(XGCValues){ .line_style = lineStyle }
    );
    return snap;
}

GCSnapshot gcSetForeground(GC gc, unsigned long colorCode) {
    GCSnapshot snap = gcSnapshotCreate(gc, GCForeground);
    XChangeGC(
        disp, gc, GCForeground,
        &(XGCValues) { .foreground = colorCode }
    );
    return snap;
}