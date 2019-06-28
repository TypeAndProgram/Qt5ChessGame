#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/chesspiece.h"

ChessBoard::ChessBoard(std::shared_ptr<QGraphicsScene>& scene)
    : scene(std::make_shared<QGraphicsScene>(scene)) {
    for (auto i = 0; i < 16; i++) {
        m_whitePieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, scene));
        m_blackPieces[i] = std::unique_ptr<ChessPiece>(new ChessPiece(nullptr, scene));
    }
}

// auto ChessBoard::checkIfNeedsNewLine(const int& index) -> bool
// {
//     // Check if there needs to be a new line via the index, return true if so.
//     if (index == 8 || index == 16 || index == 24 || index == 32 || index == 40 || index == 48 || index == 56 || index == 64) {
//         return true;
//     }
//     return false;
// }

auto ChessBoard::initRect(QRect rect,
                          QBrush brush,
                          int index,
                          bool needsNewLine,
                          int &previousX,
                          int &previousY) -> std::unique_ptr<QGraphicsRectItem> {

    rect.setWidth(80);
    rect.setHeight(80);
    auto rectItem = std::unique_ptr<QGraphicsRectItem>(scene->addRect(rect));
    if (index == 0) {
        rectItem->setPos(-200, -200);
        previousX = -200;
        previousY = -200;
        rectItem->setBrush(brush);
        return rectItem;
    } else if (needsNewLine) {
        rectItem->setPos(-200, previousY + 80);
        rectItem->setBrush(brush == QBrush(Qt::white) ?
                           QBrush(Qt::black) : QBrush(Qt::white));
        previousX = -200;
        previousY += 80;
        return rectItem;
    }

    rectItem->setPos(previousX + 80, previousY);
    rectItem->setBrush(brush);
    previousX += 80;
    return rectItem;
}


auto ChessBoard::drawRects() -> void {
    auto previousX = 0;
    auto previousY = 0;
    QBrush previousBrush;
    std::array<std::array<QRect, 8>, 8> squares;

    auto needsNewLine = false;

    for (auto outerIndex = 0; outerIndex < 8; outerIndex++) {
        auto innerArray = squares[outerIndex];

        for (auto innerIndex = 0; innerIndex < 8; innerIndex++) {
            m_squares[outerIndex][innerIndex] = initRect(innerArray[innerIndex],
                                                         innerIndex == 0 ? QBrush(Qt::white) : QBrush(Qt::black),
                                                         innerIndex,
                                                         needsNewLine,
                                                         previousX,
                                                         previousY);
        }
        needsNewLine = true;
    }
}

    // for (int index = 0; index < 64; index++) {
    //     // Set dimensions of the board's squares.
    //     squaresArray[index].setWidth(80);
    //     squaresArray[index].setHeight(80);

    //     if (index == 0) {
    //         // Add first square to this->and set its attributes.
    //         rectItem = this->addRect(squaresArray[index]);
    //         rectItem->setPos(-200, -200);
    //         rectItem->setBrush(QBrush(Qt::white));
    //         previousX = static_cast<int>(rectItem->x());
    //         previousY = static_cast<int>(rectItem->y());
    //         previousBrush = rectItem->brush();
    //         continue;
    //     }

    //     if (checkIfNeedsNewLine(index)) {
    //         // If the current square needs to be on a new line, put it back at the far left of the board, and positioned
    //         // down by one square's length.
    //         rectItem = this->addRect(squaresArray[index]);
    //         rectItem->setPos(-200, previousY + 80);

    //         if (previousBrush == QBrush(Qt::white)) {
    //             rectItem->setBrush(QBrush(Qt::white));
    //         } else {
    //             rectItem->setBrush(QBrush(Qt::gray));
    //         }
    //         previousX = static_cast<int>(rectItem->x());
    //         previousY = static_cast<int>(rectItem->y());
    //         previousBrush = rectItem->brush();
    //         continue;
    //     }

    //     // Add rect to this-> set its pos and brush, and set the previous item to it (only execute if the above two "if's" aren't met).
    //     rectItem = this->addRect(squaresArray[index]);
    //     rectItem->setPos(previousX + 80, previousY);

    //     if (previousBrush == QBrush(Qt::white)) {
    //         rectItem->setBrush(QBrush(Qt::gray));
    //     } else {
    //         rectItem->setBrush(QBrush(Qt::white));
    //     }
    //     previousX = static_cast<int>(rectItem->x());
    //     previousY = static_cast<int>(rectItem->y());
    //     previousBrush = rectItem->brush();
    // }
