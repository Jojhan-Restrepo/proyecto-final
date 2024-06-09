#include "trampas.h"
#include <QObject> // Incluye la definición de QObject
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <cmath>
#include <QTimer>

Trampas::Trampas(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), // Usamos QGraphicsPixmapItem en lugar de QGraphicsRectItem para trabajar con imágenes
    imagePath("C:/Users/JojhanSebastian/Downloads/Soldier_1/trampa.png") {
    // Cargar la imagen desde el archivo
    QPixmap trampaImage(imagePath);
    // Escalar la imagen si es necesario
    trampaImage = trampaImage.scaled(width, height);
    // Establecer la imagen en la trampa
    setPixmap(trampaImage);
    // Establecer la posición de la trampa
    setPos(x, y);

    // Crear un QTimer para gestionar la lógica de la trampa (si es necesario)
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Trampas::aumentarContador);
    timer->start(100); // Cambia el intervalo según lo necesites
}

void Trampas::setSprite(int spriteIndex) {
    float spriteWidth = 56.07;
    int spriteHeight = 87;
    float scaledWidth = 56.07;
    int scaledHeight = 87;
    int spriteX = spriteWidth * spriteIndex;
    int spriteY = 0; // Suponiendo que todas las imágenes están en la misma fila y no necesitas cambiar la posición Y

    QPixmap sprite("C:/Users/JojhanSebastian/Downloads/Soldier_1/trampa.png");
    QPixmap scaledSprite = sprite.copy(spriteX, spriteY, spriteWidth, spriteHeight)
                               .scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledSprite);
}
void Trampas::aumentarContador() {
    // Incrementa el contador
    cont++;

    // Aquí puedes realizar otras acciones si es necesario

    // Por ejemplo, cambiar el sprite de la trampa cada vez que el contador aumente
    setSprite(cont % 13); // Cambia el sprite según el valor actual del contador
}

