#include "drawchessboard.h"
#include "chesspiece.h"

DrawChessBoard::DrawChessBoard()
{
    // Do nothing.
}

bool DrawChessBoard::checkIfNeedsNewLine(const int& index)
{
    // Check if there needs to be a new line via the index, return true if so.
    if (index == 8 || index == 16 || index == 24 || index == 32 || index == 40 || index == 48 || index == 56 || index == 64) {
        return true;
    }
    return false;
}

void DrawChessBoard::drawRects(QGraphicsScene& scene)
{
    QGraphicsRectItem *rectItem = nullptr;

    // Declare variables
    int previousX = 0;
    int previousY = 0;
    QBrush previousBrush;
    QRect chessSquaresArray[64];

    for (int index = 0; index < 64; index++) {
        // Set dimensions of the board's squares.
        chessSquaresArray[index].setWidth(80);
        chessSquaresArray[index].setHeight(80);

        if (index == 0) {
            // Add first square to scene and set its attributes.
            rectItem = scene.addRect(chessSquaresArray[index]);
            rectItem->setPos(-200, -200);
            rectItem->setBrush(QBrush(Qt::white));
            previousX = static_cast<int>(rectItem->x());
            previousY = static_cast<int>(rectItem->y());
            previousBrush = rectItem->brush();
            continue;
        }

        if (checkIfNeedsNewLine(index)) {
            // If the current square needs to be on a new line, put it back at the far left of the board, and positioned
            // down by one square's length.
            rectItem = scene.addRect(chessSquaresArray[index]);
            rectItem->setPos(-200, previousY + 80);

            if (previousBrush == QBrush(Qt::white)) {
                rectItem->setBrush(QBrush(Qt::white));
            } else {
                rectItem->setBrush(QBrush(Qt::gray));
            }
            previousX = static_cast<int>(rectItem->x());
            previousY = static_cast<int>(rectItem->y());
            previousBrush = rectItem->brush();
            continue;
        }

        // Add rect to scene, set its pos and brush, and set the previous item to it (only execute if the above two "if's" aren't met).
        rectItem = scene.addRect(chessSquaresArray[index]);
        rectItem->setPos(previousX + 80, previousY);

        if (previousBrush == QBrush(Qt::white)) {
            rectItem->setBrush(QBrush(Qt::gray));
        } else {
            rectItem->setBrush(QBrush(Qt::white));
        }
        previousX = static_cast<int>(rectItem->x());
        previousY = static_cast<int>(rectItem->y());
        previousBrush = rectItem->brush();
    }
}



