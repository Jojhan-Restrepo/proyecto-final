#include "bala.h"
#include "Jugador.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>

Bala::Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, Enemigos *&enem1, QList<QGraphicsRectItem *> &obst)
    : targetPos(targetPos), enem1(enem1), obst(obst) {
    setRect(80, 60, 10, 10);
    setPos(startPos);
    setBrush(QBrush(Qt::green));
    scene->addItem(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bala::mover);
    timer->start(50);
}

void Bala::mover() {
    QPointF posActual = pos();
    QPointF posSig = 0.1 * (targetPos - posActual);
    moveBy(posSig.x(), posSig.y());

    for (int i = 0; i < obst.length(); i++) {
        if (collidesWithItem(obst.at(i))) {
            scene()->removeItem(this);
            delete this;
            timer->stop();
            return;
        }
    }

    if (enem1 && collidesWithItem(enem1)) {
        enem1->incrementarColision();
        if (enem1->getContador() >= 10) {
            scene()->removeItem(enem1);
            delete enem1;
            enem1 = nullptr;  // Establece el puntero a nullptr para evitar accesos futuros
        }
        scene()->removeItem(this);
        delete this;
        timer->stop();
        return;
    }

    if (QPointF(posActual - targetPos).manhattanLength() < 5) {
        scene()->removeItem(this);
        delete this;
        timer->stop();
        return;
    }
}


