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
    auto draw_rect(QBrush const& brush,
                  int const& index,
                  bool const& needs_new_line,
                  int &previous_x,
                  int &previous_y) -> std::unique_ptr<QGraphicsRectItem>;

    static auto set_piece_properties(std::unique_ptr<ChessPiece>& piece,
                                   ChessPieceKind const& kind,
                                   QString const& name,
                                   QPointF const& pos,
                                   int row,
                                   int column) -> void;

    auto draw_rects() -> std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8>;
    auto draw_black_pieces() -> void;
    auto draw_white_pieces() -> void;
    auto draw_pawns() -> void;

private:
    std::shared_ptr<QGraphicsScene> const m_scene;

    std::array<std::unique_ptr<ChessPiece>, 16> m_white_pieces;
    std::array<std::unique_ptr<ChessPiece>, 16> m_black_pieces;
public:
    std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> const squares_;
};

#endif // CHESSBOARD_H
