#include "Particula.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <cmath>

Particula::Particula(QGraphicsView *view, float velIn, qreal xIn, qreal yIn, float theta, QGraphicsItem *parent)
    : QGraphicsItem(parent), posX(xIn), posY(yIn), velIn(velIn), theta(theta),xIn(xIn),yIn(yIn){
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view->size();
    dir = 1;

}

QRectF Particula::boundingRect() const
{
    return QRectF(-5, -5, 20, 20); // Xoordenadas iniciales del rect (sobre el origen del punto), unidades a la derecha y unidades abajo
}

void Particula::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(-5, -5, 10, 10);
    //setPos(xIn,yIn);
}

void Particula::keyPressEvent(QKeyEvent *event)
{
    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_Up:
        moveBy(0, -5);
        break;
    case Qt::Key_Down:
        moveBy(0, 5);
        break;
    case Qt::Key_A:
        qDebug() << "Tecla: " << event->key();
        moveBy(-5, 0);
        break;
    case Qt::Key_D:
        qDebug() << "Tecla: " << event->key();
        moveBy(5, 0);
        break;
    case Qt::Key_W:
        qDebug() << "Tecla: " << event->key();
        moveBy(0, -5);
        break;
    case Qt::Key_S:
        qDebug() << "Tecla: " << event->key();
        moveBy(0, 5);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Particula::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}



void Particula::movParabolico(float* dt)
{
    float posAntX = posX;
    float posAntY = posY;
    posX = xIn + (velIn * cos(theta) * *dt)*dir;
    posY = yIn + (velIn * sin(theta) * *dt) + (0.5 * 9.8 * *dt * *dt);
    if (posX>viewRect.width()-5||posX<0){
        velIn=0.8*velIn;
        dir = -1*dir;
        xIn = posX + 6*dir;
        *dt = 0;
        yIn = posY;
        qDebug()<<xIn;
        //posX = posAntX;
    }
    if (posY>viewRect.height()-5||posY<0){

        theta = 90 - atan2((velIn*cos(theta)),velIn*sin(theta) - 9.8* *dt);
        velIn = 0.8*velIn;
        *dt = 0;
        posY = posAntY-5;
        yIn = posAntY-5;
        xIn = posX;
        //velIn=0.8*velIn;
    }

    qDebug()<<posX<<posY<<theta<<velIn<<*dt<<dir<<velIn*cos(theta)<<velIn*sin(theta) - 9.8* *dt;

    setPos(posX, posY);
}
