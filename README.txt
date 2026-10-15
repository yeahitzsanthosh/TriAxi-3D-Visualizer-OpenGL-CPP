TRIAXI 3D VISUALIZER (OpenGL + C++)

A learning project to build a CAD/FEA viewer from scratch using
C++, wxWidgets and OpenGL.

Step 1 done: a canvas with mouse pan, zoom and rotate.
Next: loading model files.


WHAT IS THIS?

My goal is to build a CAD/FEA file viewer step by step, learning
OpenGL along the way. This is Step 1. Right now the app shows a
purple triangle in a window, and you can move it around with your
mouse. This is the base that the viewer will be built on.

Small start, but it works!


WHAT IT CAN DO

- Opens a window with an OpenGL canvas
- Draws a triangle
- Pan, zoom and rotate using the mouse


HOW TO CONTROL IT

Pan (move the view)    Hold Ctrl + Right mouse button, then move the mouse
Zoom                   Scroll the mouse wheel
Rotate                 Hold Ctrl + Left mouse button, then move the mouse left or right

Zoom is limited between 0.1x and 2.5x, so you can't lose the triangle.


WHAT I USED

- Language: C++
- Window and mouse handling: wxWidgets
- Drawing: OpenGL
- Platform: Windows (Visual Studio)


FILES

TA_Main_APP.h     Class declarations
TA_Main_APP.cpp   All the code: window, canvas, mouse and drawing

There are two classes:
- TA_APP     starts the app and creates the window
- TA_Canvas  draws with OpenGL and handles the mouse


HOW IT WORKS (THE SIMPLE VERSION)

The mouse never talks to OpenGL directly. Instead:

1. When you move the mouse, I save the new values (pan, zoom, angle).
2. The canvas repaints.
3. On every repaint, those saved values are given to OpenGL.

   Ctrl + Right drag  ->  pan values   ->  glTranslatef
   Mouse wheel        ->  zoom value   ->  glScalef
   Ctrl + Left drag   ->  angle value  ->  glRotatef

4. The triangle is drawn and the screen is updated with SwapBuffers.

That's the whole idea!


WHAT I LEARNED

- glClearColor: sets the background color
- glTranslatef: moves things (used for pan)
- glScalef: makes things bigger or smaller (used for zoom)
- glRotatef: spins things (used for rotate)
- Double buffering: draw in the background, then show it all at once,
  so there is no flickering
- How wxWidgets sets up an OpenGL canvas
- How to turn mouse movement into pan, zoom and rotate
- CaptureMouse: keeps dragging working even when the mouse leaves
  the canvas


HOW TO BUILD

You need:
- Windows and Visual Studio
- wxWidgets built with OpenGL support

Steps:
1. Download and build wxWidgets from wxwidgets.org
2. Make a new Visual Studio C++ project
3. Add TA_Main_APP.h and TA_Main_APP.cpp
4. Set up the wxWidgets include and library paths
5. Build and run

Note about the icon:
The icon path in the code is fixed to my computer:
D:\WS\TRI_AXI_26\Dependecy\Image\logo_256.png
Change it to your own image path. If the image is not found, the app
still runs, it just uses the default icon.


THINGS NOT DONE YET

- Cannot load any CAD/FEA files yet
- Uses old-style OpenGL (glBegin / glEnd)
- Rotation only spins around the Z axis
- Only one hard-coded triangle
- The view does not adjust when the window is resized


WHAT'S NEXT

- Load model files (first file format to be decided)
- Show the loaded model on the canvas
- Fix window resizing
- Draw X, Y, Z axes and a grid
- Add a real 3D camera
- Add lighting and shading
- Show FEA results with colors
- Move to modern OpenGL (shaders)
- Add menus and toolbars


AUTHOR

Santhoshkumar Selvakkumar
https://github.com/your-username/TriAxi-3D-Visualizer-OpenGL-CPP
