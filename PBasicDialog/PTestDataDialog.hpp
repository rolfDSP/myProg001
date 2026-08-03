//
// Created by rolf on 30.07.26.
//

#ifndef MYPROG001_PTESTDATADIALOG_HPP
#define MYPROG001_PTESTDATADIALOG_HPP

#include "PBasicDialog.hpp"
#include "GUI_Elements/PFramedWindow/PFramedWindow.hpp"

class PTestDataDialog : public PBasicDialog
{
public:
    PTestDataDialog(GtkWindow *parent = nullptr);
    ~PTestDataDialog();

protected:
    GtkWidget*    m_vbox;
    PFramedWindow* m_framedWindow;
    PFramedWindow* m_framedWindow1;
};

#endif //MYPROG001_PTESTDATADIALOG_HPP
