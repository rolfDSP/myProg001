#pragma once

#include <gtk/gtk.h>
#include <string>

class PBasicDialog {
public:
    enum ButtonAlignment {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };

    explicit PBasicDialog(GtkWindow* parent = nullptr, ButtonAlignment alignment = ALIGN_RIGHT);
    ~PBasicDialog();

    void setCaption(const std::string& caption);
    void setMainControlWindow(GtkWidget* widget);

    gint run();

private:
    GtkWidget*      m_window;
    GtkWidget*      m_mainContainer;
    ButtonAlignment m_alignment;
    GMainLoop*      m_loop;
    gint            m_result;

    static void     onOkClicked(GtkWidget* widget, gpointer data);
    static void     onCancelClicked(GtkWidget* widget, gpointer data);
    static gboolean onDeleteEvent(GtkWidget* widget, GdkEvent* event, gpointer data);
};