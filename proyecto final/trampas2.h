#ifndef TRAMPAS2_H
#define TRAMPAS2_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QVector>
#include <QList>

class QGraphicsScene;
class Jugador;

class trampas2 : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    trampas2(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QVector<Jugador*> &jugador, QGraphicsItem *parent = nullptr);

signals:
    void jugadorHerido();

private slots:
    void actualizarPosicion();

private:
    QTimer *timer;
    qreal angulo;
    qreal longitud;
    qreal velocidadAngular;
    qreal aceleracionAngular;
    qreal gravedad;
    qreal puntoAnclajeX;
    qreal puntoAnclajeY;
    QVector<Jugador*> &jugador;
};

#endif // TRAMPAS2_H
