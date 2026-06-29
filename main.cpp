#include <gtk/gtk.h>
#include "TMainWindow/TMainWindow.h"

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

    gtk_main();
    return 0;
}