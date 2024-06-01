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

// Definir el jugador y la imagen
const qreal Jugador::SALTO_ALTURA = 30; // Altura máxima del salto
const int Jugador::SALTO_DURACION = 80; // Duración del salto en milisegundos
const int Jugador::SALTO_INTERVALO = 10; // Intervalo del temporizador en milisegundos
const qreal Jugador::GRAVEDAD = 0.1;

Jugador::Jugador(QGraphicsView *view, QGraphicsItem *im) : QGraphicsPixmapItem(im)
{
    // Inicializa el jugador
    yInicial = 275; // Ajusta la posición inicial en Y
    x = 0;
    y = yInicial;
    setFlag(QGraphicsItem::ItemIsFocusable); // Permitir que el jugador reciba eventos del teclado
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " " << sceneRect << " " << view->size().width();
    enSalto = false; // Asegurarse de que enSalto se inicialice correctamente
    velocidadVertical = 0; // Inicializa la velocidad vertical
}

void Jugador::cambiarSprite(const QString &spritePath, int dir) {
    int spriteWidth = 128;
    int spriteHeight = 68;
    int scaledWidth = 100;
    int scaledHeight = 68;
    spriteX = spriteWidth * cont1; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Shot_1.png");
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    QPixmap scaledSprite = sprite.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setPixmap(scaledSprite);
    cont1++;
    if (cont1 == 4) { cont1 = 0; }  // Asegura que el contador se reinicie correctamente
}

void Jugador::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        // Movimiento a la izquierda
        moveBy(-5, 0);
        setSpriteizquierda(0);
        break;
    case Qt::Key_D:
        // Movimiento a la derecha
        moveBy(5, 0);
        setSpritederecha(0);
        break;
    case Qt::Key_W:
        IniciarSalto(); // Iniciar el salto solo cuando se presiona la tecla "W"
        break;
    case Qt::Key_S:
        // Movimiento hacia abajo
        //moveBy(0, 5);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Jugador::moveBy(int dx, int dy)
{
    qreal newX = x + dx;
    qreal newY = y + dy;

    // Verificar colisiones y límites antes de establecer la nueva posición
    bool collisionDetected = false;

    // Verificar colisiones solo en la dirección del movimiento actual
    setPos(newX, newY);
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
        // Si se detecta una colisión, revertir la posición
        setPos(x, y);
    }
    else
    {
        // Aplicar límites de movimiento
        if (newX > 3880 - 80) newX = 3880 - 80;
        if (newX < 0) newX = 0;
        if (newY > yInicial) newY = yInicial; // El jugador no debe ir por debajo del suelo
        if (newY < 175) newY = 175; // Ajustar el límite superior si es necesario

        // Establecer la nueva posición
        setPos(newX, newY);
        x = newX;
        y = newY;
    }
}

void Jugador::setSpritederecha(int dir)
{
    int spriteWidth = 128;
    int spriteHeight = 69;
    int scaledWidth = 100;
    int scaledHeight = 69;
    spriteX = spriteWidth * cont; // Calcula la posición X del sprite actual
    spriteY = dir; // Ajusta la posición Y según la dirección
    spriteSheet.load("C:/Users/JojhanSebastian/Downloads/Soldier_1/Walk12.png");

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

void Jugador::IniciarSalto() {
    if (!enSalto) { // Solo inicia el salto si el jugador no está ya en otro salto
        enSalto = true;
        dy = -5; // Velocidad inicial del salto
        QTimer *saltoTimer = new QTimer(this);
        connect(saltoTimer, &QTimer::timeout, [=]() {
            moveBy(0, dy);
            dy += GRAVEDAD; // Aplica la gravedad
            if (y >= yInicial) { // Detiene el salto cuando el jugador alcanza el suelo
                y = yInicial;
                enSalto = false;
                saltoTimer->stop();
                delete saltoTimer;
            }
        });
        saltoTimer->start(20);
    }
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


