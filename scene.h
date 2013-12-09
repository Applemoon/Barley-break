#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>



class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene() : QGraphicsScene() {}

    void shuffle();

public slots:
    void checkWin();

private:
    QPointF getEmptyPlace();
};

#endif // SCENE_H
