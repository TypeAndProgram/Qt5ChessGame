#include "mainwindow.h"
#include "../include/ChessGame/chesspiece.h"

#include "../include/ChessGame/chessboard.h"
#include "../include/ChessGame/pch.h"

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);

    // Create the scene
    std::shared_ptr<QGraphicsScene> scene = std::make_shared<QGraphicsScene>();
    ChessBoard board(scene);
    board.resize(700, 700);
    board.setRenderHint(QPainter::HighQualityAntialiasing);
    board.setScene(scene.get());
    board.draw();
    board.show();

    a.exec();

    return 0;
}

