#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/chesspiece.h"

// TODO: Make the chessboard orientation user configurable,
// i.e. white/black pieces on top/bottom.

ChessBoard::ChessBoard(std::shared_ptr<QGraphicsScene> scene)
    : m_scene(scene), squares(drawRects()) {
    for (auto i = 0; i < 16; i++) {
        m_whitePieces[i] = std::make_unique<ChessPiece>(nullptr, m_scene, this);
        m_blackPieces[i] = std::make_unique<ChessPiece>(nullptr, m_scene, this);
    }
}


auto ChessBoard::setPieceProperties(std::unique_ptr<ChessPiece>& piece,
                                    ChessPieceKind const& kind,
                                    QString const& name,
                                    QPointF const& pos,
                                    int row,
                                    int column) -> void {
    QString pathString = "../../assets/pieces/";
    pathString += (name.trimmed() + ".png");
    piece->setPixmap(QPixmap(pathString).scaled(80, 80));
    piece->setPos(pos);
    piece->row = row;
    piece->column = column;
    piece->kind = kind;
}


auto ChessBoard::drawRect(QBrush const& brush,
                          int const& index,
                          bool const& needsNewLine,
                          int &previousX,
                          int &previousY) -> std::unique_ptr<QGraphicsRectItem> {
    QRect rect;
    rect.setWidth(80);
    rect.setHeight(80);
    auto rectItem = m_scene->addRect(rect);
    if (index == 0) {
        rectItem->setPos(-200, -200);
        previousX = -200;
        previousY = -200;
        rectItem->setBrush(brush);
        return std::make_unique<QGraphicsRectItem>(rectItem);
    } else if (needsNewLine) {
        rectItem->setPos(-200, previousY + 80);
        rectItem->setBrush(index % 2 == 0 ?
                           QBrush(Qt::white) : QBrush(Qt::darkGray));
        previousX = -200;
        previousY += 80;
        return std::make_unique<QGraphicsRectItem>(rectItem);
    }

    rectItem->setPos(previousX + 80, previousY);
    rectItem->setBrush(brush);
    previousX += 80;
    return std::make_unique<QGraphicsRectItem>(rectItem);
}


auto ChessBoard::drawRects() -> std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> {
    auto previousX = 0;
    auto previousY = 0;
    QBrush previousBrush;
    std::array<std::array<std::unique_ptr<QGraphicsRectItem>, 8>, 8> squares;

    auto needsNewLine = true;
    for (auto row = 0; row < 8; row++) {
        for (auto column = 0; column < 8; column++) {
            squares[row][column] = drawRect(previousBrush == QBrush(Qt::white) ? QBrush(Qt::darkGray) : QBrush(Qt::white),
                                            // TODO: Make this look better

                                            // If this is the first square,
                                            // this line below indicates it as such.
                                            column == 0 ? row : row + 1,
                                            needsNewLine,
                                            previousX,
                                            previousY);
            previousBrush = squares[row][column]->brush();
            needsNewLine = false;
        }
        needsNewLine = true;
    }

    return squares;
}


auto ChessBoard::drawPawns() -> void {
    for (auto index = 0; index < 8; index++) {
        setPieceProperties(m_whitePieces[index],
                           ChessPieceKind::Pawn,
                           "Pawn",
                           squares[1][index]->pos(),
                           1,
                           index);

        setPieceProperties(m_blackPieces[index],
                           ChessPieceKind::BPawn,
                           "B_Pawn",
                           squares[6][index]->pos(),
                           1,
                           index);

        m_scene->addItem(m_whitePieces[index].get());
        m_scene->addItem(m_blackPieces[index].get());
    }
}


auto ChessBoard::drawWhitePieces() -> void {
    setPieceProperties(m_whitePieces[8], ChessPieceKind::Rook, "Rook",
                       squares[0][0]->pos(), 0, 0);
    setPieceProperties(m_whitePieces[15], ChessPieceKind::Rook, "Rook",
                       squares[0][7]->pos(), 0, 7);

    setPieceProperties(m_whitePieces[9], ChessPieceKind::Knight, "Knight",
                       squares[0][1]->pos(), 0, 1);
    setPieceProperties(m_whitePieces[14], ChessPieceKind::Knight, "Knight",
                       squares[0][6]->pos(), 0, 6);

    setPieceProperties(m_whitePieces[10], ChessPieceKind::Bishop, "Bishop",
                       squares[0][2]->pos(), 0, 2);
    setPieceProperties(m_whitePieces[13], ChessPieceKind::Bishop, "Bishop",
                       squares[0][5]->pos(), 0, 5);

    setPieceProperties(m_whitePieces[11], ChessPieceKind::Bishop, "King",
                       squares[0][3]->pos(), 0, 3);
    setPieceProperties(m_whitePieces[12], ChessPieceKind::Bishop, "Queen",
                       squares[0][4]->scenePos(), 0, 4);
    for (auto i = 8; i < 16; i++) {
        m_scene->addItem(m_whitePieces[i].get());
    }
}


auto ChessBoard::drawBlackPieces() -> void {
    setPieceProperties(m_blackPieces[8], ChessPieceKind::BRook, "B_Rook",
                       squares[7][0]->pos(), 7, 0);
    setPieceProperties(m_blackPieces[15], ChessPieceKind::BRook, "B_Rook",
                       squares[7][7]->pos(), 7, 0);

    setPieceProperties(m_blackPieces[9], ChessPieceKind::BKnight, "B_Knight",
                       squares[7][1]->pos(), 7, 1);
    setPieceProperties(m_blackPieces[14], ChessPieceKind::BKnight, "B_Knight",
                       squares[7][6]->pos(), 7, 6);

    setPieceProperties(m_blackPieces[10], ChessPieceKind::BBishop, "B_Bishop",
                       squares[7][2]->pos(), 7, 2);
    setPieceProperties(m_blackPieces[13], ChessPieceKind::BBishop, "B_Bishop",
                       squares[7][5]->pos(), 7, 5);

    setPieceProperties(m_blackPieces[11], ChessPieceKind::BKing, "B_King",
                       squares[7][3]->pos(), 7, 3);
    setPieceProperties(m_blackPieces[12], ChessPieceKind::BQueen, "B_Queen",
                       squares[7][4]->pos(), 7, 4);

    for (auto i = 8; i < 16; i++) {
        m_scene->addItem(m_blackPieces[i].get());
    }
}


auto ChessBoard::draw() -> void
{
    drawPawns();

    // TODO: Have numbers associated with the pieces.
    drawWhitePieces();
    drawBlackPieces();
}
