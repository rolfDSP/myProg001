#include "TMainWindow.h"

static const gchar* DARK_BLUE_CSS =
    "* {"
    "  font-family: Arial, sans-serif;"
    "}"
    "window {"
    "  background-color: #0a1628;"
    "}"
    "menubar {"
    "  background-color: #0d1f3c;"
    "  color: #c8d8f0;"
    "  border-bottom: 1px solid #1a3a6b;"
    "}"
    "menubar > menuitem {"
    "  color: #c8d8f0;"
    "  padding: 4px 8px;"
    "}"
    "menubar > menuitem:hover,"
    "menubar > menuitem:active {"
    "  background-color: #1a3a6b;"
    "  color: #ffffff;"
    "}"
    "menu {"
    "  background-color: #0d1f3c;"
    "  color: #c8d8f0;"
    "  border: 1px solid #1a3a6b;"
    "}"
    "menuitem {"
    "  color: #c8d8f0;"
    "  padding: 4px 12px;"
    "}"
    "menuitem:hover {"
    "  background-color: #1a3a6b;"
    "  color: #ffffff;"
    "}";

TMainWindow::TMainWindow() {
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(m_window), "Main Window");
    gtk_window_set_default_size(GTK_WINDOW(m_window), 800, 600);
    g_signal_connect(m_window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // GtkGrid gives explicit per-row sizing: only the content row expands
    m_vbox = gtk_grid_new();
    gtk_widget_set_hexpand(m_vbox, TRUE);
    gtk_widget_set_vexpand(m_vbox, TRUE);
    gtk_container_add(GTK_CONTAINER(m_window), m_vbox);

    // Row 0: menu bar — fixed height
    m_menuBar = gtk_menu_bar_new();
    gtk_widget_set_hexpand(m_menuBar, TRUE);
    gtk_grid_attach(GTK_GRID(m_vbox), m_menuBar, 0, 0, 1, 1);

    // Row 1: content area — expands to fill all remaining vertical space
    m_contentArea = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(m_contentArea, TRUE);
    gtk_widget_set_vexpand(m_contentArea, TRUE);
    gtk_grid_attach(GTK_GRID(m_vbox), m_contentArea, 0, 1, 1, 1);

    // Row 2: status bar — fixed height, pinned to bottom
    GtkWidget* statusWidget = m_statusBar.getWidget();
    gtk_widget_set_hexpand(statusWidget, TRUE);
    gtk_widget_set_vexpand(statusWidget, FALSE);
    gtk_widget_set_valign(statusWidget, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(m_vbox), statusWidget, 0, 2, 1, 1);

    applyDarkBlueTheme();

    mfileMenu   = createMenuMainEntry("File");
    m_quitItem  = createMenuSubEntry("Quit", mfileMenu, onQuit);
}

TMainWindow::~TMainWindow() = default;

void TMainWindow::show() {
    gtk_widget_show_all(m_window);
}

MenuMainEntryObjectHandle TMainWindow::createMenuMainEntry(const char* name) {
    if (!name) return nullptr;
    GtkWidget* menuItem = gtk_menu_item_new_with_label(name);
    GtkWidget* subMenu  = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), subMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(m_menuBar), menuItem);
    // Return the submenu so callers can attach sub-entries to it
    return subMenu;
}

MenuSubEntryObjectHandle TMainWindow::createMenuSubEntry(const char* name,
                                                          MenuMainEntryObjectHandle ref,
                                                          MenuCallback callback,
                                                          gpointer userData) {
    if (!name || !ref) return nullptr;
    GtkWidget* menuItem = gtk_menu_item_new_with_label(name);

    if (ref == mfileMenu && m_quitItem) {
        // Keep Quit pinned at the bottom of the File menu
        GList* children = gtk_container_get_children(GTK_CONTAINER(ref));
        gint pos = g_list_index(children, m_quitItem);
        g_list_free(children);
        gtk_menu_shell_insert(GTK_MENU_SHELL(ref), menuItem, pos);
    } else {
        gtk_menu_shell_append(GTK_MENU_SHELL(ref), menuItem);
    }

    if (callback) {
        g_signal_connect(menuItem, "activate", G_CALLBACK(callback), userData);
    }
    return menuItem;
}

void TMainWindow::setStatusBarDefaultText(const std::string text) {
    m_statusBar.setStatusDefaultText(text);
}

void TMainWindow::onQuit(GtkWidget* /*widget*/, gpointer /*data*/) {
    gtk_main_quit();
}

void TMainWindow::applyDarkBlueTheme() {
    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, DARK_BLUE_CSS, -1, nullptr);
    GdkScreen* screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}
