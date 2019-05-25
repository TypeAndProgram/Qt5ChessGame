#include "chesspiece.h"
#include "validatepiecemove.h"

#include <QList>
#include <memory>
#include <QProcess>

ChessPiece::ChessPiece(QGraphicsItem *parent) : QGraphicsPixmapItem(parent), dragOver(false)
{
    setAcceptDrops(true);
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Set the previous position of the chesspiece equal to its current position
    // To prepare for it to be moved
    this->setPreviousPos(this->pos());
    Q_UNUSED(event)
}

void ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Move the pawn with the cursor as it drags the pawn
    QPointF lastPoint = mapToScene(event->lastPos());
    this->setPos(lastPoint.x() + -30, lastPoint.y() + -30);
}

// TODO: Handle capturing of pieces

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    QList<QGraphicsItem *> colliders = this->collidingItems();

    // Handle capturing pieces
    if (colliders.length() > 0) {

        foreach(QGraphicsItem * collider, colliders) {
            QGraphicsPixmapItem *target = dynamic_cast<QGraphicsPixmapItem*>(collider);

            if (target)
            {
                // TODO: Check if the QImage of targeted piece is equal to a certain piece, then verify pawn, then 
                // move the piece
                
                if (this->m_Name == "Pawn" || this->m_Name == "B_Pawn") {
                    if (ValidatePieceMove::verifyPawnCapture(this, static_cast<ChessPiece*>(target))) {
                        // Move pawn, remove target, set variables
                        this->setPos(target->pos());
                        this->hasLeftStart = true;
                        this->getPieceScene()->removeItem(target);
                        this->setPreviousPos(this->pos());
                        return;
                    } else {
                        this->setPos(this->getPreviousPos());
                        return;
                    }
                }
                this->setPos(target->pos());
                this->hasLeftStart = true;

                this->getPieceScene()->removeItem(target);
                qDebug() << "Removed item from board";
                this->m_PreviousPos = this->pos();

                return;
            }
        }

 	    // Handle piece movement (one collider means it is a square in this case)
        if (colliders.length() == 1) {

            // Handle pawns
	        if (this->m_Name == "Pawn" || this->m_Name == "B_Pawn") {
                
                // If pawn's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyPawn(this, colliders[0])) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if (!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;
                
                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }

            // Handle rooks
            } else if (this->m_Name == "Rook" || this->m_Name == "B_Rook") {

                // If rook's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyRook(this, colliders)) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if (!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;

                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }
		
            // Handle bishops
            } else if (this->m_Name == "Bishop" || this->m_Name == "B_Bishop") {

                // If bishop's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyBishop(this, colliders)) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if (!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;

                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }

            // Handle knights
            } else if (this->m_Name == "Knight" || this->m_Name == "B_Knight") {

                // If knight's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyKnight(this, colliders)) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if (!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;

                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }

            // Handle kings
            } else if (this->m_Name == "King" || this->m_Name == "B_King") {

                // If knight's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyKing(this, colliders)) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if(!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;

                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }

            // Handle queens
            } else if (this->m_Name == "Queen" || this->m_Name == "B_Queen") {

                // If queen's move is valid, move it to new pos and return
                if (ValidatePieceMove::verifyQueen(this, colliders)) {
                    this->setPos(colliders[0]->pos());
                    this->m_PreviousPos = this->pos();
                    if (!hasLeftStart) {
                        hasLeftStart = true;
                    }
                    return;

                // Else, move it back where it was
                } else {
                    this->setPos(m_PreviousPos);
                    return;
                }
            }

        // Move piece back to its previous position if it is colliding 
        // with more than one piece/square
        } else {
            this->setPos(this->m_PreviousPos);
        }
    }
}

