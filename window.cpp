#include "window.h"
#include "ui_window.h"
#include "draw.h"

#include <QtWidgets>

// MainWindow constructor
Window::Window()
{
    // Create the ScribbleArea widget and make it
    // the central widget
    draw = new Draw;
    setCentralWidget(draw);

    // Create actions and menus
    createActions();
    createMenus();

    // Set the title
//    setWindowTitle(tr("Scribble"));

    // Size the app
    resize(500, 500);
}

// Opens a dialog to change the pen color
void Window::penColor()
{
    // Store the chosen color from the dialog
    QColor newColor = QColorDialog::getColor(draw->penColor());

    // If a valid color set it
    if (newColor.isValid())
        draw->setPenColor(newColor);

}


// Define menu actions that call functions
void Window::createActions()
{


    // Create pen color action and tie to MainWindow::penColor()
    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));


    // Create clear screen action and tie to MainWindow::clearImage()
    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            draw, SLOT(clearImage()));

}

// Create the menubar
void Window::createMenus()
{

    // Attach all actions to Options
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);

    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Add menu items to the menubar

    menuBar()->addMenu(optionMenu);

}

