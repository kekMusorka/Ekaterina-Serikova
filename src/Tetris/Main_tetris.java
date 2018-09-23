package Tetris;

import Tetris.GraphicsModule;
import Tetris.LwjglGraphicsModule;
import Tetris.KeyboardHandleModule;
import Tetris.LwjglKeyboardHandleModule;

import java.lang.reflect.Field;

import static Tetris.Constants.BOOST_MULTIPLIER;
import static Tetris.Constants.FPS;
import static Tetris.Constants.FRAMES_PER_MOVE;

public class Main_tetris {
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
        //System.out.println("HI2");
        keyboardModule = new LwjglKeyboardHandleModule();
        //System.out.println("HI3");
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
