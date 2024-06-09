#ifndef PARTICULA_H
#define PARTICULA_H

#include <QGraphicsItem>
#include <QGraphicsView>

class QTimer;

class Particula : public QGraphicsItem //Hereda de
{
public:
    Particula(QGraphicsView *view, float velIn,qreal xIn, qreal yIn, float theta, QGraphicsItem *parent = nullptr); //Es un constructor que puede tomar un puntero a un padre

    QRectF boundingRect() const override; //sobrecarga un método de la clase padre, que entrega las coordenadas del rectángulo que engloba la partícula
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override; //otra sobrecarga

    // Reimplementación del evento Keypress
    void keyPressEvent(QKeyEvent *event) override;

    // Movimiento
    void moveBy(int dx, int dy);
    void movParabolico(float* dt);

private: //Podrían ser públicas
    qreal posX;
    qreal posY;
    QSize viewRect;
    float velIn, theta,dir;
    qreal xIn, yIn;
    QTimer *timer; //Objeto que permite manejar eventos repetitivos


private slots:
void movimiento(); //Los slots son miembros de una clase que se pueden conectar a señales, eventos, emitidos por objetos
};

#endif // PARTICULA_H

