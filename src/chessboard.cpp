#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/chesspiece.h"

// TODO: Make the chessboard orientation user configurable,
// i.e. white/black pieces on top/bottom.

ChessBoard::ChessBoard(std::shared_ptr<QGraphicsScene> scene)
    : m_scene(scene), squares_(draw_rects()) {
    for (auto i = 0; i < 16; i++) {
        m_white_pieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, m_scene, this));
        m_black_pieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, m_scene, this));
    }
}


auto ChessBoard::set_piece_properties(std::unique_ptr<ChessPiece>& piece,
                                      ChessPieceKind const& kind,
                                      QString const& name,
                                      QPointF const& pos,
                                      int row,
                                      int column) -> void {
    QString pathString = "../../assets/pieces/";
    pathString += (name.trimmed() + ".png");
    piece->setPixmap(QPixmap(pathString).scaled(80, 80));
    piece->setPos(pos);
    piece->row_ = row;
    piece->column_ = column;
    piece->kind_ = kind;
}


auto ChessBoard::draw_rect(QBrush const& brush,
                           int const& index,
                           bool const& needs_new_line,
                           int &previous_y,
                           int &previous_x) -> std::unique_ptr<QGraphicsRectItem> {
    QRect rect;
    rect.setWidth(80);
    rect.setHeight(80);
    auto rect_item = m_scene->addRect(rect);
    if (index == 0) {
        rect_item->setPos(-200, -200);
        previous_x = -200;
        previous_y = -200;
        rect_item->setBrush(brush);
        return std::unique_ptr<QGraphicsRectItem>(rect_item);
    } else if (needs_new_line) {
        rect_item->setPos(-200, previous_y + 80);
        rect_item->setBrush(index % 2 == 0 ?
                           QBrush(Qt::white) : QBrush(Qt::darkGray));
        previous_x = -200;
        previous_y += 80;
        return std::unique_ptr<QGraphicsRectItem>(rect_item);
    }

    rect_item->setPos(previous_x + 80, previous_y);
    rect_item->setBrush(brush);
    previous_x += 80;
    return std::unique_ptr<QGraphicsRectItem>(rect_item);
}


auto ChessBoard::draw_rects() -> std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> {
    auto previous_x = 0;
    auto previous_y = 0;
    QBrush previous_brush;
    std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> squares;

    auto needs_new_line = true;
    for (auto row = 0; row < 8; row++) {
        for (auto column = 0; column < 8; column++) {
            squares[row][column] = draw_rect(previous_brush == QBrush(Qt::white) ? QBrush(Qt::darkGray) : QBrush(Qt::white),
                                             // TODO: Make this look better

                                             // If this is the first square,
                                             // this line below indicates it as such.
                                             column == 0 ? row : row + 1,
                                             needs_new_line,
                                             previous_x,
                                             previous_y);
            previous_brush = squares[row][column]->brush();
            needs_new_line = false;
        }
        needs_new_line = true;
    }

    return squares;
}


auto ChessBoard::draw_pawns() -> void {
    for (auto index = 0; index < 8; index++) {
        set_piece_properties(m_white_pieces[index],
                             ChessPieceKind::Pawn,
                             "Pawn",
                             squares_[1][index]->pos(),
                             1,
                             index);

        set_piece_properties(m_black_pieces[index],
                             ChessPieceKind::BPawn,
                             "B_Pawn",
                             squares_[6][index]->pos(),
                             6,
                             index);

        m_scene->addItem(m_white_pieces[index].get());
        m_scene->addItem(m_black_pieces[index].get());
    }
}


auto ChessBoard::draw_white_pieces() -> void {
    set_piece_properties(m_white_pieces[8], ChessPieceKind::Rook, "Rook",
                         squares_[0][0]->pos(), 0, 0);
    set_piece_properties(m_white_pieces[15], ChessPieceKind::Rook, "Rook",
                         squares_[0][7]->pos(), 0, 7);

    set_piece_properties(m_white_pieces[9], ChessPieceKind::Knight, "Knight",
                         squares_[0][1]->pos(), 0, 1);
    set_piece_properties(m_white_pieces[14], ChessPieceKind::Knight, "Knight",
                         squares_[0][6]->pos(), 0, 6);

    set_piece_properties(m_white_pieces[10], ChessPieceKind::Bishop, "Bishop",
                         squares_[0][2]->pos(), 0, 2);
    set_piece_properties(m_white_pieces[13], ChessPieceKind::Bishop, "Bishop",
                         squares_[0][5]->pos(), 0, 5);

    set_piece_properties(m_white_pieces[11], ChessPieceKind::Bishop, "King",
                         squares_[0][3]->pos(), 0, 3);
    set_piece_properties(m_white_pieces[12], ChessPieceKind::Bishop, "Queen",
                         squares_[0][4]->scenePos(), 0, 4);
    for (auto i = 8; i < 16; i++) {
        m_scene->addItem(m_white_pieces[i].get());
    }
}


auto ChessBoard::draw_black_pieces() -> void {
    set_piece_properties(m_black_pieces[8], ChessPieceKind::BRook, "B_Rook",
                         squares_[7][0]->pos(), 7, 0);
    set_piece_properties(m_black_pieces[15], ChessPieceKind::BRook, "B_Rook",
                         squares_[7][7]->pos(), 7, 7);

    set_piece_properties(m_black_pieces[9], ChessPieceKind::BKnight, "B_Knight",
                         squares_[7][1]->pos(), 7, 1);
    set_piece_properties(m_black_pieces[14], ChessPieceKind::BKnight, "B_Knight",
                         squares_[7][6]->pos(), 7, 6);

    set_piece_properties(m_black_pieces[10], ChessPieceKind::BBishop, "B_Bishop",
                         squares_[7][2]->pos(), 7, 2);
    set_piece_properties(m_black_pieces[13], ChessPieceKind::BBishop, "B_Bishop",
                         squares_[7][5]->pos(), 7, 5);

    set_piece_properties(m_black_pieces[11], ChessPieceKind::BKing, "B_King",
                         squares_[7][3]->pos(), 7, 3);
    set_piece_properties(m_black_pieces[12], ChessPieceKind::BQueen, "B_Queen",
                         squares_[7][4]->pos(), 7, 4);

    for (auto i = 8; i < 16; i++) {
        m_scene->addItem(m_black_pieces[i].get());
    }
}


auto ChessBoard::draw() -> void
{
    draw_pawns();

    // TODO: Have numbers associated with the pieces.
    draw_white_pieces();
    draw_black_pieces();
}
