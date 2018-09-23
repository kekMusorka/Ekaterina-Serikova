package com.company.Tetris;

import java.util.Random;
import static com.company.Tetris.Constants.*;
public class GameField {
    private TpReadableColor[][] theField;
    private int[] countFilledCellsInLine;
    private Figure figure;
    public GameField() {
        spawnNewFigure();
        theField = new TpReadableColor[COUNT_CELLS_X][COUNT_CELLS_Y+OFFSET_TOP];
        countFilledCellsInLine = new int[COUNT_CELLS_Y+OFFSET_TOP];
        Random rnd = new Random();
        for(int y = 0; y < BLOCKS_INITIAL_LEVEL; y++){
            int missingBlocksCount = 5;
            int[] missingBlocksXCoords = new int[missingBlocksCount];
            missingBlocksXCoords[0] = rnd.nextInt(COUNT_CELLS_X - 1);
            //System.out.println(missingBlocksXCoords[0]);
            for(int i = 1; i < missingBlocksCount; i++) {
                if (i == 0) {
                    continue;
                }
                missingBlocksXCoords[i] = missingBlocksXCoords[i - 1] + rnd.nextInt(3);
            }
            int q = 0;
            for(int x = 0; x < COUNT_CELLS_X; x++){
                if((q < missingBlocksCount) && (missingBlocksXCoords[q] == x)) {
                    theField[x][y] = EMPTINESS_COLOR;
                    q++;
                } else {
                    while(true) {
                        theField[x][y] = TpReadableColor.getRandomColor();
                        if (theField[x][y] != EMPTINESS_COLOR) {
                            break;
                        }
                    }
                    countFilledCellsInLine[y]++;
                }
            }
        }
        for (int x = 0; x < COUNT_CELLS_X; x++) {
            for (int y = BLOCKS_INITIAL_LEVEL; y < COUNT_CELLS_Y + OFFSET_TOP; y++) {
                theField[x][y] = EMPTINESS_COLOR;
            }
        }
    }

    private void spawnNewFigure() {
        int randomX = new Random().nextInt(COUNT_CELLS_X - MAX_FIGURE_WIDTH);
        this.figure = new Figure(new Coord(randomX, COUNT_CELLS_Y + OFFSET_TOP - 1));
    }
    public boolean isEmpty(int x, int y) {
        return (theField[x][y].equals(EMPTINESS_COLOR));
    }
    public TpReadableColor getColor(int x, int y) {
        return theField[x][y];
    }
    public Figure getFigure() {
        return figure;
    }
    public void tryShiftFigure(ShiftDirection shiftDirection) {
        Coord[] shiftedCoords = figure.getShiftedCoords(shiftDirection);
        boolean canShift = true;
        for(Coord coord: shiftedCoords) {
            if((coord.y<0 || coord.y>=COUNT_CELLS_Y+OFFSET_TOP)
                    ||(coord.x<0 || coord.x>=COUNT_CELLS_X)
                    || ! isEmpty(coord.x, coord.y)){
                canShift = false;
            }
        }
        if(canShift){
            figure.shift(shiftDirection);
        }
    }
    public void tryRotateFigure() {
        Coord[] rotatedCoords = figure.getRotatedCoords();
        boolean canRotate = true;
        for(Coord coord: rotatedCoords) {
            if((coord.y<0 || coord.y>=COUNT_CELLS_Y+OFFSET_TOP)
                    ||(coord.x<0 || coord.x>=COUNT_CELLS_X)
                    ||! isEmpty(coord.x, coord.y)){
                canRotate = false;
            }
        }

        if(canRotate){
            figure.rotate();
        }
    }
    public void letFallDown() {
        Coord[] fallenCoords = figure.getFallenCoords();
        boolean canFall = true;
        for(Coord coord: fallenCoords) {
            if((coord.y<0 || coord.y>=COUNT_CELLS_Y+OFFSET_TOP)
                    ||(coord.x<0 || coord.x>=COUNT_CELLS_X)
                    ||! isEmpty(coord.x, coord.y)){
                canFall = false;
            }
        }
        if(canFall) {
            figure.fall();
        } else {
            Coord[] figureCoords = figure.getCoords();
            boolean haveToShiftLinesDown = false;
            for(Coord coord: figureCoords) {
                theField[coord.x][coord.y] = figure.getColor();
                countFilledCellsInLine[coord.y]++;
                if (tryDestroyLine(coord.y)) {
                    haveToShiftLinesDown = true;
                }
            }
            if(haveToShiftLinesDown) shiftLinesDown();
            spawnNewFigure();
        }
    }
    private void shiftLinesDown() {
        int fallTo = -1;
        for(int y = 0; y < COUNT_CELLS_Y; y++){
            if(fallTo == -1) {
                if (countFilledCellsInLine[y] == 0) fallTo = y;
            } else {
                if(countFilledCellsInLine[y] != 0){

                    for(int x = 0; x < COUNT_CELLS_X; x++){
                        theField[x][fallTo] = theField[x][y];
                        theField[x][y] = EMPTINESS_COLOR;
                    }

                    countFilledCellsInLine[fallTo] = countFilledCellsInLine[y];
                    countFilledCellsInLine[y] = 0;
                    fallTo++;
                }
            }
        }
    }

    private boolean tryDestroyLine(int y) {
        if(countFilledCellsInLine[y] < COUNT_CELLS_X) {
            return false;
        }
        for(int x = 0; x < COUNT_CELLS_X; x++) {
            theField[x][y] = EMPTINESS_COLOR;
        }
        countFilledCellsInLine[y] = 0;
        return true;
    }

    public boolean isOverfilled() {
        boolean ret = false;
        for(int i = 0; i < OFFSET_TOP; i++) {
            if(countFilledCellsInLine[COUNT_CELLS_Y+i] != 0) ret = true;
        }
        return ret;
    }
}
