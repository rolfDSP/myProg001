Create a C++ class named:

PDataItem.cpp
PDataItem.h

This class shall create a fixed-size GTK+ 3 window with no border and no windows title bar.

The background color of the window should be configurable with this public class function:

void setBackgroundColor(color)

color should be a RGB color suitale for GTK+ 3.

The size should be quadratic, i.e. width = height and the user shall be ale to set it with the public class function:

void setDispSize(int size)

The class should have a member variable called m_sName of the type std::string.
It should have a suitable public set/get function.

