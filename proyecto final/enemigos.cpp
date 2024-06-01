#include "enemigos.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include "Bala.h"
#include "Jugador.h"
#include "balaenemigo.h"
#include <cmath>
//#include "balaenemigos.h"
//Definir el jugador y la imgen
Enemigos::Enemigos(QGraphicsView *view, qreal startX, qreal startY, QGraphicsItem *im) : QGraphicsPixmapItem(im), x(startX), y(startY)
{
    setFlag(QGraphicsItem::ItemIsFocusable); // Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " " << sceneRect << " " << view->size().width();
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
    velocidadX = 5; // Velocidad de movimiento en el eje x
    velocidadY = 0; // Velocidad de movimiento en el eje y
    movingRight = true;
    setPos(x, y); // Establecer la posición inicial
}
void Enemigos::movimiento(int dx, int dy) {
    qreal newX = x + (movingRight ? dx : -dx);
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
        movingRight = !movingRight; // Cambia la dirección
        newX = x + (movingRight ? dx : -dx); // Ajusta la posición según la nueva dirección
    }

    // Si el enemigo está en los bordes horizontalmente, cambia de dirección
    if (newX >= 3880 - 80 || newX <= 0) {
        movingRight = !movingRight;
        newX = x + (movingRight ? dx : -dx); // Ajusta la posición según la nueva dirección
    }

    // Ajusta el sprite en función de la dirección de movimiento
    if (movingRight) {
        setSpritederecha(0); // Ajusta el sprite para que mire hacia la derecha
    } else {
        setSpriteizquierda(0); // Ajusta el sprite para que mire hacia la izquierda
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
    int spriteHeight = 69;
    int scaledWidth = 100;
    int scaledHeight = 69;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledSprite);
    cont++;
    if(cont == 8) { cont = 0; }
}
void Enemigos::setSpriteizquierda(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 68;
    int scaledWidth = 100;
    int scaledHeight = 68;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walkiz.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);

    cont++;
    if(cont == 8) { cont = 0; }
}
/*void Enemigos::disparar() {
    QPointF startPos = mapToScene(0, 0); // Obtiene la posición del enemigo en relación con la escena
    QPointF targetPos =  Calcula la posición del objetivo, por ejemplo, la posición del jugador ;

    // Crea una nueva instancia de BalaEnemigo y la agrega a la escena
    BalaEnemigo *bala = new BalaEnemigo(scene(), startPos, targetPos, collidingItems());
}*/


