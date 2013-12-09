#include "cell.h"

#include <QTime>
#include <QSound>
#include <assert.h>
#include <QGraphicsScene>

#include "values.h"



Cell :: Cell( int val, int bs ) : QGraphicsObject(), value( val ), boardSize( bs ),
    moving( false ), newPosition( QPoint( 0, 0 ) )
{
    switch ( THEME )
    {
    case paper_theme:
    {
        frameImage = QImage( ":/images/paper_theme/Images/cellFrame" + QString::number( 1 + qrand() % FRAMES_NUMBER ) );
        break;
    }
    case girl_theme:
    {
        break;
    }
    default:
        assert( false );
    }
}


QRectF Cell :: boundingRect() const
{
    return QRectF( 0, 0, SELL_SIZE, SELL_SIZE );
}



void Cell :: paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
    if ( value != 0 )
    {
        switch ( THEME )
        {
        case paper_theme:
        {
            const int penWidth = 3;

            painter->drawImage( boundingRect(), QImage( ":/images/paper_theme/Images/cellBackground.png" ) );
            painter->drawImage( boundingRect(), frameImage );

            painter->setPen( QPen( QColor( 0, 29, 113 ) , penWidth ) );
            painter->setFont( QFont( "Comic Sans MS", 40 ) );
            painter->drawText( boundingRect(), Qt::AlignCenter, QString::number( value )  );
            break;
        }
        case girl_theme:
        {
            painter->drawImage( boundingRect(), QImage( ":/images/girl_theme/Images/" + QString::number( value ) + ".png" ) );
            break;
        }
        default:
            assert( false );
        }


    }
}



void Cell :: mousePressEvent( QGraphicsSceneMouseEvent * )
{
    if ( !moving )
    {
        QPointF localCellCenter( SELL_SIZE/2, SELL_SIZE/2 );
        QPointF sceneCellCenter = mapToScene( localCellCenter );

        const bool top = ( localCellCenter.y() == sceneCellCenter.y() );
        const bool left = ( localCellCenter.x() == sceneCellCenter.x() );
        const bool bottom = ( sceneCellCenter.y() == SELL_SIZE * boardSize - SELL_SIZE/2 );
        const bool right = ( sceneCellCenter.x() == SELL_SIZE * boardSize - SELL_SIZE/2 );

        QPointF upCenterPoint( sceneCellCenter.x(), sceneCellCenter.y() - SELL_SIZE );
        QPointF downCenterPoint( sceneCellCenter.x(), sceneCellCenter.y() + SELL_SIZE );
        QPointF leftCenterPoint( sceneCellCenter.x() - SELL_SIZE, sceneCellCenter.y() );
        QPointF rightCenterPoint( sceneCellCenter.x() + SELL_SIZE, sceneCellCenter.y() );

        QList< QGraphicsItem *> cellList;

        if ( !top )
        {
            cellList = scene()->items( upCenterPoint );
            if ( cellList.size() == 0 )
            {
                newPosition = mapToParent( 0, -SELL_SIZE );
                moving = true;
                QSound::play( ":/sounds/Sounds/move.wav" );
            }
        }

        if ( !left )
        {
            cellList = scene()->items( leftCenterPoint );
            if ( cellList.size() == 0 )
            {
                newPosition = mapToParent( -SELL_SIZE, 0 );
                moving = true;
                QSound::play( ":/sounds/Sounds/move.wav" );
            }
        }

        if ( !bottom )
        {
            cellList = scene()->items( downCenterPoint );
            if ( cellList.size() == 0 )
            {
                newPosition = mapToParent( 0, SELL_SIZE );
                moving = true;
                QSound::play( ":/sounds/Sounds/move.wav" );
            }
        }

        if ( !right )
        {
            cellList = scene()->items( rightCenterPoint );
            if ( cellList.size() == 0 )
            {
                newPosition = mapToParent( SELL_SIZE, 0 );
                moving = true;
                QSound::play( ":/sounds/Sounds/move.wav" );
            }
        }
    }
}



void Cell :: advance( int phase )
{
    if ( !phase )
    {
        return;
    }

    if ( moving )
    {
        const float dx = ( newPosition.rx() - mapToParent( 0, 0 ).rx() ) / 4;
        const float dy = ( newPosition.ry() - mapToParent( 0, 0 ).ry() ) / 4;
        const bool stopX = ( abs( dx ) < SELL_SIZE / 200.0 );
        const bool stopY = ( abs( dy ) < SELL_SIZE / 200.0 );
        if ( stopX && stopY )
        {
            setPos( newPosition );
            moving = false;
            emit positionChanged();
        }
        else
        {
            setPos( mapToParent( dx, dy ) );
        }
    }
}
