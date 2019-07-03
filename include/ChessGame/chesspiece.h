#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "pch.h"

class ChessBoard;

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
    ChessPiece(QGraphicsItem *parent = nullptr,
               std::shared_ptr<QGraphicsScene> const scene = nullptr,
               const std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8>* boardSquares = nullptr);
protected:
    auto mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mousePressEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void override;

    auto handlePieceMove(ChessPieceKind const& pieceName, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handlePawnMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleRookMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleBishopMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleKnightMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleKingMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    auto handleQueenMove(std::unique_ptr<QGraphicsItem> collider) -> void;
    bool dragOver;
public:
    std::shared_ptr<QGraphicsScene> const scene;
    const std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8>* boardSquares;
    QPointF previousPos;
    ChessPieceKind kind;
    int row;
    int column;
    bool hasLeftStart;
};

#endif // CHESSPIECE_H
