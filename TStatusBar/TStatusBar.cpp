#include "TStatusBar.h"

static const gchar* STATUS_BAR_CSS =
    "box.statusbar {"
    "  background-color: #0f2744;"
    "  padding: 2px;"
    "}"
    "box.statusbar grid {"
    "  background-color: #0f2744;"
    "}"
    "box.statusbar grid frame {"
    "  background-color: #0a1f3a;"
    "  border: 1px solid #1a3a6b;"
    "}";

TStatusBar::TStatusBar() {
    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, STATUS_BAR_CSS, -1, nullptr);
    GdkScreen* screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    m_frame = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class(gtk_widget_get_style_context(m_frame), "statusbar");
    gtk_widget_set_size_request(m_frame, -1, 30);

    m_grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(m_grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(m_grid), 2);
    gtk_widget_set_hexpand(m_grid, TRUE);
    gtk_widget_set_vexpand(m_grid, TRUE);
    gtk_box_pack_start(GTK_BOX(m_frame), m_grid, TRUE, TRUE, 0);

    m_default_label = gtk_label_new("OK");
    gtk_label_set_xalign(GTK_LABEL(m_default_label), 0.0f);
    SetSubWindow(0, m_default_label);
}

TStatusBar::~TStatusBar() = default;

GtkWidget* TStatusBar::getWidget() {
    return m_frame;
}

int TStatusBar::addPanel(GtkWidget* content) {
    if (!content || m_panelCount >= MAX_PANELS) return -1;

    GtkWidget* panel = gtk_frame_new(nullptr);
    gtk_widget_set_hexpand(panel, TRUE);
    gtk_widget_set_vexpand(panel, TRUE);
    gtk_container_add(GTK_CONTAINER(panel), content);
    gtk_grid_attach(GTK_GRID(m_grid), panel, m_panelCount, 0, 1, 1);

    return m_panelCount++;
}

void TStatusBar::setStatusDefaultText(const std::string text) {
    gtk_label_set_text(GTK_LABEL(m_default_label), text.c_str());
}

void TStatusBar::SetSubWindow(int index, GtkWidget* widget) {
    if (index < 0 || index >= MAX_PANELS || !widget) return;

    if (m_subWindows[index]) {
        gtk_container_remove(GTK_CONTAINER(m_grid), m_subWindows[index]);
    }

    m_subWindows[index] = widget;
    gtk_widget_set_hexpand(widget, TRUE);
    gtk_widget_set_vexpand(widget, TRUE);
    gtk_grid_attach(GTK_GRID(m_grid), widget, index, 0, 1, 1);
    gtk_widget_show(widget);
}

GtkWidget* TStatusBar::getSubWindow(int index) const {
    if (index < 0 || index >= MAX_PANELS) return nullptr;
    return m_subWindows[index];
}