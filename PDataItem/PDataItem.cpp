#include "PDataItem.h"

PDataItem::PDataItem()
    : m_window(nullptr)
    , m_size(100)
{
    m_bgColor = { 0.0, 0.0, 0.0, 1.0 };

    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(m_window), FALSE);
    gtk_window_set_resizable(GTK_WINDOW(m_window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(m_window), m_size, m_size);

    // Let the application paint the background instead of the GTK theme
    gtk_widget_set_app_paintable(m_window, TRUE);

    g_signal_connect(m_window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
    g_signal_connect(m_window, "draw",    G_CALLBACK(onDraw),        this);
}

PDataItem::~PDataItem() = default;

void PDataItem::show() {
    gtk_widget_show_all(m_window);
}

void PDataItem::setBackgroundColor(const GdkRGBA& color) {
    m_bgColor = color;
    gtk_widget_queue_draw(m_window);
}

void PDataItem::setDispSize(int size) {
    m_size = size;
    gtk_window_set_default_size(GTK_WINDOW(m_window), m_size, m_size);
    gtk_widget_set_size_request(m_window, m_size, m_size);
}

gboolean PDataItem::onDraw(GtkWidget* /*widget*/, cairo_t* cr, gpointer userData) {
    PDataItem* self = static_cast<PDataItem*>(userData);
    cairo_set_source_rgba(cr,
                          self->m_bgColor.red,
                          self->m_bgColor.green,
                          self->m_bgColor.blue,
                          self->m_bgColor.alpha);
    cairo_paint(cr);
    return FALSE;
}
