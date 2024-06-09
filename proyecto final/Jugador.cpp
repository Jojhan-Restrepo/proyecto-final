#include "Jugador.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include "Particula.h"
#include <cmath>
#include <QTimer>
#include <QObject>

const qreal Jugador::SALTO_ALTURA = 30;
const int Jugador::SALTO_DURACION = 80;
const int Jugador::SALTO_INTERVALO = 10;
const qreal Jugador::GRAVEDAD = 0.1;

Jugador::Jugador(QGraphicsView *view, QGraphicsItem *parent)
    : Entidad(view, parent), contadorColisiones(0), enemigosEliminados(0), cont1(0), cont(0) {
    yInicial = 275;
    x = 0;
    y = yInicial;
    setFlag(QGraphicsItem::ItemIsFocusable);
    viewRect = view->size();
    enSalto = false;
    velocidadVertical = 0;
}

void Jugador::incrementarColision() {
    contadorColisiones++;
}

int Jugador::getContador() const {
    return contadorColisiones;
}


void Jugador::cambiarSprite(const QString &spritePath, int dir) {
    int spriteWidth = 128;
    int spriteHeight = 68;
    int scaledWidth = 100;
    int scaledHeight = 68;
    spriteX = spriteWidth * cont1;
    spriteY = dir;
    spriteSheet.load(spritePath);
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);
    cont1++;
    if (cont1 == 4) {
        cont1 = 0;
    }
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        moveBy(-5, 0);
        setSpriteizquierda(0);
        break;
    case Qt::Key_D:
        moveBy(5, 0);
        setSpritederecha(0);
        break;
    case Qt::Key_W:
        iniciarSalto();
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}
void Jugador::mover(int dx, int dy) {
        moveBy(dx,dy);
}
void Jugador::moveBy(int dx, int dy) {
    qreal newX = x + dx;
    qreal newY = y + dy;

    bool collisionDetected = false;
    setPos(newX, newY);
    for (QGraphicsItem *item : collidingItems()) {
        if (dynamic_cast<QGraphicsRectItem *>(item)) {
            collisionDetected = true;
            break;
        }
    }

    if (collisionDetected) {
        setPos(x, y);
    } else {
        if (newX > 3880 - 80) newX = 3880 - 80;
        if (newX < 0) newX = 0;
        if (newY > yInicial) newY = yInicial;
        if (newY < 175) newY = 175;

        setPos(newX, newY);
        x = newX;
        y = newY;
    }
}

void Jugador::setSpritederecha(int dir) {
    int spriteWidth = 128;
    int spriteHeight = 69;
    int scaledWidth = 100;
    int scaledHeight = 69;
    spriteX = spriteWidth * cont;
    spriteY = dir;
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Walk12.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);

    cont++;
    if (cont == 7) {
        cont = 0;
    }
}

void Jugador::setSpriteizquierda(int dir) {
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont;
    spriteY = dir;
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Walkiz.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);
    cont++;
    if (cont == 7) {
        cont = 0;
    }
}

void Jugador::iniciarSalto() {
    if (!enSalto) {
        enSalto = true;
        dy = -5;
        QTimer *saltoTimer = new QTimer();
        QObject::connect(saltoTimer, &QTimer::timeout, [=]() {
            moveBy(0, dy);
            dy += GRAVEDAD;
            if (y >= yInicial) {
                y = yInicial;
                enSalto = false;
                saltoTimer->stop();
                delete saltoTimer;
            }
        });
        saltoTimer->start(20);
    }
}

void Jugador::caer() {
    enSalto = false;
}

void Jugador::actualizarPosicionVertical() {
    if (enSalto) {
        velocidadVertical += GRAVEDAD;
        qreal nuevaY = y + velocidadVertical;
        if (nuevaY > yInicial) {
            nuevaY = yInicial;
            velocidadVertical = 0;
            enSalto = false;
        }
        setY(nuevaY);
    }
}

void Jugador::incrementarEnemigosEliminados() {
    enemigosEliminados++;
}

void Jugador::enemigoEliminado() {
    incrementarEnemigosEliminados();
    qDebug() << "Enemigos eliminados:" << getEnemigos();
}

int Jugador::getEnemigos() const {
    return enemigosEliminados;
}
