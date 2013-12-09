#include "scene.h"

#include <QMessageBox>
#include <assert.h>
#include <QTime>
#include <QSound>

#include "cell.h"
#include "values.h"



void Scene :: shuffle()
{
    QTime time = QTime::currentTime();
    qsrand( (uint)time.msec() );

    const ulong shuffleSteps = 100000;
    for ( ulong i = 0; i < shuffleSteps; ++i )
    {
        const ushort direction = qrand() % 4;
        QPointF empty = getEmptyPlace();
        const int emptyCol = empty.rx();
        const int emptyRow = empty.ry();
        const uint emptyX = ( emptyCol + 0.5 ) * SELL_SIZE;
        const uint emptyY = ( emptyRow + 0.5 ) * SELL_SIZE;
        QGraphicsItem *cell;
        QPoint movingDirection;

        switch ( direction )
        {
        case Cell::up: //сверху
        {
            if ( emptyRow != 0 )
                movingDirection = QPoint( 0, SELL_SIZE );
            else
                movingDirection = QPoint( 0, -SELL_SIZE );
            break;
        }
        case Cell::right: //справа
        {
            if ( emptyCol + 1 != BOARD_SIZE )
                movingDirection = QPoint( -SELL_SIZE, 0 );
            else
                movingDirection = QPoint( SELL_SIZE, 0 );
            break;
        }
        case Cell::down: //снизу
        {
            if ( emptyRow + 1 != BOARD_SIZE )
                movingDirection = QPoint( 0, -SELL_SIZE );
            else
                movingDirection = QPoint( 0, SELL_SIZE );
            break;
        }
        case Cell::left: //слева
        {
            if ( emptyCol != 0 )
                movingDirection = QPoint( SELL_SIZE, 0 );
            else
                movingDirection = QPoint( -SELL_SIZE, 0 );
            break;
        }
        default:
        {
            assert( false );
        }
        }

        cell = itemAt( emptyX - movingDirection.rx(), emptyY - movingDirection.ry(), QTransform() );
        cell->setPos( cell->mapToParent( movingDirection ) );
    }
}



void Scene :: checkWin()
{
    for ( int i = 1; i < BOARD_SIZE*BOARD_SIZE; ++i )
    {
        const int col = ( i - 1 ) % BOARD_SIZE;
        const int row = ( i - 1 ) / BOARD_SIZE;
        const int x = ( col + 0.5 ) * SELL_SIZE;
        const int y = ( row + 0.5 ) * SELL_SIZE;
        Cell *cell = (Cell *)itemAt( QPointF( x, y ), QTransform() );
        if ( cell )
        {
            if ( cell->getValue() != i )
            {
                return;
            }
        }
        else
        {
            return;
        }
    }

    QSound::play( ":/sounds/Sounds/say_yeaah.wav" );

    QMessageBox msgBox;
    msgBox.setWindowTitle( "Barley break" );
    msgBox.setText( "You win!" );
    msgBox.setStandardButtons( QMessageBox::Ok );
    msgBox.setDefaultButton( QMessageBox::Ok );
    const int ret = msgBox.exec();
    switch (ret)
    {
        case QMessageBox::Ok:
            exit( 0 );
            break;
        default:
            assert( false );
    }
}


QPointF Scene :: getEmptyPlace()
{
    for ( int i = 1; i < BOARD_SIZE*BOARD_SIZE + 1; ++i )
    {
        const int col = ( i - 1 ) % BOARD_SIZE;
        const int row = ( i - 1 ) / BOARD_SIZE;
        const int x = ( col + 0.5 ) * SELL_SIZE;
        const int y = ( row + 0.5 ) * SELL_SIZE;
        Cell *cell = (Cell *)itemAt( QPointF( x, y ), QTransform() );
        if ( !cell )
        {
            return QPointF( col, row );
        }
    }

    assert( false );
    return QPointF();
}
