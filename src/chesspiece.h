#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "pch.h"

class ChessPiece : public QGraphicsPixmapItem
{
public:
    ChessPiece(QGraphicsItem *parent = nullptr, std::shared_ptr<QGraphicsScene> scene = nullptr);
protected:
    auto mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mousePressEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void override;
    bool dragOver;
public:
    std::shared_ptr<QGraphicsScene> const scene;
    QPointF previousPos;
    QString name;
   //  inline void setPieceScene(QGraphicsScene *graphicsScene) { m_PieceScene = graphicsScene; }
    //inline QGraphicsScene* getPieceScene() { return m_pieceScene; }
   //  inline QString getPieceName() { return m_Name; }
   //  inline QPointF getPreviousPos() { return m_PreviousPos; }
   //  inline void setPreviousPos(QPointF pos) { m_PreviousPos = pos; }
    bool hasLeftStart;
};

#endif // CHESSPIECE_H
