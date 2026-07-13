#include "PDataItem.h"

PDataItem::PDataItem()
    : m_window(nullptr)
    , m_size(100)
    , m_svgHandle(nullptr)
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

PDataItem::~PDataItem() {
    if (m_svgHandle)
        g_object_unref(m_svgHandle);
}

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

void PDataItem::setSVG(const std::string& def) {
    if (m_svgHandle) {
        g_object_unref(m_svgHandle);
        m_svgHandle = nullptr;
    }

    if (def.empty())
        return;

    GError* error = nullptr;
    m_svgHandle = rsvg_handle_new_from_data(
        reinterpret_cast<const guint8*>(def.data()),
        static_cast<gsize>(def.size()),
        &error
    );
    if (!m_svgHandle) {
        g_printerr("PDataItem::setSVG: failed to parse SVG: %s\n",
                   error ? error->message : "unknown error");
        if (error) g_error_free(error);
        return;
    }

    gtk_widget_queue_draw(m_window);
}

gboolean PDataItem::onDraw(GtkWidget* widget, cairo_t* cr, gpointer userData) {
    PDataItem* self = static_cast<PDataItem*>(userData);

    // Fill background
    cairo_set_source_rgba(cr,
                          self->m_bgColor.red,
                          self->m_bgColor.green,
                          self->m_bgColor.blue,
                          self->m_bgColor.alpha);
    cairo_paint(cr);

    if (!self->m_svgHandle)
        return FALSE;

    const double win_w = gtk_widget_get_allocated_width(widget);
    const double win_h = gtk_widget_get_allocated_height(widget);

    // SVG occupies 90% of the window; the remaining 10% is split as 5% margin on each side
    const double render_w = win_w * 1.2;
    const double render_h = win_h * 1.2;

    // Get the SVG's natural size so we can preserve its aspect ratio
    gdouble svg_w = 0.0, svg_h = 0.0;
    if (!rsvg_handle_get_intrinsic_size_in_pixels(self->m_svgHandle, &svg_w, &svg_h)
        || svg_w <= 0.0 || svg_h <= 0.0)
    {
        // No intrinsic size — fill the 90% box directly
        svg_w = render_w;
        svg_h = render_h;
    }

    // Scale uniformly so the SVG fits within the 90% box
    const double scale    = MIN(render_w / svg_w, render_h / svg_h);
    const double scaled_w = svg_w * scale;
    const double scaled_h = svg_h * scale;

    // Center the scaled SVG in the window
    const double x_offset = (win_w - scaled_w) / 2.0;
    const double y_offset = (win_h - scaled_h) / 2.0;

    GError* error = nullptr;
    const RsvgRectangle viewport = { x_offset, y_offset, scaled_w, scaled_h };
    rsvg_handle_render_document(self->m_svgHandle, cr, &viewport, &error);

    if (error) {
        g_printerr("PDataItem::onDraw: render error: %s\n", error->message);
        g_error_free(error);
    }

    return FALSE;
}