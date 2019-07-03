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
                                 std::unique_ptr<QGraphicsItem> collider) -> void {
    switch (pieceKind) {
        case Pawn: case BPawn:
            handlePawnMove(std::move(collider));
            break;
        case Rook: case BRook:
            handleRookMove(std::move(collider));
            break;
        case Bishop: case BBishop:
            handleBishopMove(std::move(collider));
            break;
        case Knight: case BKnight:
            handleKnightMove(std::move(collider));
            break;
        case King: case BKing:
            handleKingMove(std::move(collider));
            break;
        case Queen: case BQueen:
            handleQueenMove(std::move(collider));
            break;
    }
}

auto ChessPiece::handlePawnMove(std::unique_ptr<QGraphicsItem> collider) -> void {
    if (!ValidatePieceMove::validatePawn(std::make_unique<ChessPiece>(this),
                                         std::move(collider))) {
        // set pawn to previous pos and return
    }
}


auto ChessPiece::handleRookMove(std::unique_ptr<QGraphicsItem> collider) -> void {
}


auto ChessPiece::handleBishopMove(std::unique_ptr<QGraphicsItem> collider) -> void {
}


auto ChessPiece::handleKnightMove(std::unique_ptr<QGraphicsItem> collider) -> void {
}


auto ChessPiece::handleKingMove(std::unique_ptr<QGraphicsItem> collider) -> void {
}


auto ChessPiece::handleQueenMove(std::unique_ptr<QGraphicsItem> collider) -> void {
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

                // if (kind == ChessPieceKind::Pawn || kind == ChessPieceKind::Pawn) {
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

 	    // Handle piece movement (one collider means it is a square in this case)
        if (colliders.length() == 1) {
            handlePieceMove(kind, std::unique_ptr<QGraphicsItem>(colliders[0]));

            // Handle pawns
	    //     if (name == "Pawn" || name == "B_Pawn") {

        //         // If pawn's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyPawn(this, colliders[0])) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if (!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }

        //     // Handle rooks
        //     } else if (name == "Rook" || name == "B_Rook") {

        //         // If rook's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyRook(this, colliders)) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if (!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }

        //     // Handle bishops
        //     } else if (name == "Bishop" || name == "B_Bishop") {

        //         // If bishop's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyBishop(this, colliders)) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if (!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }

        //     // Handle knights
        //     } else if (name == "Knight" || name == "B_Knight") {

        //         // If knight's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyKnight(this, colliders)) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if (!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }

        //     // Handle kings
        //     } else if (name == "King" || name == "B_King") {

        //         // If knight's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyKing(this, colliders)) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if(!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }

        //     // Handle queens
        //     } else if (name == "Queen" || name == "B_Queen") {

        //         // If queen's move is valid, move it to new pos and return
        //         if (ValidatePieceMove::verifyQueen(this, colliders)) {
        //             setPos(colliders[0]->pos());
        //             previousPos = pos();
        //             if (!hasLeftStart) {
        //                 hasLeftStart = true;
        //             }
        //             return;

        //         // Else, move it back where it was
        //         } else {
        //             setPos(previousPos);
        //             return;
        //         }
        //     }

        // // Move piece back to its previous position if it is colliding
        // // with more than one piece/square
        // } else {
        //     setPos(previousPos);
        // }
        }
    }
}

