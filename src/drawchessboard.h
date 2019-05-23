#ifndef DRAWCHESSBOARD_H
#define DRAWCHESSBOARD_H

#include "mainwindow.h"
#include "chesspiece.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QSize>
#include <QList>

class DrawChessBoard
{
public:
    DrawChessBoard();
    static void drawChessBoard(QGraphicsScene& scene, ChessPiece pieces[]);
private:
    static bool checkIfNeedsNewLine(const int& index);
    static void drawRects(QGraphicsScene& scene);
    static void drawPieces(const QGraphicsScene& scene);
};

#endif // DRAWCHESSBOARD_H
