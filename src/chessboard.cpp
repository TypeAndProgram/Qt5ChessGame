#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/chesspiece.h"

ChessBoard::ChessBoard(std::shared_ptr<QGraphicsScene> scene)
    : scene(scene) {
    for (auto i = 0; i < 16; i++) {
        m_whitePieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, scene));
        m_blackPieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, scene));
    }
}

auto ChessBoard::initRect(QRect rect,
                          QBrush const& brush,
                          int const& index,
                          bool const& needsNewLine,
                          int &previousX,
                          int &previousY) -> std::unique_ptr<QGraphicsRectItem> {

    rect.setWidth(80);
    rect.setHeight(80);
    auto rectItem = scene->addRect(rect);
    if (index == 0) {
        rectItem->setPos(-200, -200);
        previousX = -200;
        previousY = -200;
        rectItem->setBrush(brush);
        return std::unique_ptr<QGraphicsRectItem>(rectItem);
    } else if (needsNewLine) {
        rectItem->setPos(-200, previousY + 80);
        rectItem->setBrush(index % 2 == 0 ?
                           QBrush(Qt::white) : QBrush(Qt::darkGray));
        previousX = -200;
        previousY += 80;
        return std::unique_ptr<QGraphicsRectItem>(rectItem);
    }

    rectItem->setPos(previousX + 80, previousY);
    rectItem->setBrush(brush);
    previousX += 80;
    return std::unique_ptr<QGraphicsRectItem>(rectItem);
}


auto ChessBoard::drawRects() -> void {
    auto previousX = 0;
    auto previousY = 0;
    QBrush previousBrush;
    std::array<std::array<QRect, 8>, 8> squares;

    auto needsNewLine = true;
    for (auto row = 0; row < 8; row++) {
        for (auto column = 0; column < 8; column++) {
            m_squares[row][column] = initRect(squares[row][column],
                                              previousBrush == QBrush(Qt::white) ? QBrush(Qt::darkGray) : QBrush(Qt::white),
                                              // TODO: Make this look better
                                              // If this is the first square,
                                              // indicate it as such.
                                              column == 0 ? row : row + 1,
                                              needsNewLine,
                                              previousX,
                                              previousY);
            previousBrush = m_squares[row][column]->brush();
            needsNewLine = false;
        }
        needsNewLine = true;
    }
}

auto ChessBoard::setPieceProperties(std::unique_ptr<ChessPiece>& piece, QString const& name, QPointF const& pos) -> void {
    QString pathString = "../../assets/pieces/";
    pathString += (name.trimmed() + ".png");
    piece->setPixmap(QPixmap(pathString).scaled(80, 80));
    piece->setPos(pos);
    piece->name = name;
}

auto ChessBoard::drawPawns() -> void {
    auto previousWhitePoint = QPoint(-200, -120);
    auto previousBlackPoint = QPoint(-200, 280);

    for (auto index = 0; index < 8; index++) {
        // TODO: Make this changeable depending on user settings
        // for board orientation.
        setPieceProperties(m_whitePieces[index], "Pawn", previousWhitePoint);
        setPieceProperties(m_blackPieces[index], "B_Pawn", previousBlackPoint);
        // TODO: Verify no memory leaks.
        scene->addItem(m_whitePieces[index].get());
        scene->addItem(m_blackPieces[index].get());

        previousWhitePoint = QPoint(previousWhitePoint.x() + 80, previousWhitePoint.y());
        previousBlackPoint = QPoint(previousBlackPoint.x() + 80, previousBlackPoint.y());
    }
}

auto ChessBoard::drawWhitePieces() -> void {
    // Assert that the squares are initialized.
    for (auto& arr : m_squares)
        for (auto& square : arr)
            Q_ASSERT(square != nullptr);

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
    // Assert that the squares are initialized.
    for (auto& arr : m_squares)
        for (auto& square : arr)
            Q_ASSERT(square != nullptr);

    setPieceProperties(m_blackPieces[8], "B_Rook", m_squares[7][0]->pos());
    qDebug() << m_squares[1][0]->pos();
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

auto ChessBoard::drawPieces() -> void {
    drawPawns();
    // TODO: Have numbers associated with the pieces (not the pawns)
    drawWhitePieces();
    drawBlackPieces();
}

auto ChessBoard::draw() -> void
{
    // Draw the rects for the chessboard
    drawRects();
    drawPieces();
}
