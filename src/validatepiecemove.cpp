#include "../include/ChessGame/validatepiecemove.h"
#include "../include/ChessGame/chessboard.h"

namespace ValidatePieceMove {
    auto validatePawn(std::unique_ptr<ChessPiece> pawn, std::unique_ptr<QGraphicsItem> collider) -> void {
    }
}

// TODO: Implement "en Passant" capturing for pawns
// bool ValidatePieceMove::verifyPawnCapture(ChessPiece *pawn, ChessPiece* collider) {
//
//     int previousX = static_cast<int>(pawn->getPreviousPos().x());
//     int previousY = static_cast<int>(pawn->getPreviousPos().y());
//     QPointF destinationPoint = collider->pos();
//
//     QString pawnColor = pawn->getPieceName() == "Pawn" ? "white" : "black";
//     QString colliderColor = collider->getPieceName().at(0) == "B" &&
//         collider->getPieceName().at(1) == "_" ? "black" : "white";
//
//     if (pawnColor == "white")
//         if (colliderColor == "black") {
//             if (collider->getPieceName() == "B_King")
//                 return false;
//            // Verify white pawn capturing
//             if (destinationPoint.x() == previousX + 80 || destinationPoint.x() == previousX - 80)
//                 if (destinationPoint.y() == previousY + 80)
//                     return true;
//         }
//
//     if (pawnColor == "black")
//         if (colliderColor == "white") {
//             if (collider->getPieceName() == "King")
//                 return false;
//
//
//             if (destinationPoint.x() == previousX + 80 || destinationPoint.x() == previousX - 80)
//                 if (destinationPoint.y() == previousY - 80)
//                     return true;
//         }
//     return false;
// }
//
// bool ValidatePieceMove::verifyPawn(ChessPiece *pawn, QGraphicsItem* collider) {
//     int previousX = static_cast<int>(pawn->getPreviousPos().x());
//     int previousY = static_cast<int>(pawn->getPreviousPos().y());
//     QPointF destinationPoint = collider->pos();
//
//     if (!pawn->hasLeftStart && pawn->getPieceName() == "Pawn") {
//         if (destinationPoint == QPointF(previousX, previousY + 80) ||
//                 destinationPoint == QPointF(previousX, previousY + 160)) {
//             return true;
//         }
//     }
//
//     // Execute this if pawn has already left start.
//     if (destinationPoint == QPointF(previousX, previousY + 80) && pawn->getPieceName() == "Pawn") {
//         return true;
//     }
//
//     if (!pawn->hasLeftStart && pawn->getPieceName() == "B_Pawn") {
//
//         if (destinationPoint == QPointF(previousX, previousY - 80) || destinationPoint ==
//                 QPointF(previousX, previousY - 160)) {
//             return true;
//         }
//     }
//
//     if (destinationPoint == QPointF(previousX, previousY - 80) && pawn->getPieceName() == "B_Pawn") {
//         return true;
//     }
//
//     return false;
// }
//
// bool ValidatePieceMove::verifyRook(ChessPiece *rook, QList<QGraphicsItem*> colliders) {
//     QPointF destinationPoint = colliders[0]->pos();
//     int previousX = static_cast<int>(rook->getPreviousPos().x());
//     int previousY = static_cast<int>(rook->getPreviousPos().y());
//
//     for (int i = 1; i < 9; i++) {
//         if (destinationPoint == QPointF(previousX + (80 * i), previousY) ||
//                 destinationPoint == QPointF(previousX - (80 * i), previousY)) {
//             return true;
//         }
//
//         if (destinationPoint == QPointF(previousX, previousY + (80 * i)) ||
//                 destinationPoint == QPointF(previousX, previousY - (80 * i))) {
//             return true;
//         }
//     }
//     return false;
// }
//
// bool ValidatePieceMove::verifyBishop(ChessPiece *bishop, QList<QGraphicsItem*> colliders) {
//     QPointF destinationPoint = colliders[0]->pos();
//     int previousX = static_cast<int>(bishop->getPreviousPos().x());
//     int previousY = static_cast<int>(bishop->getPreviousPos().y());
//
//     for (int i = 1; i < 9; i++) {
//         if (destinationPoint == QPointF(previousX + (80 * i), previousY - (80 * i)) ||
//                 destinationPoint == QPointF(previousX + (80 * i), previousY + (80 * i))) {
//             return true;
//         }
//
//         if (destinationPoint == QPointF(previousX - (80 * i), previousY + (80 * i)) ||
//                 destinationPoint == QPointF(previousX - (80 * i), previousY - (80 * i))) {
//             return true;
//         }
//     }
//     return false;
// }
//
// bool ValidatePieceMove::verifyKnight(ChessPiece *knight, QList<QGraphicsItem*> colliders) {
//     QPointF destinationPoint = colliders[0]->pos();
//     int previousX = static_cast<int>(knight->getPreviousPos().x());
//     int previousY = static_cast<int>(knight->getPreviousPos().y());
//
//     if (destinationPoint == QPointF(previousX - 80, previousY + 160) ||
//             destinationPoint == QPointF(previousX - 80, previousY - 160)) {
//         return true;
//     }
//
//     if (destinationPoint == QPointF(previousX + 80, previousY + 160) ||
//             destinationPoint == QPointF(previousX + 80, previousY - 160)) {
//         return true;
//     }
//
//     if (destinationPoint == QPointF(previousX + 160, previousY + 80) ||
//             destinationPoint == QPointF(previousX + 160, previousY - 80)) {
//         return true;
//     }
//
//     if (destinationPoint == QPointF(previousX - 160, previousY - 80) ||
//             destinationPoint == QPointF(previousX - 160, previousY + 80)) {
//         return true;
//     }
//     return false;
// }
//
// bool ValidatePieceMove::verifyKing(ChessPiece *king, QList<QGraphicsItem*> colliders) {
//     int previousX = static_cast<int>(king->getPreviousPos().x());
//     int previousY = static_cast<int>(king->getPreviousPos().y());
//     int destinationX = static_cast<int>(colliders[0]->pos().x());
//     int destinationY = static_cast<int>(colliders[0]->pos().y());
//
//     if (destinationX == previousX) {
//         if (destinationY == previousY + 80 || destinationY == previousY - 80) {
//             return true;
//         }
//     }
//
//     if (destinationY == previousY) {
//         if (destinationX == previousX + 80 || destinationX == previousX - 80) {
//             return true;
//         }
//     }
//
//     if (destinationX == previousX + 80 || destinationX == previousX - 80) {
//         if (destinationY == previousY + 80 || destinationY == previousY - 80) {
//             return true;
//         }
//     }
//     return false;
// }
//
// bool ValidatePieceMove::verifyQueen(ChessPiece *queen, QList<QGraphicsItem*> colliders) {
//     QPointF destinationPoint = colliders[0]->pos();
//     int previousX = static_cast<int>(queen->getPreviousPos().x());
//     int previousY = static_cast<int>(queen->getPreviousPos().y());
//
//     for (int i = 1; i < 9; i++) {
//        if (destinationPoint == QPointF(previousX + (80 * i), previousY) ||
//                destinationPoint == QPointF(previousX - (80 * i), previousY)) {
//            return true;
//        }
//
//        if (destinationPoint == QPointF(previousX, previousY + (80 * i)) ||
//                destinationPoint == QPointF(previousX, previousY - (80 * i))) {
//            return true;
//        }
//
//        if (destinationPoint == QPointF(previousX + (80 * i), previousY - (80 * i)) ||
//               destinationPoint == QPointF(previousX + (80 * i), previousY + (80 * i))) {
//            return true;
//        }
//
//        if (destinationPoint == QPointF(previousX - (80 * i), previousY + (80 * i)) ||
//                destinationPoint == QPointF(previousX - (80 * i), previousY - (80 * i))) {
//            return true;
//        }
//    }
//     return false;
// }
