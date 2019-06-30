#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/chesspiece.h"

// TODO: Make the chessboard orientation user configurable,
// i.e. white/black pieces on top/bottom.

ChessBoard::ChessBoard(std::shared_ptr<QGraphicsScene> scene)
    : scene(scene), m_squares(drawRects()) {
    for (auto i = 0; i < 16; i++) {
        m_whitePieces[i] = std::make_unique<ChessPiece>(nullptr, scene);
        m_blackPieces[i] = std::make_unique<ChessPiece>(nullptr, scene);
    }
}


auto ChessBoard::setPieceProperties(std::unique_ptr<ChessPiece>& piece,
                                    QString const& name,
                                    QPointF const& pos) -> void {
    QString pathString = "../../assets/pieces/";
    pathString += (name.trimmed() + ".png");
    piece->setPixmap(QPixmap(pathString).scaled(80, 80));
    piece->setPos(pos);
    piece->name = name;
}


auto ChessBoard::drawRect(QBrush const& brush,
                          int const& index,
                          bool const& needsNewLine,
                          int &previousX,
                          int &previousY) -> std::unique_ptr<QGraphicsRectItem> {

    QRect rect;
    rect.setWidth(80);
    rect.setHeight(80);
    auto rectItem = scene->addRect(rect);
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
        setPieceProperties(m_whitePieces[index], "Pawn", m_squares[1][index]->pos());
        setPieceProperties(m_blackPieces[index], "B_Pawn", m_squares[6][index]->pos());

        scene->addItem(m_whitePieces[index].get());
        scene->addItem(m_blackPieces[index].get());
    }
}


auto ChessBoard::drawWhitePieces() -> void {
    setPieceProperties(m_whitePieces[8], "Rook", m_squares[0][0]->pos());
    setPieceProperties(m_whitePieces[15], "Rook", m_squares[0][7]->pos());

    setPieceProperties(m_whitePieces[9], "Knight", m_squares[0][1]->pos());
    setPieceProperties(m_whitePieces[14], "Knight", m_squares[0][6]->pos());

    setPieceProperties(m_whitePieces[10], "Bishop", m_squares[0][2]->pos());
    setPieceProperties(m_whitePieces[13], "Bishop", m_squares[0][5]->pos());

    setPieceProperties(m_whitePieces[11], "King", m_squares[0][3]->pos());
    setPieceProperties(m_whitePieces[12], "Queen", m_squares[0][4]->scenePos());
    for (auto i = 8; i < 16; i++) {
        scene->addItem(m_whitePieces[i].get());
    }
}


auto ChessBoard::drawBlackPieces() -> void {
    setPieceProperties(m_blackPieces[8], "B_Rook", m_squares[7][0]->pos());
    setPieceProperties(m_blackPieces[15], "B_Rook", m_squares[7][7]->pos());

    setPieceProperties(m_blackPieces[9], "B_Knight", m_squares[7][1]->pos());
    setPieceProperties(m_blackPieces[14], "B_Knight", m_squares[7][6]->pos());

    setPieceProperties(m_blackPieces[10], "B_Bishop", m_squares[7][2]->pos());
    setPieceProperties(m_blackPieces[13], "B_Bishop", m_squares[7][5]->pos());

    setPieceProperties(m_blackPieces[11], "B_King", m_squares[7][3]->pos());
    setPieceProperties(m_blackPieces[12], "B_Queen", m_squares[7][4]->pos());
    for (auto i = 8; i < 16; i++) {
        scene->addItem(m_blackPieces[i].get());
    }
}


auto ChessBoard::draw() -> void
{
    drawPawns();

    // TODO: Have numbers associated with the pieces.
    drawWhitePieces();
    drawBlackPieces();
}
