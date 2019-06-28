#ifndef VALIDATEPIECEMOVE_H
#define VALIDATEPIECEMOVE_H

#include "chesspiece.h"
#include "pch.h"

class ValidatePieceMove
{
public:
    static bool verifyPawnCapture(ChessPiece *pawn, ChessPiece* collider);

    static bool verifyPawn(ChessPiece *pawn, QGraphicsItem* collider);

    // TODO: make these take a single QGraphicsItem*
    static bool verifyRook(ChessPiece *rook, QList<QGraphicsItem*> colliders);
    static bool verifyBishop(ChessPiece *bishop, QList<QGraphicsItem*> colliders);
    static bool verifyKnight(ChessPiece *knight, QList<QGraphicsItem*> colliders);
    static bool verifyKing(ChessPiece *king, QList<QGraphicsItem*> colliders);
    static bool verifyQueen(ChessPiece *queen, QList<QGraphicsItem*> colliders);
};

#endif // VALIDATEPIECEMOVE_H
