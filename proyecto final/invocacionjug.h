#ifndef INVOCACIONJUG_H
#define INVOCACIONJUG_H

#include <QObject>
#include <QGraphicsView>

class invocacionjug : public QObject {
    Q_OBJECT
public:
    explicit invocacionjug(QGraphicsView *view, QObject *parent = nullptr);

signals:

};

#endif // INVOCACIONJUG_H
