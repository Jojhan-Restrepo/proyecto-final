#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "Particula.h"
#include "Jugador.h"
#include "enemigos.h"
#include "Bala.h"
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

private slots:
    void on_pushButton_clicked();
    void startGame();
    void showScores();
    void updateGame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *menuScene;
    QGraphicsScene *gameScene;
    QTimer *timer;
    Particula *bola;
    Jugador *jug1;
    QVector<Enemigos*> enemigos;
    QVector<Trampas*> trampas;
    QVector<Jugador*> jugador;
    QVector<QGraphicsRectItem*> obst;
    qreal tiempoTrans;
    bool clic;

    void initGameScene();
    void movjug(Jugador *jug1);
    void hmov(Particula *bola);
    void enemigomov(Enemigos *enem1);
    void animacionTiro(const QPointF &posTiro);
    void incrementarContador();
    void Trampa(Trampas *trampa);
    void mousePressEvent(QMouseEvent *event);
    void animacionTiroDesdeEnemigo();
};

#endif // MAINWINDOW_H


