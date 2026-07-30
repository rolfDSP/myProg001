Create a C++ class named PBasicDialog
with the source and header files

PBasicDialog.hpp
PBasicDialog.cpp

The class should have a modal dialog window to be created based on GTK-3

The window has a caption with a title.
The window title can be set with the public member funtion:

void setCaption(const std::string caption)

The window has a two-row vertical layout with

- The main dialog control window in the upper half, covering 90% of the window height.
- A lower half, which has:

- 2 push buttons next to each other, the left one has the caption "OK", while the right one has the caption "Cancel"
- The two buttons shall be next to each other with a spacing of 10 pixels.
- Both buttons can either be left-aligned, centered or right-aligned depending on a flag during the initialization of the class.

The main dialog control window is empty during initialization and can be set with the function:

void setMainControlWiindow(GTKWidget* reference)