// }

auto ChessBoard::setPieceProperties(std::unique_ptr<ChessPiece>& piece, QString name, QPoint pos) -> void {
    QString pathString = "ImagesOfPieces/";
    pathString += name.trimmed();
    piece->setPixmap(QPixmap(pathString).scaled(80, 80));
    piece->setPos(pos);
    piece->name = name;
}

auto ChessBoard::drawPawns() -> void {
    auto previousWhitePoint = QPoint(-200, -200);
    auto previousBlackPoint = QPoint(-200, 280);

    for (auto index = 0; index < 8; index++) {
        // TODO: Make this changeable depending on user settings
        // for board orientation.
        setPieceProperties(m_whitePieces[index], "Pawn", previousWhitePoint);
        setPieceProperties(m_blackPieces[index], "Black", previousBlackPoint);
        // TODO: Verify no memory leaks.
        scene->addItem(m_whitePieces[index].get());
        scene->addItem(m_blackPieces[index].get());

        previousWhitePoint = QPoint(previousWhitePoint.x() + 80, previousWhitePoint.y());
        previousBlackPoint = QPoint(previousBlackPoint.x() + 80, previousBlackPoint.y());
    }
}

auto ChessBoard::drawPieces() -> void {
    drawPawns();

    // TODO: Add the other pieces and draw them, and abstract the logic.
    for (auto index = 8; index < 16; index++) {
    }
}

