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
    x=0;
    y=0;
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " "<< sceneRect << " "<<view->size().width();
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_2/Walk.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
}

void Enemigos::movimiento(int dx, int dy)
{
    qreal newX = x + dx;
    qreal newY = y + dy;
    static bool movingRight = true;

    // Si el personaje está en los bordes horizontalmente, cambia de dirección
    if (newX >= 3880 - 80 || newX <= 0) {
        movingRight = !movingRight;
    }

    // Si estamos moviéndonos hacia la derecha, ajusta la posición hacia la derecha
    if (movingRight) {
        newX = x + dx;
        setSpritederecha(18);
    }
    // Si estamos moviéndonos hacia la izquierda, ajusta la posición hacia la izquierda
    else {
        newX = x - dx;
        setSpriteizquierda(18);
    }

    // Si el personaje llega a los bordes superior o inferior, invierte la dirección vertical
    if (newY > 192 || newY < 0) {
        dy = -dy; // Invierte la dirección vertical
        newY = y + dy; // Calcula la nueva posición con la dirección invertida
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
