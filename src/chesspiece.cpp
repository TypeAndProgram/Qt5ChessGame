#include "../include/ChessGame/chesspiece.h"
#include "../include/ChessGame/validatepiecemove.h"
#include "../include/ChessGame/chessboard.h"

#include <QList>
#include <memory>
#include <QProcess>

ChessPiece::ChessPiece(QGraphicsItem *parent,
                       std::shared_ptr<QGraphicsScene> const scene,
                       ChessBoard const *board)
    : QGraphicsPixmapItem(parent), dragOver(false), scene_(scene), board_(board)
{
    setAcceptDrops(true);
}


auto ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event) -> void
{
    // Set the previous position of the chesspiece equal to its current position
    // To prepare for it to be moved
    previous_pos_ = pos();
    Q_UNUSED(event)
}


auto ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void
{
    // Move the pawn with the cursor as it drags the pawn
    QPointF lastPoint = mapToScene(event->lastPos());
    setPos(lastPoint.x() + -30, lastPoint.y() + -30);
}


auto ChessPiece::handle_piece_move(ChessPieceKind const& pieceKind,
                                   QGraphicsItem const* collider) -> void {
    switch (pieceKind) {
        case Pawn: case BPawn:
            handle_pawn_move(collider);
            break;
        case Rook: case BRook:
            handle_rook_move(collider);
            break;
        case Bishop: case BBishop:
            handle_bishop_move(collider);
            break;
        case Knight: case BKnight:
            handle_knight_move(collider);
            break;
        case King: case BKing:
            handle_king_move(collider);
            break;
        case Queen: case BQueen:
            handle_queen_move(collider);
            break;
    }
}

auto ChessPiece::handle_pawn_move(QGraphicsItem const* collider) -> void {
    auto returnTuple = ValidatePieceMove::validate_pawn(this, collider);

    if (!std::get<0>(returnTuple)) {
        setPos(previous_pos_);
        row_ = std::get<1>(returnTuple);
        return;
    }

    // If the pawn's move is validated,
    // move it and update fields.
    setPos(collider->pos());
    previous_pos_ = pos();
    row_ = std::get<1>(returnTuple);
    has_left_start_ = true;
}


auto ChessPiece::handle_rook_move(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handle_bishop_move(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handle_knight_move(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handle_king_move(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handle_queen_move(QGraphicsItem const* collider) -> void {
}

// TODO: Handle capturing of pieces

auto ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) -> void
{
    Q_UNUSED(event)
    QList<QGraphicsItem *> colliders = collidingItems();

    // Handle capturing pieces
    if (colliders.length() > 0) {

        foreach(QGraphicsItem * collider, colliders) {
            QGraphicsPixmapItem *target = dynamic_cast<QGraphicsPixmapItem*>(collider);

            if (target)
            {
                // TODO: Check if the QImage of targeted piece is equal to a certain piece, then verify pawn, then
                // move the piece

                // if (kind == ChessPieceKind::Pawn || kind == ChessPieceKind::BPawn) {
                //     if (ValidatePieceMove::validatePawnCapture(std::make_unique<ChessPiece>(this),
                //                                                std::make_unique<ChessPiece>(target))) {
                //         // Move pawn, remove target, set variables
                //         setPos(target->pos());
                //         hasLeftStart = true;
                //         scene->removeItem(target);
                //         previousPos = pos();
                //         return;
                //     } else {
                //         setPos(previousPos);
                //         return;
                //     }
                // }
                setPos(target->pos());
                has_left_start_ = true;

                scene_->removeItem(target);
                qDebug() << "Removed item from board";
                previous_pos_ = pos();

                return;
            }
        }

        if (colliders.length() == 1) {
            handle_piece_move(kind_, colliders[0]);
        }
    }
}

