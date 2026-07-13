#include <gtk/gtk.h>
#include "TMainWindow/TMainWindow.h"
#include "PDataItem/PDataItem.h"

const std::string folder_svg = R"SVG(<?xml version="1.0" encoding="utf-8"?>
<svg viewBox="0 0 500 500" xmlns="http://www.w3.org/2000/svg" xmlns:bx="https://boxy-svg.com">
  <path style="stroke: rgb(0, 0, 0); stroke-width: 0px; stroke-linejoin: round; stroke-linecap: round; paint-order: fill; fill: rgb(231, 236, 71);"
        d="M 127.46 133.215 H 345.009 A 20 20 0 0 1 365.009 153.215 V 371.226 H 107.46 V 153.215 A 20 20 0 0 1 127.46 133.215 Z"
        bx:shape="rect 107.46 133.215 257.549 238.011 20 20 0 0 1@00d29309"/>
  <path style="stroke: rgb(0, 0, 0); fill: rgb(231, 236, 71); stroke-width: 0px;"
        d="M 144.286 114.565 H 192.303 A 16.4 16.4 0 0 1 208.703 130.965 V 147.425 H 127.886 V 130.965 A 16.4 16.4 0 0 1 144.286 114.565 Z"
        bx:shape="rect 127.886 114.565 80.817 32.86 16.4 16.4 0 0 1@7c4518bc"/>
</svg>)SVG";

void OnAddMenu1(GtkWidget *widget, gpointer data) {
    g_print("AddMenu1\n");
    if (data==nullptr) {
        return;
    }

    TMainWindow *mainwindow = static_cast<TMainWindow*>(data);
    mainwindow->setStatusBarDefaultText("AddMenu1");
}

void OnAddMenu2(GtkWidget *widget, gpointer data) {
    g_print("AddMenu2\n");
    if (data==nullptr) {
        return;
    }

    TMainWindow *mainwindow = static_cast<TMainWindow*>(data);
    mainwindow->setStatusBarDefaultText("AddMenu2");
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    TMainWindow window;
    MenuMainEntryObjectHandle addMenu = window.createMenuMainEntry("Add");
    MenuSubEntryObjectHandle addMenu1Menu = window.createMenuSubEntry("Add1", addMenu, OnAddMenu1, &window);
    MenuSubEntryObjectHandle addMenu2Menu = window.createMenuSubEntry("Add2", addMenu, OnAddMenu2, &window);

    window.show();

    PDataItem item;
    item.setBackgroundColor({0.2, 0.0, 0.3, 0.5});
    item.setDispSize(64);
    item.setSVG(folder_svg);
    item.show();

    gtk_main();
    return 0;
}