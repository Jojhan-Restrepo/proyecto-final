#include "Enemigos.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include "Bala.h"
#include "Jugador.h"
#include "BalaEnemigo.h"
#include <cmath>
#include <cstdlib>

Enemigos::Enemigos(QGraphicsView *view, qreal startX, qreal startY, QGraphicsItem *im)
    : Entidad(view, im), movingRight(true), direccion(1), flag(true), cont(0), contadorColisiones(0), velocidadX(5), velocidadY(0) {
    x = startX;
    y = startY;
    setFlag(QGraphicsItem::ItemIsFocusable);
    viewRect = view->size();
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
    setPos(x, y);
}

Enemigos::Enemigos(const Enemigos &other, qreal newX, qreal newY)
    : Entidad(other.scene()->views().first(), other.parentItem()), movingRight(other.movingRight), direccion(other.direccion),
    flag(other.flag), cont(other.cont), contadorColisiones(0), velocidadX(other.velocidadX),
    velocidadY(other.velocidadY) {
    x = newX;
    y = newY;
    spriteSheet = other.spriteSheet;
    spriteX = other.spriteX;
    spriteY = other.spriteY;
    setPixmap(other.pixmap());
    setPos(newX, newY);
}

void Enemigos::mover(int dx, int dy) {
    moveBy(dx, dy);
}

void Enemigos::moveBy(int dx, int dy) {
    qreal newX = x + (movingRight ? dx : -dx);
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
        movingRight = !movingRight;
        newX = x + (movingRight ? dx : -dx);
    }

    if (newX >= 3880 - 80 || newX <= 0) {
        movingRight = !movingRight;
        newX = x + (movingRight ? dx : -dx);
    }

    if (movingRight) {
        setSpritederecha(0);
    } else {
        setSpriteizquierda(0);
    }

    setPos(newX, newY);
    x = newX;
    y = newY;
}

void Enemigos::incrementarColision() {
    contadorColisiones++;
}

int Enemigos::getContador() const {
    return contadorColisiones;
}

void Enemigos::setSpritederecha(int dir) {
    int spriteWidth = 128;
    int spriteHeight = 69;
    int scaledWidth = 100;
    int scaledHeight = 69;
    spriteX = spriteWidth * cont;
    spriteY = dir;
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledSprite);
    cont++;
    if (cont == 8) {
        cont = 0;
    }
}

void Enemigos::setSpriteizquierda(int dir) {
    int spriteWidth = 128;
    int spriteHeight = 68;
    int scaledWidth = 100;
    int scaledHeight = 68;
    spriteX = spriteWidth * cont;
    spriteY = dir;
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walkiz.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledSprite);
    cont++;
    if (cont == 8) {
        cont = 0;
    }
}
