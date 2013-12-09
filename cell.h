#ifndef CELL_H
#define CELL_H

#include <QGraphicsObject>
#include <QPainter>



class Cell : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Cell( int val, int boardSize );

    QRectF boundingRect() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget );
    inline int getValue() const { return value; }

    enum dirEnum
    {
        up = 0,
        down = 1,
        left = 2,
        right = 3
    };

public slots:
    void mousePressEvent( QGraphicsSceneMouseEvent *event );

signals:
    void positionChanged();

protected:
    void advance( int phase );

private:
    int value;
    int boardSize;
    bool moving;
    QPointF newPosition;
    QImage frameImage;
    static int framesNumber;
};

#endif // CELL_H
