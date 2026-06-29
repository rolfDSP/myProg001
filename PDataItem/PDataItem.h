#pragma once

#include <gtk/gtk.h>
#include <string>

class PDataItem {
public:
    PDataItem();
    ~PDataItem();

    PDataItem(const PDataItem&)            = delete;
    PDataItem& operator=(const PDataItem&) = delete;
    PDataItem(PDataItem&&)                 = delete;
    PDataItem& operator=(PDataItem&&)      = delete;

    void show();

    void setBackgroundColor(const GdkRGBA& color);
    void setDispSize(int size);

    void               setName(const std::string& name) { m_sName = name; }
    const std::string& getName() const                  { return m_sName; }

private:
    GtkWidget*  m_window;
    std::string m_sName;
    GdkRGBA     m_bgColor;
    int         m_size;

    static gboolean onDraw(GtkWidget* widget, cairo_t* cr, gpointer userData);
};
