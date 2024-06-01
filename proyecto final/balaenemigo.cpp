#include "balaenemigo.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include "jugador.h"
#include <QGraphicsRectItem>
#include <QObject>

BalaEnemigo::BalaEnemigo(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Jugador*> &jugador, QList<QGraphicsRectItem *> &obst)
    : targetPos(targetPos), jugador(jugador), obst(obst)
{
    setRect(70, 20, 10, 10);
    setPos(startPos);

    QPixmap balaImage("C:/Users/JojhanSebastian/Downloads/Soldier_1/corazon.png");
    balaImage = balaImage.scaled(10, 10);
    setBrush(QBrush(balaImage));
    setPen(Qt::NoPen);

    scene->addItem(this);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &BalaEnemigo::mover);
    timer->start(50);
}

BalaEnemigo::~BalaEnemigo() {
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void BalaEnemigo::mover() {
    QPointF posActual = pos();
    QPointF direction = targetPos - posActual;

    // Normalize direction
    qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    if (length == 0) {
        return; // Avoid division by zero
    }
    direction /= length;

    // Move 5 units in the direction
    QPointF posSig = 5 * direction;
    moveBy(posSig.x(), posSig.y());

    for (int i = 0; i < obst.size(); i++) {
        if (collidesWithItem(obst.at(i))) {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    for (int i = 0; i < jugador.size(); i++) {
        Jugador *jugadorItem = jugador[i];
        if (jugadorItem && collidesWithItem(jugadorItem)) {
            // Aquí puedes agregar el código adicional que necesites para el jugador
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (QPointF(posActual - targetPos).manhattanLength() < 5) {
        scene()->removeItem(this);
        delete this;
        return;
    }

    if (jugador.isEmpty()) {
        scene()->removeItem(this);
        delete this;
        return;
    }
}
