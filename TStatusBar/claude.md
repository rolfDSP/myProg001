Create a C++ class named TStatusBar

TStatusBar.cpp
TStatusBar.h

Based on GTK+ 3 a GTK window as a status bar at the bottom of TMainWindow shall be created
The TStatusBar shall be a child window of TMainWindow and be visible at the bottom of the main window.

The height of the TStatusBar window shall be fixed set to 30 pixels
It should use the same color scheme as specified for the main window and have no border, but a bit different color.

The status bar should have a dynamic horizontal grid layout, where up to 3 sub windows shall be displayed next to each 
other.

A public function named SetSubWindow(int index, GtkWidget* widget)

shall dynamically set and display the status bar sub window.
The index sets the index in the 3 elements grid layout and shall not exceed 2.

With a class function named:

setStatusDefaultText(const std::string text)

I want to set and display the m_default_label left aligned to the status bar window.
The status bar sub windows shall be exchangeable dynamically with GtkWidget* pointer references.