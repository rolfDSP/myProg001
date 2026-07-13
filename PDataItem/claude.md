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

New 2026/07/13:

A SVG graphics shall be rendered in the window, centered in x and y direction.
The size of the SVG picture shall be 90% of the total window size and re-adjusted on resizing.
The SVG definition in XML format shall be passed as a string with the class function:

setSVG(const std::string def)

It should be possible to change the definition dynamically at runtime and redraw the window.