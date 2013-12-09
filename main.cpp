#include <QApplication>
#include <QDebug>
#include <QGraphicsView>
#include <QTimer>
#include <QSound>
#include <assert.h>

#include "cell.h"
#include "scene.h"
#include "values.h"



int main( int argc, char** argv )
{
    QApplication app( argc, argv );

    Scene *scene = new Scene;
    scene->setSceneRect( 0, 0, BOARD_SIZE * SELL_SIZE, BOARD_SIZE * SELL_SIZE );

    for ( int i = 0; i < BOARD_SIZE*BOARD_SIZE - 1; ++i )
    {
        Cell *cell = new Cell( i + 1, BOARD_SIZE );
        const int col = i % BOARD_SIZE;
        const int row = i / BOARD_SIZE;
        cell->setPos( col * SELL_SIZE, row * SELL_SIZE );
        scene->addItem( cell );
        Cell::connect( cell, SIGNAL( positionChanged() ), scene, SLOT(checkWin()));
    }
    scene->shuffle();

    QGraphicsView view( scene );
    view.setWindowTitle( "Пятнашки" );
    view.setRenderHint( QPainter::Antialiasing );
    view.setCacheMode( QGraphicsView::CacheBackground );
    view.setDragMode( QGraphicsView::NoDrag );
    switch ( THEME )
    {
    case girl_theme:
    {
        view.setBackgroundBrush( QPixmap( ":/images/girl_theme/Images/background.png" ) );
        break;
    }
    case paper_theme:
    {
        view.setBackgroundBrush( QBrush( Qt::lightGray ) );
        break;
    }
    default:
        assert( false );
    }

    view.setFixedSize( scene->width()*1.01, scene->height()*1.01 );
    view.show();

    QSound musicSound( ":/sounds/Sounds/music.wav" );
    musicSound.setLoops( 20 ); // КОСТЫЛЬ
    musicSound.play();

    QTimer timer;
    QObject::connect( &timer, SIGNAL( timeout() ), scene, SLOT( advance() ) );
    timer.start( 1000 / FPS );


    return app.exec();
}
