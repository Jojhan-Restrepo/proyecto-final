#include "invocacionjug.h"
#include "Jugador.h"
invocacionjug::invocacionjug(QGraphicsView *view, QObject *parent) : QObject(parent) {
    invocacionjug *jug1 = new invocacionjug(view); // Crea una instancia
    // Realiza cualquier otra inicialización necesaria
}
