Class PFramedWindow

with

PFramedWindow.cpp
PFramedWindow.hpp

contains a GTK-3 window with these features:

- Window should be used as a control element to be subclassed as a child window.
- Should be transparent or have a background with a defineable color.
  setTransparentMode(bool bTransparent)
  if bTransparent is true, then the window should be transparent, otherwise have a background color m_bgColor as class member
  setBGColor(RGB color color)
  sets the background color, if the window is not transparent.
- The window shall have a frame with an adjustable line width and color. The edges shall be rounded.
  setBorderWidth(int width)
  should set the border width in pixels.
  setBorderColor(RGB color color)
  should set the color of the border line.
- In the center of the window shall be a child GTK Window, which can be set with the function
  setChildWindow(GTKWidget* ref)
  The inner window should have an adjustable distance to the border of the widget, which can be set by the function:
  setInnerWidgetDistance(int d)
  where d is the distance to the border line in pixels for all 4 edges of the window.

