#pragma once

#include <gtk/gtk.h>
#include "TStatusBar/TStatusBar.h"

using MenuMainEntryObjectHandle = GtkWidget*;
using MenuSubEntryObjectHandle  = GtkWidget*;
using MenuCallback              = void (*)(GtkWidget*, gpointer);

class TMainWindow {
public:
    TMainWindow();
    ~TMainWindow();

    TMainWindow(const TMainWindow&)            = delete;
    TMainWindow& operator=(const TMainWindow&) = delete;
    TMainWindow(TMainWindow&&)                 = delete;
    TMainWindow& operator=(TMainWindow&&)      = delete;

    void show();

    MenuMainEntryObjectHandle createMenuMainEntry(const char* name);
    MenuSubEntryObjectHandle  createMenuSubEntry(const char* name,
                                                 MenuMainEntryObjectHandle ref,
                                                 MenuCallback callback,
                                                 gpointer userData = nullptr);

    MenuMainEntryObjectHandle getFileMenu() {
        return mfileMenu;
    }

    void setStatusBarDefaultText(const std::string text);

    void onAddMenu1();

private:
    GtkWidget* m_window;
    GtkWidget* m_vbox;
    GtkWidget* m_menuBar;
    GtkWidget* m_contentArea;

    MenuMainEntryObjectHandle mfileMenu  = nullptr;
    MenuSubEntryObjectHandle  m_quitItem = nullptr;
    TStatusBar                m_statusBar;

    static void applyDarkBlueTheme();
    static void onQuit(GtkWidget* widget, gpointer data);
};
