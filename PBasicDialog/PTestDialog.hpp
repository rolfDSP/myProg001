//
// Created by rolf on 30.07.26.
//

#ifndef MYPROG001_PTESTDIALOG_HPP
#define MYPROG001_PTESTDIALOG_HPP

#include "PBasicDialog.hpp"

class PTestDialog : public PBasicDialog
{
public:
    explicit PTestDialog(GtkWindow *parent = nullptr);
    ~PTestDialog();

protected:
    void onOkClicked();
};

#endif //MYPROG001_PTESTDIALOG_HPP
