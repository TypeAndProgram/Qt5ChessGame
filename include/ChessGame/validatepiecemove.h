#ifndef VALIDATEPIECEMOVE_H
#define VALIDATEPIECEMOVE_H

#include "chesspiece.h"
#include "pch.h"

namespace ValidatePieceMove
{
    static auto validatePawnCapture(std::unique_ptr<ChessPiece> pawn, std::unique_ptr<ChessPiece> collider) -> bool;

    static auto validatePawn(std::unique_ptr<ChessPiece> pawn, std::unique_ptr<QGraphicsItem> collider) -> bool;

    // TODO: make these take a single QGraphicsItem
    static auto validateRook(std::unique_ptr<ChessPiece> rook, std::unique_ptr<QGraphicsItem> collider) -> bool;
    static auto validateBishop(std::unique_ptr<ChessPiece> bishop, std::unique_ptr<QGraphicsItem> collider) -> bool;
    static auto validateKnight(std::unique_ptr<ChessPiece> knight, std::unique_ptr<QGraphicsItem> collider) -> bool;
    static auto validateKing(std::unique_ptr<ChessPiece> king, std::unique_ptr<QGraphicsItem> collider) -> bool;
    static auto validateQueen(std::unique_ptr<ChessPiece> queen, std::unique_ptr<QGraphicsItem> collider) -> bool;
};

#endif // VALIDATEPIECEMOVE_H
