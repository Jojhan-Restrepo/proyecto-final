#include "bala.h"
#include <QDebug>

Bala::Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Enemigos*> &enemigos, QList<QGraphicsRectItem *> &obst)
    : targetPos(targetPos), enemigos(enemigos), obst(obst) {
    setRect(70, 20, 10, 10);
    setPos(startPos);
    // Cargar la imagen de la bala desde el archivo
    QPixmap balaImage("C:/Users/JojhanSebastian/Downloads/Soldier_1/corazon.png");
    // Escalar la imagen si es necesario
    balaImage = balaImage.scaled(10, 10); // Escala la imagen al tamaño de la bala
    // Establecer la imagen en la bala
    setBrush(QBrush(balaImage));
    // Establecer el color de la pluma en transparente
    setPen(Qt::NoPen);
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

    for (int i = 0; i < enemigos.size(); i++) {
        Enemigos *enem = enemigos[i];
        if (enem && collidesWithItem(enem)) {
            enem->incrementarColision();
            if (enem->getContador() >= 10) {
                scene()->removeItem(enem);
                delete enem;
                enemigos[i] = nullptr;  // Establece el puntero a nullptr para evitar accesos futuros
            }
            scene()->removeItem(this);
            delete this;
            timer->stop();
            return;
        }
    }

    if (QPointF(posActual - targetPos).manhattanLength() < 5) {
        scene()->removeItem(this);
        delete this;
        timer->stop();
        return;
    }
}



