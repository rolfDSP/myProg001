Based on GTK+ 3 create a TMainWindow class with the corresponding source and header files:
TMainWindow.cpp
TMainWindow.h

The main window should have a main popup menu visible at the top of the window as usual.

A class function named

MenuMainEntryObjectHandle createMenuMainEntry(const char* name)

should dynamically create a menu top level entry with the name visible as menu label
It should return a suitable reference to the object, which can be stored.

A class function named:

MenuSubEntryObjectHandle createMenuSubEntry(const char* name, MenuMainEntryObjectHandle ref, callback)

should create a sub item for the menu toplevel entry, which is visible, when the menu item is selected as usual.

name: Label visible to the user of this sub menu entry
ref: Reference to the menu top level entry
callback: GTK-3 suitable callback function, which is invoked when the menu is selected.

The function should return a reference to the generated object, which can be stored for further apolication needs.

In the initialization of the TMainWindow class a standard top level menu entry named "File" shall be created.
A sub level entry named "Quit" is required, which calls a function, that closes the complete application.
The "Quit" entry should always be at the end of the sub menu, but this should only be for the "File" main menu created
during the initialization of the TMainWindow class.

The Main Window shall appear in a dark blue color theme.

The default font for the complete text shall be "Arial"

An instance of TStatusBar shall be created and added to the TMainWindow at the bottom in a grid layout.