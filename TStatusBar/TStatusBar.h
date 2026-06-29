#pragma once

#include <gtk/gtk.h>
#include <string>

class TStatusBar {
public:
    TStatusBar();
    ~TStatusBar();

    TStatusBar(const TStatusBar&)            = delete;
    TStatusBar& operator=(const TStatusBar&) = delete;
    TStatusBar(TStatusBar&&)                 = delete;
    TStatusBar& operator=(TStatusBar&&)      = delete;

    // Returns the top-level widget to be packed into TMainWindow
    GtkWidget* getWidget();

    // Add a widget as a panel (up to 3). Returns panel index, or -1 if full.
    int addPanel(GtkWidget* content);

    // Set (or replace) the widget at a specific grid slot (index 0–2).
    void       SetSubWindow(int index, GtkWidget* widget);

    // Retrieve the widget currently occupying a slot (nullptr if empty).
    GtkWidget* getSubWindow(int index) const;

    void setStatusDefaultText(const std::string text);

private:
    static constexpr int MAX_PANELS = 3;

    GtkWidget* m_frame;
    GtkWidget* m_grid;
    GtkWidget* m_subWindows[MAX_PANELS] = {};
    int        m_panelCount = 0;
    GtkWidget* m_default_label = nullptr;
};
