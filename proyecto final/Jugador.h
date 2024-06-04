#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QObject>

class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Jugador(QGraphicsView *view, QGraphicsItem *parent = nullptr);

    void incrementarColision();
    int getContador() const;
    void cambiarSprite(const QString &spritePath, int dir);
    void incrementarEnemigosEliminados();
    void enemigoEliminado();
    int getEnemigos() const;
    void IniciarSalto();
    void ActualizarPosicionVertical();
    void Caer();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void moveBy(int dx, int dy);

    static const qreal SALTO_ALTURA;
    static const int SALTO_DURACION;
    static const int SALTO_INTERVALO;
    static const qreal GRAVEDAD;

    int contadorColisiones;
    int enemigosEliminados = 0;
    int cont1 = 0;
    int cont = 0;
    int spriteX;
    int spriteY;
    qreal x;
    qreal y;
    qreal yInicial;
    bool enSalto;
    qreal velocidadVertical;
    qreal dy;
    QSize viewRect;
    QPixmap spriteSheet;
};

#endif // JUGADOR_H


