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
//Definir el jugador y la imgen
const qreal Jugador::SALTO_ALTURA = 50; // Altura máxima del salto
const int Jugador::SALTO_DURACION = 100; // Duración del salto en milisegundos
const int Jugador::SALTO_INTERVALO = 10; // Intervalo del temporizador en milisegundos
const qreal Jugador::GRAVEDAD = 0.1;
Jugador::Jugador(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im)
{
    //setPixmap(QPixmap(":/sprites.png"));
    yInicial = y;
    x=0;
    y=80;
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    //sceneRect = scene->sceneRect();
    //qDebug() << scene->sceneRect();
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " "<< sceneRect << " "<<view->size().width();
    bool enSalto = false;
    qreal velocidadVertical = 0;
}

void Jugador::cambiarSprite(const QString &spritePath, int dir) {
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Shot_1.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);
    cont++;
    if(cont == 4) { cont = 0; }
    cont++;
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        // Movimiento a la izquierda
        moveBy(-5, 0);
        setSpriteizquierda(18);
        break;
    case Qt::Key_D:
        // Movimiento a la derecha
        moveBy(5, 0);
        setSpritederecha(18);
        break;
    case Qt::Key_W:
        // Salto solo si no está en otro salto
        if (!enSalto) {
            enSalto = true;
            Salto();
        }
        break;
    case Qt::Key_S:
        // Movimiento hacia abajo
        moveBy(0, 5);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}


void Jugador::moveBy(int dx, int dy)
{
    qreal newX = x + dx;
    qreal newY = y + dy;
    setPos(newX, newY);

    if (newX > 3880 - 80 || newX < 0) {
        newX -= dx;
    }
    if (newY > 85 || newY < 0) {
        newY -= dy;
    }

    bool collisionDetected = false;

    for (QGraphicsItem *item : collidingItems())
    {
        if (dynamic_cast<QGraphicsRectItem *>(item))
        {
            collisionDetected = true;
            break;
        }
    }

    if (collisionDetected)
    {
        setPos(x, y); // Revertir a la posición anterior
    }
    else
    {
        x = newX;
        y = newY;
    }

}

void Jugador::setSpritederecha(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Walk.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);

    cont++;
    if(cont == 7) { cont = 0; }
}
void Jugador::setSpriteizquierda(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 128;
    int scaledWidth = 100;
    int scaledHeight = 100;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Walkiz.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);
    cont++;
    if(cont == 7) { cont = 0; }
}

void Jugador::Salto() {
    dy = -5; // Cambié la velocidad inicial del salto a -5 para que el personaje se mueva hacia arriba más rápidamente
    QTimer *saltoTimer = new QTimer(this);
    connect(saltoTimer, &QTimer::timeout, [=]() {
        moveBy(0, dy);
        dy += GRAVEDAD; // Agregué la gravedad al dy en cada iteración para simular el efecto de la gravedad
        if (y >= yInicial) { // Detenemos el salto cuando el personaje alcanza el suelo
            y = yInicial;
            enSalto = false;
            saltoTimer->stop();
            delete saltoTimer;
        }
    });
    saltoTimer->start(20);
}

void Jugador::Caer() {
    enSalto = false;
}

void Jugador::ActualizarPosicionVertical() {
    if (enSalto) {
        velocidadVertical += GRAVEDAD; // Aplica la gravedad
        qreal nuevaY = y + velocidadVertical; // Calcula la nueva posición vertical
        if (nuevaY > yInicial) { // Detiene el salto al alcanzar la altura inicial
            nuevaY = yInicial;
            velocidadVertical = 0;
            enSalto = false;
        }
        setY(nuevaY);
    }
}



