#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "../../src/mainwindow.h"
#include "chesspiece.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QSize>
#include <QList>

class ChessBoard : public QGraphicsView
{
public:
    ChessBoard(std::shared_ptr<QGraphicsScene> scene);
    auto draw() -> void;

private:
    auto drawRect(QBrush const& brush,
                  int const& index,
                  bool const& needsNewLine,
                  int &previousX,
                  int &previousY) -> std::unique_ptr<QGraphicsRectItem>;

    static auto setPieceProperties(std::unique_ptr<ChessPiece>& piece,
                                   ChessPieceKind const& kind,
                                   QString const& name,
                                   QPointF const& pos,
                                   int row,
                                   int column) -> void;
    auto checkIfNeedsNewLine(int const& index) -> bool;

    auto drawRects() -> std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8>;
    auto drawBlackPieces() -> void;
    auto drawWhitePieces() -> void;
    auto drawPawns() -> void;

private:
    std::shared_ptr<QGraphicsScene> const m_scene;

    std::array<std::unique_ptr<ChessPiece>, 16> m_whitePieces;
    std::array<std::unique_ptr<ChessPiece>, 16> m_blackPieces;
public:
    std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> const squares;
};

#endif // CHESSBOARD_H
