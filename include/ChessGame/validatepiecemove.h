#ifndef VALIDATEPIECEMOVE_H
#define VALIDATEPIECEMOVE_H

#include "chesspiece.h"
#include "pch.h"

namespace ValidatePieceMove
{
    // auto validatePawnCapture(std::unique_ptr<ChessPiece> pawn, std::unique_ptr<ChessPiece> collider) -> void;

    auto validatePawn(std::unique_ptr<ChessPiece> pawn, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto validateRook(std::unique_ptr<ChessPiece> rook, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto validateBishop(std::unique_ptr<ChessPiece> bishop, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto validateKnight(std::unique_ptr<ChessPiece> knight, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto validateKing(std::unique_ptr<ChessPiece> king, std::unique_ptr<QGraphicsItem> collider) -> void;
    auto validateQueen(std::unique_ptr<ChessPiece> queen, std::unique_ptr<QGraphicsItem> collider) -> void;
};

#endif // VALIDATEPIECEMOVE_H
