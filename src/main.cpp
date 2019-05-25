#include "mainwindow.h"
#include "chesspiece.h"

#include "drawchessboard.h"
#include "pch.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create chesspieces on heap
    ChessPiece *pieces = new ChessPiece[32];

    // Create the scene
    QGraphicsScene scene;

    // Draw the chessboard squares and its pieces
    DrawChessBoard::drawChessBoard(scene, pieces);

    // Create the graphics view and set its properties
    QGraphicsView board;
    board.resize(700, 700);
    board.setRenderHint(QPainter::Antialiasing);
    board.setScene(&scene);

    // Show the board
    board.show();

    // Exec the QApplication
    a.exec();

    // Free the memory of the pieces
    delete[] pieces;

    return 0;
}

