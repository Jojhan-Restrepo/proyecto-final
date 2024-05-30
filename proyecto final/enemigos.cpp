#include "enemigos.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>

//Definir el jugador y la imgen
Enemigos::Enemigos(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im)
{
    //x=0;
    //y=0;
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " "<< sceneRect << " "<<view->size().width();
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
    velocidadX = 5; // Velocidad de movimiento en el eje x
    velocidadY = 0; // Velocidad de movimiento en el eje y
    movingRight = true;
}

void Enemigos::movimiento(int dx, int dy) {
    qreal newX = x + dx;
    qreal newY = y + dy;

    bool collisionDetected = false; // Variable para detectar colisiones con otros objetos

    // Verifica si hay colisiones con objetos en la escena
    for (QGraphicsItem *item : collidingItems()) {
        if (dynamic_cast<QGraphicsRectItem *>(item)) {
            collisionDetected = true;
            break;
        }
    }

    // Si hay colisión con algún objeto, invierte la dirección de movimiento
    if (collisionDetected) {
        dx = -dx;
        movingRight = !movingRight; // Cambia la dirección
    }

    // Si el enemigo está en los bordes horizontalmente, cambia de dirección
    if (newX >= 3880 - 80 || newX <= 0) {
        movingRight = !movingRight;
    }

    // Ajusta la posición en función de la dirección de movimiento
    if (movingRight) {
        newX = x + dx;
        setSpritederecha(18); // Ajusta el sprite para que mire hacia la derecha
    } else {
        newX = x - dx;
        setSpriteizquierda(18); // Ajusta el sprite para que mire hacia la izquierda
    }

    // Verifica si hay colisión con los rectángulos y ajusta la posición si es necesario
    QRectF newRect(newX, newY, pixmap().width(), pixmap().height());
    for (QGraphicsItem *item : collidingItems()) {
        if (dynamic_cast<QGraphicsRectItem *>(item)) {
            QRectF intersectedRect = newRect.intersected(item->boundingRect());
            if (!intersectedRect.isEmpty()) {
                if (dx > 0) {
                    newX -= intersectedRect.width();
                } else {
                    newX += intersectedRect.width();
                }
            }
        }
    }

    // Aplica la nueva posición
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
void Enemigos::setSpritederecha(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledSprite);
    cont++;
    if(cont == 7) { cont = 0; }
}
void Enemigos::setSpriteizquierda(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walkiz.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);

    cont++;
    if(cont == 7) { cont = 0; }
}
