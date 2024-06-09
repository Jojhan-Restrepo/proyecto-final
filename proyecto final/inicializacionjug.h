#ifndef INICIALIZACIONJUG_H
#define INICIALIZACIONJUG_H
#include "Jugador.h"

class inicializacionjug : public Jugador {
public:
    inicializacionjug(QGraphicsView *view, QGraphicsItem *parent = nullptr)
        : Jugador(view, parent) {}

    // Implementa los métodos virtuales puros de Jugador aquí si los hay
};
#endif // INICIALIZACIONJUG_H
