package com.company.Tetris;

import com.company.Tetris.GraphicsModule;
import com.company.Tetris.LwjglGraphicsModule;
import com.company.Tetris.KeyboardHandleModule;
import com.company.Tetris.LwjglKeyboardHandleModule;

import java.lang.reflect.Field;

import static com.company.Tetris.Constants.BOOST_MULTIPLIER;
import static com.company.Tetris.Constants.FPS;
import static com.company.Tetris.Constants.FRAMES_PER_MOVE;

public class Main_sapper {
    private static boolean endOfGame;
    private static GraphicsModule graphicsModule;
    private static KeyboardHandleModule keyboardModule;
    private static GameField gameField;
    private static ShiftDirection shiftDirection;
    private static boolean isRotateRequested;
    private static boolean isBoostRequested;
    private static int loopNumber;
    public static void main(String[] args) {
        initFields();

        while(!endOfGame){
            input();
            logic();

            graphicsModule.draw(gameField);
            graphicsModule.sync(FPS);
        }
        graphicsModule.destroy();
    }
    private static void initFields() {
        loopNumber = 0;
        endOfGame = false;
        shiftDirection = ShiftDirection.AWAITING;
        isRotateRequested = false;
        graphicsModule = new LwjglGraphicsModule();
        keyboardModule = new LwjglKeyboardHandleModule();
        gameField = new GameField();
    }

    private static void input(){
        keyboardModule.update();
        shiftDirection = keyboardModule.getShiftDirection();
        isRotateRequested = keyboardModule.wasRotateRequested();
        isBoostRequested = keyboardModule.wasBoostRequested();
        if (keyboardModule.wasEscPressed() || graphicsModule.isCloseRequested()) {
            endOfGame = true;
        }
    }
    private static void logic(){
        if(shiftDirection != ShiftDirection.AWAITING){
            gameField.tryShiftFigure(shiftDirection);
            shiftDirection = ShiftDirection.AWAITING;
        }
        if(isRotateRequested){
            gameField.tryRotateFigure();
            isRotateRequested = false;
        }
        int a = 1;
        if (isBoostRequested) {
            a = BOOST_MULTIPLIER;
        }
        if(loopNumber % (FRAMES_PER_MOVE / a) == 0) gameField.letFallDown();
        loopNumber = (loopNumber+1)% (FRAMES_PER_MOVE);
        endOfGame = endOfGame || gameField.isOverfilled();
    }

}
