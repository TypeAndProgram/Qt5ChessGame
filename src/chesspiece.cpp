#include "../include/ChessGame/chesspiece.h"
#include "../include/ChessGame/validatepiecemove.h"
#include "../include/ChessGame/chessboard.h"

#include <QList>
#include <memory>
#include <QProcess>

ChessPiece::ChessPiece(QGraphicsItem *parent,
                       std::shared_ptr<QGraphicsScene> const scene,
                       ChessBoard const *board)
    : QGraphicsPixmapItem(parent), dragOver(false), scene(scene), board(board)
{
    setAcceptDrops(true);
}


auto ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event) -> void
{
    // Set the previous position of the chesspiece equal to its current position
    // To prepare for it to be moved
    previousPos = pos();
    Q_UNUSED(event)
}


auto ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event) -> void
{
    // Move the pawn with the cursor as it drags the pawn
    QPointF lastPoint = mapToScene(event->lastPos());
    setPos(lastPoint.x() + -30, lastPoint.y() + -30);
}


auto ChessPiece::handlePieceMove(ChessPieceKind const& pieceKind,
                                 QGraphicsItem const* collider) -> void {
    switch (pieceKind) {
        case Pawn: case BPawn:
            handlePawnMove(collider);
            break;
        case Rook: case BRook:
            handleRookMove(collider);
            break;
        case Bishop: case BBishop:
            handleBishopMove(collider);
            break;
        case Knight: case BKnight:
            handleKnightMove(collider);
            break;
        case King: case BKing:
            handleKingMove(collider);
            break;
        case Queen: case BQueen:
            handleQueenMove(collider);
            break;
    }
}

auto ChessPiece::handlePawnMove(QGraphicsItem const* collider) -> void {
    auto returnTuple = ValidatePieceMove::validatePawn(this, collider);

    if (!std::get<0>(returnTuple)) {
        setPos(previousPos);
        row = std::get<1>(returnTuple);
        return;
    }

    // If the pawn's move is validated,
    // move it and update fields.
    setPos(collider->pos());
    previousPos = pos();
    row = std::get<1>(returnTuple);
    hasLeftStart = true;
}


auto ChessPiece::handleRookMove(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handleBishopMove(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handleKnightMove(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handleKingMove(QGraphicsItem const* collider) -> void {
}


auto ChessPiece::handleQueenMove(QGraphicsItem const* collider) -> void {
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
                hasLeftStart = true;

                scene->removeItem(target);
                qDebug() << "Removed item from board";
                previousPos = pos();

                return;
            }
        }

        if (colliders.length() == 1) {
            handlePieceMove(kind, colliders[0]);
        }
    }
}

