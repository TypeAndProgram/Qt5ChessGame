#ifndef VALIDATEPIECEMOVE_H
#define VALIDATEPIECEMOVE_H

#include "chesspiece.hpp"
#include "pch.hpp"

namespace ValidatePieceMove
{
    // auto validate_pawn_capture(ChessPiece const* pawn, std::unique_ptr<ChessPiece> collider) -> std::tuple<bool, int>;

    auto validate_pawn(ChessPiece const* pawn, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validate_rook(ChessPiece const* rook, QGraphicsItem const* collider) -> std::tuple<bool, int, int>;
    auto validate_bishop(ChessPiece const* bishop, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validate_knight(ChessPiece const* knight, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validate_king(ChessPiece const* king, QGraphicsItem const* collider) -> std::tuple<bool, int>;
    auto validate_queen(ChessPiece const* queen, QGraphicsItem const* collider) -> std::tuple<bool, int>;
};

#endif // VALIDATEPIECEMOVE_H
