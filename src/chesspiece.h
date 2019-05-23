#ifndef CHESSPIECE_H 
#define CHESSPIECE_H

#include "pch.h"

class ChessPiece : public QGraphicsPixmapItem
{
public:
    ChessPiece(QGraphicsItem *parent = nullptr);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    bool dragOver;
private:
    QGraphicsScene *m_PieceScene;
    QPointF m_PreviousPos;
    QString m_Name;
public:
    inline void setPieceScene(QGraphicsScene *graphicsScene) { m_PieceScene = graphicsScene; }
    inline QGraphicsScene* getPieceScene() { return m_PieceScene; }
    inline void setPieceName(QString pieceName) { m_Name = pieceName; }
    inline QString getPieceName() { return m_Name; }
    inline QPointF getPreviousPos() { return m_PreviousPos; }
    inline void setPreviousPos(QPointF pos) { m_PreviousPos = pos; }
    bool hasLeftStart;
};

#endif // CHESSPIECE_H
