#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QTimer>

class Proyectil : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Proyectil(QGraphicsScene *scene, const QPointF &startPos, const QPointF &targetPos, QGraphicsItem *parent = nullptr);
    virtual ~Proyectil();

public slots:
    virtual void mover() = 0;

protected:
    QPointF targetPos;
    QTimer *timer;
};

#endif // PROYECTIL_H
