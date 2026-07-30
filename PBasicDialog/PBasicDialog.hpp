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
    void show();

    gint run();

protected:
    virtual void onOkClicked();
    virtual void onCancelClicked();

private:
    GtkWidget*      m_window;
    GtkWidget*      m_mainContainer;
    ButtonAlignment m_alignment;
    GMainLoop*      m_loop;
    gint            m_result;

    static void     okClickedCb(GtkWidget* widget, gpointer data);
    static void     cancelClickedCb(GtkWidget* widget, gpointer data);
    static gboolean onDeleteEvent(GtkWidget* widget, GdkEvent* event, gpointer data);
};