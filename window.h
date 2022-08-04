#ifndef WINDOW_H
#define WINDOW_H

#include <QList>
#include <QMainWindow>

// ScribbleArea used to paint the image
class Draw;

class Window : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    Window();
    Draw *draw;
protected:
    // Function used to close an event


// The events that can be triggered
private slots:

    void penColor();


private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();

    // Will check if changes have occurred since last save


    // Opens the Save dialog and saves

    // What we'll draw on


    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    // Actions tied to specific file formats

    QAction *penColorAct;

    QAction *clearScreenAct;

};


#endif // WINDOW_H
