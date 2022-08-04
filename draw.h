// A class implement based on Qt to handle UI: mouse interaction and basic interface

#ifndef DRAW_H
#define DRAW_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>

class Draw : public QWidget
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    Draw(QWidget *parent = 0);

    // Handles all events

    void setPenColor(const QColor &newColor);


    // Has the image been modified since last save
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }

public slots:

    // Events to handle
    void clearImage();
    void onSendPos(QPoint point, bool toggle);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    // private function to draw on the whiteboard
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    // private variables
    bool modified;
    bool scribbling;
    QColor myPenColor;
    int myPenWidth;
    QImage image;
    QPoint lastPoint;


signals:
    // Signalling to the Pins (in main)
    void sendPoint(QPoint p, char c);
    void sendClear();
    void sendColour(QColor colour);
};

#endif
