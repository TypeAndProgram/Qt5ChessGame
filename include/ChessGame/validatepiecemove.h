#ifndef VALIDATEPIECEMOVE_H
#define VALIDATEPIECEMOVE_H

#include "chesspiece.h"
#include "pch.h"

namespace ValidatePieceMove
{
    // auto validatePawnCapture(ChessPiece const* pawn, std::unique_ptr<ChessPiece> collider) -> std::tuple<bool, int>;

    auto validatePawn(ChessPiece const* pawn, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validateRook(ChessPiece const* rook, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validateBishop(ChessPiece const* bishop, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validateKnight(ChessPiece const* knight, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validateKing(ChessPiece const* king, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validateQueen(ChessPiece const* queen, QGraphicsItem const* collider) -> std::tuple<bool, int>;
};

#endif // VALIDATEPIECEMOVE_H
