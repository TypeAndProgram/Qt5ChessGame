#include "../include/ChessGame/validatepiecemove.h"
#include "../include/ChessGame/chessboard.h"
#include <cmath>

namespace ValidatePieceMove {

    auto validate_pawn(ChessPiece const* pawn, QGraphicsItem const* collider) -> std::tuple<bool, int> {
        auto& squares = pawn->board_->squares_;

        // Handle white pawn movement.
        if (pawn->kind_ == ChessPieceKind::Pawn) {
            if (squares[pawn->row_ + 1][pawn->column_]->pos() == collider->pos())
                return std::make_tuple(true, pawn->row_ + 1);

            else if (squares[pawn->row_ + 2][pawn->column_]->pos() == collider->pos()
                        && !pawn->has_left_start_)
                // Pawns can move 2 squares on their first move.
                return std::make_tuple(true, pawn->row_ + 2);

        } else if (pawn->kind_ == ChessPieceKind::BPawn) {
            // Handle black pawn movement.
            if (squares[pawn->row_ - 1][pawn->column_]->pos() == collider->pos())
                return std::make_tuple(true, pawn->row_ - 1);

            else if (squares[pawn->row_ - 2][pawn->column_]->pos() == collider->pos()
                        && !pawn->has_left_start_)
                // Pawns can move 2 squares on their first move.
                return std::make_tuple(true, pawn->row_ - 2);
        }

        return std::make_tuple(false, pawn->row_);
    }
}
