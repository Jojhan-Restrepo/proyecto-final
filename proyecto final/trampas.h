#ifndef TRAMPAS_H
#define TRAMPAS_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Trampas : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Trampas(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QGraphicsItem *parent = nullptr);
    void setSprite(int spriteIndex);

private:
    QString imagePath; // Ruta de la imagen de la trampa
    int cont = 0; // Contador para controlar el cambio de sprites

private slots:
    void aumentarContador();
};

#endif // TRAMPAS_H
