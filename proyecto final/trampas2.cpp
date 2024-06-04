#include "trampas2.h"
#include "Jugador.h" // Incluir la definición completa de la clase Jugador
#include <QGraphicsScene>
#include <QPixmap>
#include <cmath>

trampas2::trampas2(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QVector<Jugador*> &jugador, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), angulo(M_PI / 4), longitud(70), velocidadAngular(0), aceleracionAngular(0), gravedad(9.8), puntoAnclajeX(x), puntoAnclajeY(y), jugador(jugador) {
    QPixmap particulaImage(imagePath);
    particulaImage = particulaImage.scaled(width / 2, height / 2); // Escalar la imagen a un tamaño menor
    setPixmap(particulaImage);
    setPos(puntoAnclajeX + longitud * sin(angulo), puntoAnclajeY + longitud * cos(angulo));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &trampas2::actualizarPosicion);
    timer->start(160);
}

void trampas2::actualizarPosicion() {
    aceleracionAngular = (-1 * gravedad / longitud) * sin(angulo);
    velocidadAngular += aceleracionAngular;
    angulo += velocidadAngular;

    qreal x = puntoAnclajeX + longitud * sin(angulo);
    qreal y = puntoAnclajeY + longitud * cos(angulo);
    setPos(x, y);

    // Verificar colisiones con el jugador
    for (auto *jugadorItem : jugador) {
        if (collidesWithItem(static_cast<QGraphicsItem*>(jugadorItem))) {
            jugadorItem->incrementarColision();
            if (jugadorItem->getContador() >= 20) {  // Número de golpes necesarios para eliminar al jugador
                emit jugadorHerido();
            }
        }
    }
}
