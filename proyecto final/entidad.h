#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QSize>

class Entidad : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Entidad(QGraphicsView *view, QGraphicsItem *parent = nullptr);
    virtual ~Entidad() = default;

    virtual void mover(int dx, int dy) = 0;
    virtual void moveBy(int dx, int dy);

protected:
    qreal x;
    qreal y;
    QSize viewRect;
    int spriteX;
    int spriteY;
    int spriteWidth;
    int spriteHeight;
    QPixmap spriteSheet;
};

#endif // ENTIDAD_H
