#pragma once

#include <gtk/gtk.h>

struct RGB {
    double r, g, b;  // components in [0.0, 1.0]
};

class PFramedWindow {
public:
    PFramedWindow();
    virtual ~PFramedWindow();

    void setTransparentMode(bool bTransparent);
    void setBGColor(RGB color);
    void setBorderWidth(int width);
    void setBorderColor(RGB color);
    void setCornerRadius(int radius);
    void setChildWindow(GtkWidget* ref);
    void setInnerWidgetDistance(int d);

    void       show();
    GtkWidget* getWidget();

protected:
    GtkWidget* m_container;  // embeddable GtkBox — root widget (no-window, draws in parent surface)
    GtkWidget* m_inner;      // GtkBox inside; margins provide the inset
    GtkWidget* m_child;

    bool m_transparent;
    RGB  m_bgColor;
    int  m_borderWidth;
    RGB  m_borderColor;
    int  m_cornerRadius;
    int  m_innerDistance;

    void updateMargins();

private:
    static gboolean onDraw(GtkWidget* widget, cairo_t* cr, gpointer data);
};