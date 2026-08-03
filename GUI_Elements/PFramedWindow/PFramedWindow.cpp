#include "PFramedWindow.hpp"
#include <cmath>

static void roundedRect(cairo_t* cr, double x, double y, double w, double h, double r) {
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + r,     y + r,     r,  M_PI,      -M_PI / 2);
    cairo_arc(cr, x + w - r, y + r,     r, -M_PI / 2,  0);
    cairo_arc(cr, x + w - r, y + h - r, r,  0,          M_PI / 2);
    cairo_arc(cr, x + r,     y + h - r, r,  M_PI / 2,  M_PI);
    cairo_close_path(cr);
}

PFramedWindow::PFramedWindow()
    : m_child(nullptr),
      m_transparent(false),
      m_bgColor{1.0, 1.0, 1.0},
      m_borderWidth(1),
      m_borderColor{0.0, 0.0, 0.0},
      m_cornerRadius(6),
      m_innerDistance(0)
{
    m_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    g_signal_connect(m_container, "draw", G_CALLBACK(onDraw), this);

    m_inner = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(m_container), m_inner, TRUE, TRUE, 0);

    updateMargins();
}

PFramedWindow::~PFramedWindow() {
    if (m_container) {
        gtk_widget_destroy(m_container);
        m_container = nullptr;
    }
}

void PFramedWindow::setTransparentMode(bool bTransparent) {
    m_transparent = bTransparent;
    gtk_widget_queue_draw(m_container);
}

void PFramedWindow::setBGColor(RGB color) {
    m_bgColor = color;
    gtk_widget_queue_draw(m_container);
}

void PFramedWindow::setBorderWidth(int width) {
    m_borderWidth = width;
    updateMargins();
    gtk_widget_queue_draw(m_container);
}

void PFramedWindow::setBorderColor(RGB color) {
    m_borderColor = color;
    gtk_widget_queue_draw(m_container);
}

void PFramedWindow::setCornerRadius(int radius) {
    m_cornerRadius = radius;
    gtk_widget_queue_draw(m_container);
}

void PFramedWindow::setChildWindow(GtkWidget* ref) {
    if (m_child) {
        gtk_container_remove(GTK_CONTAINER(m_inner), m_child);
    }
    m_child = ref;
    if (m_child) {
        gtk_box_pack_start(GTK_BOX(m_inner), m_child, TRUE, TRUE, 0);
        gtk_widget_show_all(m_child);
    }
}

void PFramedWindow::setInnerWidgetDistance(int d) {
    m_innerDistance = d;
    updateMargins();
}

void PFramedWindow::show() {
    gtk_widget_show_all(m_container);
}

GtkWidget* PFramedWindow::getWidget() {
    return m_container;
}

void PFramedWindow::updateMargins() {
    int margin = m_borderWidth + m_innerDistance;
    gtk_widget_set_margin_start(m_inner, margin);
    gtk_widget_set_margin_end(m_inner, margin);
    gtk_widget_set_margin_top(m_inner, margin);
    gtk_widget_set_margin_bottom(m_inner, margin);
}

gboolean PFramedWindow::onDraw(GtkWidget* widget, cairo_t* cr, gpointer data) {
    auto* self = static_cast<PFramedWindow*>(data);
    int w = gtk_widget_get_allocated_width(widget);
    int h = gtk_widget_get_allocated_height(widget);

    double radius = self->m_cornerRadius;

    if (self->m_transparent) {
        roundedRect(cr, 0, 0, w, h, radius);
        cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
        cairo_fill(cr);
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    } else {
        roundedRect(cr, 0, 0, w, h, radius);
        cairo_set_source_rgb(cr, self->m_bgColor.r, self->m_bgColor.g, self->m_bgColor.b);
        cairo_fill(cr);
    }

    if (self->m_borderWidth > 0) {
        double half = self->m_borderWidth / 2.0;
        roundedRect(cr, half, half, w - self->m_borderWidth, h - self->m_borderWidth, radius);
        cairo_set_source_rgb(cr, self->m_borderColor.r, self->m_borderColor.g, self->m_borderColor.b);
        cairo_set_line_width(cr, self->m_borderWidth);
        cairo_stroke(cr);
    }

    return FALSE;
}