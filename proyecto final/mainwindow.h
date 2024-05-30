#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Jugador.h"
#include "Particula.h"
#include "enemigos.h"
#include "trampas.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool clic;
    float tiempoTrans;
    int contadormuerte=0;
    void mousePressEvent(QMouseEvent *event);
    void animacionTiro(const QPointF &posTiro);
    void muerte(int contadormuerte, Enemigos *enem1);
    void incrementarContador();
    Jugador *jug1;
    QGraphicsScene *scene;
    Enemigos *enem1;
private slots:
    void on_pushButton_clicked(); //Se crea una vez vamos al slot
    void hmov(Particula *bola);
    void movjug(Jugador *jug1);
    void enemigomov(Enemigos *enem1);
    void Trampa(Trampas *trampa);
    //void enemigomov();
   // void ajustarVista();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QList<QGraphicsRectItem*> obst;
    QVector<Enemigos*> enemigos;
    QVector<Trampas*> trampas;
};
#endif // MAINWINDOW_H
