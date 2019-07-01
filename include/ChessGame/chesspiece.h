#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "pch.h"

enum ChessPieceKind {
    Pawn,
    Rook,
    Bishop,
    Knight,
    King,
    Queen,
    BPawn,
    BRook,
    BBishop,
    BKnight,
    BKing,
    BQueen
};

class ChessPiece : public QGraphicsPixmapItem
{
public:
    ChessPiece(QGraphicsItem *parent = nullptr, std::shared_ptr<QGraphicsScene> scene = nullptr);
protected:
    auto mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mousePressEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void override;

    auto handlePieceMove(ChessPieceKind const& pieceName, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handlePawnMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleRookMove() -> void;
    auto handleBishopMove() -> void;
    auto handleKnightMove() -> void;
    auto handleKingMove() -> void;
    auto handleQueenMove() -> void;
    bool dragOver;
public:
    std::shared_ptr<QGraphicsScene> const scene;
    QPointF previousPos;
    ChessPieceKind kind;
    bool hasLeftStart;
};

#endif // CHESSPIECE_H
