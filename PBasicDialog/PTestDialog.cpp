//
// Created by rolf on 30.07.26.
//
#include "PTestDialog.hpp"

PTestDialog::PTestDialog(GtkWindow *parent) : PBasicDialog(parent, ALIGN_RIGHT)
{
    GtkWidget* label = gtk_label_new(
        "This is the main content area.\n"
        "Replace this widget with your custom control.");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    setMainControlWindow(label);
}

PTestDialog::~PTestDialog()
{

}