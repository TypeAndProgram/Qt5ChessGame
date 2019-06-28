#include "mainwindow.h"
#include "chesspiece.h"

#include "chessboard.h"
#include "pch.h"

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);

    // Create the scene
    QGraphicsScene scene;
    ChessBoard board(std::unique_ptr<QGraphicsScene>(new QGraphicsScene));
    board.resize(700, 700);
    board.setRenderHint(QPainter::HighQualityAntialiasing);
    board.setScene(&scene);
    board.draw();
    board.show();

    a.exec();

    return 0;
}

