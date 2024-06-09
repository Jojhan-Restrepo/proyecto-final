#include "bala.h"
#include <QDebug>
#include <cstdlib>  // Para usar rand()

Bala::Bala(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QVector<Enemigos*> &enemigos, QVector<Jugador*> &jugador, QList<QGraphicsRectItem *> &obst)
    : targetPos(targetPos), enemigos(enemigos), jugador(jugador), obst(obst) {
    if (!scene || enemigos.isEmpty() || jugador.isEmpty() || obst.isEmpty()) {
        qDebug() << "Algunos punteros son nulos.";
        return;
    }
    setRect(70, 20, 10, 10);
    setPos(startPos);

    QPixmap balaImage("C:/Users/JojhanSebastian/Downloads/Soldier_1/corazon.png");
    balaImage = balaImage.scaled(10, 10);
    setBrush(QBrush(balaImage));
    setPen(Qt::NoPen);
    scene->addItem(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bala::mover);
    timer->start(50);
}

void Bala::mover() {
    if (jugador.isEmpty()) {
        timer->stop();
        scene()->removeItem(this);
        delete this;
        return;
    }

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
                qreal newX = rand() % 3880;
                qreal newY = 270;

                Enemigos *nuevoEnemigo = new Enemigos(*enem, newX, newY);
                scene()->addItem(nuevoEnemigo);
                enemigos.append(nuevoEnemigo);

                scene()->removeItem(enem);
                delete enem;
                enemigos[i] = nullptr;
                emit enemigoEliminado(); // Emitir la señal
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
