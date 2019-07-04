#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "pch.hpp"

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
               ChessBoard const *board = nullptr);
protected:
    auto mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mousePressEvent(QGraphicsSceneMouseEvent *event) -> void override;
    auto mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void override;

    auto handle_move(std::tuple<bool, int> validate_tuple, QGraphicsItem const* collider) -> void;
    auto handle_move(std::tuple<bool, int, int> validate_tuple, QGraphicsItem const* collider) -> void;

    bool dragOver;
public:
    std::shared_ptr<QGraphicsScene> const scene_;
    ChessBoard const *board_;
    QPointF previous_pos_;
    ChessPieceKind kind_;
    int row_;
    int column_;
    bool has_left_start_;
};

#endif // CHESSPIECE_H
