#ifndef JUGADOR_H
#define JUGADOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Jugador:public QObject,
             public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT
private:
    qreal dy;
    qreal x=200;
    qreal y=200;
    QSize viewRect;
    int dir=1;
    bool flag=true;
    int cont=0;
    int spriteX = 0;
    int spriteY = 120;
    int spriteWidth;
    int spriteHeight;    
    QPixmap sprite;
    QPixmap spriteSheet;
    QString spritePath;
    qreal yInicial;
    bool enSalto;
    qreal velocidadVertical;
    static const qreal SALTO_ALTURA;
    static const int SALTO_DURACION;
    static const int SALTO_INTERVALO;
    static const qreal GRAVEDAD;

public:
    Jugador(QGraphicsView *view,QGraphicsItem* im = 0); //se inicializa con nullptr en el constructor. Valor predeterminado que se asigna al parámetro en caso de que no se proporcione ningún valor al crear un objeto de la clase.
    void keyPressEvent(QKeyEvent *event) override;
    // Movimiento
    void moveBy(int dx, int dy);
    //Simular caminar
    void setSpritederecha(int dir);
    void setSpriteizquierda(int dir);
    void cambiarSprite(const QString &spritePath, int dir);
protected:
    void Salto();
    void Caer();
    void ActualizarPosicionVertical();
};
#endif // JUGADOR_H
