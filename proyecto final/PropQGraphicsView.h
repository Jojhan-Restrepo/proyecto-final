#ifndef PROPQGRAPHICSVIEW_H
#define PROPQGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsItem>

class PropQGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    PropQGraphicsView(QWidget *parent = nullptr);
    void setPlayerItem(QGraphicsItem *item);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsItem *playerItem;
};
#endif // PROPQGRAPHICSVIEW_H
