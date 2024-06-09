#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"
#include <QKeyEvent>

class Jugador : public Entidad {
    Q_OBJECT
public:
    explicit Jugador(QGraphicsView *view, QGraphicsItem *parent = nullptr);

    void incrementarColision();
    int getContador() const;
    void cambiarSprite(const QString &spritePath, int dir);
    void incrementarEnemigosEliminados();
    void enemigoEliminado();
    int getEnemigos() const;
    void iniciarSalto();
    void actualizarPosicionVertical();
    void caer();
    void moveBy(int dx, int dy) override;
    void mover(int dx, int dy) override;
protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);

    static const qreal SALTO_ALTURA;
    static const int SALTO_DURACION;
    static const int SALTO_INTERVALO;
    static const qreal GRAVEDAD;

    int contadorColisiones;
    int enemigosEliminados;
    int cont1;
    int cont;
    qreal yInicial;
    bool enSalto;
    qreal velocidadVertical;
    qreal dy;
};

#endif // JUGADOR_H
