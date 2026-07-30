#include "PBasicDialog.hpp"

PBasicDialog::PBasicDialog(GtkWindow* parent, ButtonAlignment alignment)
    : m_alignment(alignment), m_loop(nullptr), m_result(GTK_RESPONSE_NONE)
{
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_modal(GTK_WINDOW(m_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(m_window), 400, 300);

    if (parent) {
        gtk_window_set_transient_for(GTK_WINDOW(m_window), parent);
        gtk_window_set_destroy_with_parent(GTK_WINDOW(m_window), TRUE);
    }

    g_signal_connect(m_window, "delete-event", G_CALLBACK(onDeleteEvent), this);

    // Outer vertical box: main area (expands) + button row (fixed)
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(m_window), vbox);

    // Main control container — takes all available vertical space
    m_mainContainer = gtk_frame_new(nullptr);
    gtk_frame_set_shadow_type(GTK_FRAME(m_mainContainer), GTK_SHADOW_NONE);
    gtk_widget_set_vexpand(m_mainContainer, TRUE);
    gtk_widget_set_hexpand(m_mainContainer, TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), m_mainContainer, TRUE, TRUE, 0);

    // Button row
    GtkWidget* buttonRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_top(buttonRow, 6);
    gtk_widget_set_margin_bottom(buttonRow, 6);
    gtk_widget_set_margin_start(buttonRow, 6);
    gtk_widget_set_margin_end(buttonRow, 6);

    GtkAlign halign;
    switch (alignment) {
        case ALIGN_LEFT:   halign = GTK_ALIGN_START;  break;
        case ALIGN_CENTER: halign = GTK_ALIGN_CENTER; break;
        case ALIGN_RIGHT:  halign = GTK_ALIGN_END;    break;
        default:           halign = GTK_ALIGN_END;    break;
    }
    gtk_widget_set_halign(buttonRow, halign);

    GtkWidget* okButton     = gtk_button_new_with_label("OK");
    GtkWidget* cancelButton = gtk_button_new_with_label("Cancel");

    gtk_box_pack_start(GTK_BOX(buttonRow), okButton,     FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(buttonRow), cancelButton, FALSE, FALSE, 0);

    g_signal_connect(okButton,     "clicked", G_CALLBACK(okClickedCb),     this);
    g_signal_connect(cancelButton, "clicked", G_CALLBACK(cancelClickedCb), this);

    gtk_box_pack_start(GTK_BOX(vbox), buttonRow, FALSE, FALSE, 0);

    // Separator above button row for visual clarity
    GtkWidget* sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_reorder_child(GTK_BOX(vbox), sep, 1);
    gtk_box_pack_start(GTK_BOX(vbox), sep, FALSE, FALSE, 0);
    gtk_box_reorder_child(GTK_BOX(vbox), sep, 1);
}

PBasicDialog::~PBasicDialog() {
    if (m_window) {
        gtk_widget_destroy(m_window);
        m_window = nullptr;
    }
}

void PBasicDialog::setCaption(const std::string& caption) {
    gtk_window_set_title(GTK_WINDOW(m_window), caption.c_str());
}

void PBasicDialog::show() {
    gtk_widget_show_all(m_window);
}

void PBasicDialog::setMainControlWindow(GtkWidget* widget) {
    GtkWidget* existing = gtk_bin_get_child(GTK_BIN(m_mainContainer));
    if (existing) {
        gtk_container_remove(GTK_CONTAINER(m_mainContainer), existing);
    }
    if (widget) {
        gtk_container_add(GTK_CONTAINER(m_mainContainer), widget);
        gtk_widget_show_all(widget);
    }
}

gint PBasicDialog::run() {
    gtk_widget_show_all(m_window);
    m_result = GTK_RESPONSE_NONE;

    m_loop = g_main_loop_new(nullptr, FALSE);
    g_main_loop_run(m_loop);
    g_main_loop_unref(m_loop);
    m_loop = nullptr;

    return m_result;
}

// Static trampolines — dispatch to the virtual methods so derived classes can override
void PBasicDialog::okClickedCb(GtkWidget* /*widget*/, gpointer data) {
    static_cast<PBasicDialog*>(data)->onOkClicked();
}

void PBasicDialog::cancelClickedCb(GtkWidget* /*widget*/, gpointer data) {
    static_cast<PBasicDialog*>(data)->onCancelClicked();
}

void PBasicDialog::onOkClicked() {
    m_result = GTK_RESPONSE_OK;
    gtk_widget_hide(m_window);
    if (m_loop) {
        g_main_loop_quit(m_loop);
    }
}

void PBasicDialog::onCancelClicked() {
    m_result = GTK_RESPONSE_CANCEL;
    gtk_widget_hide(m_window);
    if (m_loop) {
        g_main_loop_quit(m_loop);
    }
}

gboolean PBasicDialog::onDeleteEvent(GtkWidget* /*widget*/, GdkEvent* /*event*/, gpointer data) {
    auto* self    = static_cast<PBasicDialog*>(data);
    self->m_result = GTK_RESPONSE_DELETE_EVENT;
    if (self->m_loop) {
        g_main_loop_quit(self->m_loop);
    }
    return TRUE;  // suppress default destroy; caller owns the window lifetime
}