auto ChessBoard::draw() -> void
{
    // Draw the rects for the chessboard
    this->drawRects();
    int previousX = 0, previousY = 0;

    // Set the this->for each of the chesspieces
    for (int index = 0; index < 32; index++) {
        pieces[index].setPieceScene(this);
    }

    for (int i = 0; i < 8; i++) {
        // Set the name and pixmap for each white pawn
        m_pieces[i].setPieceName("Pawn");
        pieces[i].setPixmap(QPixmap("ImagesOfPieces/Pawn.png").scaled(80, 80));

        // Handle the first white pawn
        if (i == 0) {
            pieces[i].setPos(-200, -120);
            previousX = static_cast<int>(pieces[i].x());
            previousY = static_cast<int>(pieces[i].y());
            this->scene()->addItem(&pieces[i]);
            continue;
        }

        // Handle the other white pawns
        pieces[i].setPos(previousX + 80, previousY);
        previousX = static_cast<int>(pieces[i].x());
        previousY = static_cast<int>(pieces[i].y());
        this->addItem(&pieces[i]);
    }

    // Handle the other pieces \/ \/ \/

    pieces[8].setPixmap(QPixmap("ImagesOfPieces/Rook.png").scaled(80, 80));
    pieces[8].setPos(-200, -200);
    pieces[8].setPieceName("Rook");
    this->addItem(&pieces[8]);

    pieces[9].setPixmap(QPixmap("ImagesOfPieces/Rook.png").scaled(80, 80));
    pieces[9].setPos(360, -200);
    pieces[9].setPieceName("Rook");
    this->addItem(&pieces[9]);

    pieces[10].setPixmap(QPixmap("ImagesOfPieces/Knight.png").scaled(80, 80));
    pieces[10].setPos(-120, -200);
    pieces[10].setPieceName("Knight");
    this->addItem(&pieces[10]);

    pieces[11].setPixmap(QPixmap("ImagesOfPieces/Knight.png").scaled(80, 80));
    pieces[11].setPos(280, -200);
    pieces[11].setPieceName("Knight");
    this->addItem(&pieces[11]);

    pieces[12].setPixmap(QPixmap("ImagesOfPieces/Bishop.png").scaled(80, 80));
    pieces[12].setPos(-40, -200);
    pieces[12].setPieceName("Bishop");
    this->addItem(&pieces[12]);

    pieces[13].setPixmap(QPixmap("ImagesOfPieces/Bishop.png").scaled(80, 80));
    pieces[13].setPos(200, -200);
    pieces[13].setPieceName("Bishop");
    this->addItem(&pieces[13]);

    pieces[14].setPixmap(QPixmap("ImagesOfPieces/King.png").scaled(80, 80));
    pieces[14].setPos(40, -200);
    pieces[14].setPieceName("King");
    this->addItem(&pieces[14]);

    pieces[15].setPixmap(QPixmap("ImagesOfPieces/Queen.png").scaled(80, 80));
    pieces[15].setPos(120, -200);
    pieces[15].setPieceName("Queen");
    this->addItem(&pieces[15]);


    for (int i = 16; i < 24; i++) {
	// Set pixmap and names for the black pawns
        pieces[i].setPixmap(QPixmap("ImagesOfPieces/B_Pawn.png").scaled(80, 80));
        pieces[i].setPieceName("B_Pawn");

	// Handle first black pawn
        if (i == 16) {
            pieces[i].setPos(-200, 280);
            previousX = static_cast<int>(pieces[i].x());
            previousY = static_cast<int>(pieces[i].y());
            this->addItem(&pieces[i]);
            continue;
        }

	// Handle other black pawns
        pieces[i].setPos(previousX + 80, previousY);
        previousX = static_cast<int>(pieces[i].x());
        previousY = static_cast<int>(pieces[i].y());
        this->addItem(&pieces[i]);
    }

    pieces[24].setPixmap(QPixmap("ImagesOfPieces/B_Rook.png").scaled(80, 80));
    pieces[24].setPos(-200, 360);
    pieces[24].setPieceName("B_Rook");
    this->addItem(&pieces[24]);

    pieces[25].setPixmap(QPixmap("ImagesOfPieces/B_Rook.png").scaled(80, 80));
    pieces[25].setPos(360, 360);
    pieces[25].setPieceName("B_Rook");
    this->addItem(&pieces[25]);

    pieces[26].setPixmap(QPixmap("ImagesOfPieces/B_Knight.png").scaled(80, 80));
    pieces[26].setPos(-120, 360);
    pieces[26].setPieceName("B_Knight");
    this->addItem(&pieces[26]);

    pieces[27].setPixmap(QPixmap("ImagesOfPieces/B_Knight.png").scaled(80, 80));
    pieces[27].setPos(280, 360);
    pieces[27].setPieceName("B_Knight");
    this->addItem(&pieces[27]);

    pieces[28].setPixmap(QPixmap("ImagesOfPieces/B_Bishop.png").scaled(80, 80));
    pieces[28].setPos(-40, 360);
    pieces[28].setPieceName("B_Bishop");
    this->addItem(&pieces[28]);

    pieces[29].setPixmap(QPixmap("ImagesOfPieces/B_Bishop.png").scaled(80, 80));
    pieces[29].setPos(200, 360);
    pieces[29].setPieceName("B_Bishop");
    this->addItem(&pieces[29]);

    pieces[30].setPixmap(QPixmap("ImagesOfPieces/B_King.png").scaled(80, 80));
    pieces[30].setPos(40, 360);
    pieces[30].setPieceName("B_King");
    this->addItem(&pieces[30]);

    pieces[31].setPixmap(QPixmap("ImagesOfPieces/B_Queen.png").scaled(80, 80));
    pieces[31].setPos(120, 360);
    pieces[31].setPieceName("B_Queen");
    this->addItem(&pieces[31]);
}
