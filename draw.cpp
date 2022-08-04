#include <QtWidgets>

#include "draw.h"

Draw::Draw(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
    myPenColor = Qt::black;
    myPenWidth = 3;
}

void Draw::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
    emit sendColour(newColor);
}

void Draw::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    emit sendClear();
    update();
}

void Draw::onSendPos(QPoint point, bool toggle)
{
    if(toggle){
        drawLineTo(point);
    } else {
        lastPoint = point;
    }
    lastPoint = point;
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint cPoint = event->pos();//return the position of the mouse cursor
        emit sendPoint(cPoint, 'f');
        lastPoint = event->pos();
        scribbling = true;
    }
}

void Draw::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        drawLineTo(event->pos());
        QPoint cPoint = event->pos();
        emit sendPoint(cPoint, 't');
        lastPoint = cPoint;
    }
}

void Draw::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        QPoint cPoint = event->pos();
        scribbling = false;
        emit sendPoint(cPoint, 'f');
    }
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void Draw::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Draw::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawLine(lastPoint, endPoint);

    modified = true;

    int rad = (myPenWidth / 2) + 2;

    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    lastPoint = endPoint;
}

void Draw::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}