void DrawChessBoard::drawChessBoard(QGraphicsScene& scene, ChessPiece pieces[])
{
    // Draw the rects for the chessboard
    drawRects(scene);
    int previousX = 0, previousY = 0;

    // Set the scene for each of the chesspieces
    for (int index = 0; index < 32; index++) {
        pieces[index].setPieceScene(&scene);
    }

    for (int i = 0; i < 8; i++) {
	// Set the name and pixmap for each white pawn
        pieces[i].setPieceName("Pawn");
        pieces[i].setPixmap(QPixmap("ImagesOfPieces/Pawn.png").scaled(80, 80));

	// Handle the first white pawn
        if (i == 0) {
            pieces[i].setPos(-200, -120);
            previousX = static_cast<int>(pieces[i].x());
            previousY = static_cast<int>(pieces[i].y());
            scene.addItem(&pieces[i]);
            continue;
        }

	// Handle the other white pawns
        pieces[i].setPos(previousX + 80, previousY);
        previousX = static_cast<int>(pieces[i].x());
        previousY = static_cast<int>(pieces[i].y());
        scene.addItem(&pieces[i]);
    }

    // Handle the other pieces \/ \/ \/

    pieces[8].setPixmap(QPixmap("ImagesOfPieces/Rook.png").scaled(80, 80));
    pieces[8].setPos(-200, -200);
    pieces[8].setPieceName("Rook");
    scene.addItem(&pieces[8]);

    pieces[9].setPixmap(QPixmap("ImagesOfPieces/Rook.png").scaled(80, 80));
    pieces[9].setPos(360, -200);
    pieces[9].setPieceName("Rook");
    scene.addItem(&pieces[9]);

    pieces[10].setPixmap(QPixmap("ImagesOfPieces/Knight.png").scaled(80, 80));
    pieces[10].setPos(-120, -200);
    pieces[10].setPieceName("Knight");
    scene.addItem(&pieces[10]);

    pieces[11].setPixmap(QPixmap("ImagesOfPieces/Knight.png").scaled(80, 80));
    pieces[11].setPos(280, -200);
    pieces[11].setPieceName("Knight");
    scene.addItem(&pieces[11]);

    pieces[12].setPixmap(QPixmap("ImagesOfPieces/Bishop.png").scaled(80, 80));
    pieces[12].setPos(-40, -200);
    pieces[12].setPieceName("Bishop");
    scene.addItem(&pieces[12]);

    pieces[13].setPixmap(QPixmap("ImagesOfPieces/Bishop.png").scaled(80, 80));
    pieces[13].setPos(200, -200);
    pieces[13].setPieceName("Bishop");
    scene.addItem(&pieces[13]);

    pieces[14].setPixmap(QPixmap("ImagesOfPieces/King.png").scaled(80, 80));
    pieces[14].setPos(40, -200);
    pieces[14].setPieceName("King");
    scene.addItem(&pieces[14]);

    pieces[15].setPixmap(QPixmap("ImagesOfPieces/Queen.png").scaled(80, 80));
    pieces[15].setPos(120, -200);
    pieces[15].setPieceName("Queen");
    scene.addItem(&pieces[15]);


    for (int i = 16; i < 24; i++) {
	// Set pixmap and names for the black pawns
        pieces[i].setPixmap(QPixmap("ImagesOfPieces/B_Pawn.png").scaled(80, 80));
        pieces[i].setPieceName("B_Pawn");

	// Handle first black pawn
        if (i == 16) {
            pieces[i].setPos(-200, 280);
            previousX = static_cast<int>(pieces[i].x());
            previousY = static_cast<int>(pieces[i].y());
            scene.addItem(&pieces[i]);
            continue;
        }

	// Handle other black pawns
        pieces[i].setPos(previousX + 80, previousY);
        previousX = static_cast<int>(pieces[i].x());
        previousY = static_cast<int>(pieces[i].y());
        scene.addItem(&pieces[i]);
    }

    pieces[24].setPixmap(QPixmap("ImagesOfPieces/B_Rook.png").scaled(80, 80));
    pieces[24].setPos(-200, 360);
    pieces[24].setPieceName("B_Rook");
    scene.addItem(&pieces[24]);

    pieces[25].setPixmap(QPixmap("ImagesOfPieces/B_Rook.png").scaled(80, 80));
    pieces[25].setPos(360, 360);
    pieces[25].setPieceName("B_Rook");
    scene.addItem(&pieces[25]);

    pieces[26].setPixmap(QPixmap("ImagesOfPieces/B_Knight.png").scaled(80, 80));
    pieces[26].setPos(-120, 360);
    pieces[26].setPieceName("B_Knight");
    scene.addItem(&pieces[26]);

    pieces[27].setPixmap(QPixmap("ImagesOfPieces/B_Knight.png").scaled(80, 80));
    pieces[27].setPos(280, 360);
    pieces[27].setPieceName("B_Knight");
    scene.addItem(&pieces[27]);

    pieces[28].setPixmap(QPixmap("ImagesOfPieces/B_Bishop.png").scaled(80, 80));
    pieces[28].setPos(-40, 360);
    pieces[28].setPieceName("B_Bishop");
    scene.addItem(&pieces[28]);

    pieces[29].setPixmap(QPixmap("ImagesOfPieces/B_Bishop.png").scaled(80, 80));
    pieces[29].setPos(200, 360);
    pieces[29].setPieceName("B_Bishop");
    scene.addItem(&pieces[29]);

    pieces[30].setPixmap(QPixmap("ImagesOfPieces/B_King.png").scaled(80, 80));
    pieces[30].setPos(40, 360);
    pieces[30].setPieceName("B_King");
    scene.addItem(&pieces[30]);

    pieces[31].setPixmap(QPixmap("ImagesOfPieces/B_Queen.png").scaled(80, 80));
    pieces[31].setPos(120, 360);
    pieces[31].setPieceName("B_Queen");
    scene.addItem(&pieces[31]);
}
