#include "../include/ChessGame/validatepiecemove.h"
#include "../include/ChessGame/chessboard.h"
#include <cmath>

namespace ValidatePieceMove {
    auto validatePawn(ChessPiece const* pawn, QGraphicsItem const* collider) -> std::tuple<bool, int> {
        auto& squares = pawn->board->squares;

        // Handle white pawn movement.
        if (pawn->kind == ChessPieceKind::Pawn) {
            if (squares[pawn->row + 1][pawn->column]->pos() == collider->pos())
                return std::make_tuple(true, pawn->row + 1);

            else if (squares[pawn->row + 2][pawn->column]->pos() == collider->pos()
                        && !pawn->hasLeftStart)
                // Pawns can move 2 squares on their first move.
                return std::make_tuple(true, pawn->row + 2);

        } else if (pawn->kind == ChessPieceKind::BPawn) {
            // Handle black pawn movement.
            if (squares[pawn->row - 1][pawn->column]->pos() == collider->pos())
                return std::make_tuple(true, pawn->row - 1);

            else if (squares[pawn->row - 2][pawn->column]->pos() == collider->pos()
                        && !pawn->hasLeftStart)
                // Pawns can move 2 squares on their first move.
                return std::make_tuple(true, pawn->row - 2);
        }

        return std::make_tuple(false, pawn->row);
    }
}
