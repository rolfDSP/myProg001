//
// Created by rolf on 30.07.26.
//
#include "PTestDataDialog.hpp"
#include "GUI_Elements/PFramedWindow/PFramedWindow.hpp"

PTestDataDialog::PTestDataDialog(GtkWindow *parent) : PBasicDialog(parent), m_framedWindow(nullptr)
{
    m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    setMainControlWindow(m_vbox);

    GtkWidget* entry = gtk_entry_new();
    gtk_widget_set_halign(entry, GTK_ALIGN_START);
    gtk_widget_set_valign(entry, GTK_ALIGN_START);
    gtk_widget_set_margin_top(entry, 10);
    gtk_widget_set_margin_start(entry, 10);
    gtk_box_pack_start(GTK_BOX(m_vbox), entry, FALSE, FALSE, 0);

    // create a new GTK text line edit field
    GtkWidget* framedEntry = gtk_entry_new();

    // create a PFramedWindow object
    m_framedWindow = new PFramedWindow();
    m_framedWindow->setBGColor({0.5, 0.0, 0.0});
    m_framedWindow->setBorderColor({1.0, 1.0, 1.0});
    m_framedWindow->setBorderWidth(1);
    m_framedWindow->setCornerRadius(20);
    m_framedWindow->setInnerWidgetDistance(10);
    m_framedWindow->setTransparentMode(true);

    // Use PframedWindow.setChildWindow(..) to add the new text line edit field as child window.
    m_framedWindow->setChildWindow(framedEntry);

    // add it to the vertical box layout m_vbox below the entry element
    gtk_box_pack_start(GTK_BOX(m_vbox), m_framedWindow->getWidget(), FALSE, FALSE, 0);

    // create a button in frame
    GtkWidget* but1 = gtk_button_new_with_label("HALLO");
    gtk_widget_set_halign(but1, GTK_ALIGN_START);
    gtk_widget_set_hexpand(but1, TRUE);

    GtkWidget* spacer = gtk_label_new("LabelText");
    gtk_widget_set_hexpand(spacer, TRUE);

    GtkWidget* grid = gtk_grid_new();

    gtk_grid_attach(GTK_GRID(grid), but1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spacer, 1, 0, 1, 1);

    m_framedWindow1 = new PFramedWindow();
    m_framedWindow1->setTransparentMode(true);
    m_framedWindow1->setBorderColor({1.0, 1.0, 1.0});
    m_framedWindow1->setInnerWidgetDistance(5);
    m_framedWindow1->setChildWindow(grid);
    gtk_widget_set_halign(m_framedWindow1->getWidget(), GTK_ALIGN_START);gtk_widget_set_size_request(m_framedWindow1->getWidget(), 300,-1);

    gtk_box_pack_start(GTK_BOX(m_vbox), m_framedWindow1->getWidget(), FALSE, FALSE, 0);
}

PTestDataDialog::~PTestDataDialog()
{
    delete m_framedWindow;
}