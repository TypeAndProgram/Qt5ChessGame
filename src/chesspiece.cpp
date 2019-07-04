#include "../include/ChessGame/chesspiece.hpp"
#include "../include/ChessGame/validatepiecemove.hpp"
#include "../include/ChessGame/chessboard.hpp"

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


auto ChessPiece::handle_move(std::tuple<bool, int> validate_tuple,
                             QGraphicsItem const* collider) -> void {
    if (!std::get<0>(validate_tuple)) {
        setPos(previous_pos_);
        return;
    }

    setPos(collider->pos());
    previous_pos_ = pos();
    has_left_start_ = true;
    row_ = std::get<1>(validate_tuple);
}


auto ChessPiece::handle_move(std::tuple<bool, int, int> validate_tuple,
                             QGraphicsItem const* collider) -> void {
    if (!std::get<0>(validate_tuple)) {
        setPos(previous_pos_);
        return;
    }

    setPos(collider->pos());
    previous_pos_ = pos();
    has_left_start_ = true;
    row_ = std::get<1>(validate_tuple);
    column_ = std::get<2>(validate_tuple);
}


// TODO(smolck): Handle capturing of pieces

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
                // TODO(smolck): Check if the QImage of targeted piece is equal to a certain piece, then verify pawn, then
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
            switch (kind_) {
                case Pawn: case BPawn:
                    handle_move(ValidatePieceMove::validate_pawn(this, colliders[0]),
                                colliders[0]);
                    break;
                case Rook: case BRook:
                    handle_move(ValidatePieceMove::validate_rook(this, colliders[0]),
                                colliders[0]);
                    break;
                // case Bishop: case BBishop:
                //     handle_move(ValidatePieceMove::validate_bishop(this, colliders[0]),
                //                 colliders[0]);
                //     break;
                // case Knight: case BKnight:
                //     handle_move(ValidatePieceMove::validate_knight(this, colliders[0]),
                //                 colliders[0]);
                //     break;
                // case King: case BKing:
                //     handle_move(ValidatePieceMove::validate_king(this, colliders[0]),
                //                 colliders[0]);
                //     break;
                // case Queen: case BQueen:
                //     handle_move(ValidatePieceMove::validate_queen(this, colliders[0]),
                //                 colliders[0]);
                //     break;
            }
            return;
        }

        setPos(previous_pos_);
    }
}
