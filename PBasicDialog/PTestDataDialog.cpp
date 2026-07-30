//
// Created by rolf on 30.07.26.
//
#include "PTestDataDialog.hpp"

PTestDataDialog::PTestDataDialog(GtkWindow *parent) : PBasicDialog(parent)
{
    m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    setMainControlWindow(m_vbox);

    GtkWidget* entry = gtk_entry_new();
    gtk_widget_set_halign(entry, GTK_ALIGN_START);
    gtk_widget_set_valign(entry, GTK_ALIGN_START);
    gtk_widget_set_margin_top(entry, 10);
    gtk_widget_set_margin_start(entry, 10);
    gtk_box_pack_start(GTK_BOX(m_vbox), entry, FALSE, FALSE, 0);
}

PTestDataDialog::~PTestDataDialog()
{

}