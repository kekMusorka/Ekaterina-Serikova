package com.company.Tetris;

import org.lwjgl.input.Keyboard;
import com.company.Tetris.KeyboardHandleModule;
import com.company.Tetris.ShiftDirection;

public class LwjglKeyboardHandleModule implements KeyboardHandleModule {
    private boolean wasEscPressed;
    private boolean wasRotateRequested;
    private ShiftDirection shiftDirection;
    public void update() {
        resetValues();
        while (Keyboard.next()) {
            if (Keyboard.getEventKeyState()) {
                switch(Keyboard.getEventKey()){
                    case Keyboard.KEY_ESCAPE:
                        wasEscPressed = true;
                        break;
                    case Keyboard.KEY_UP:
                        wasRotateRequested = true;
                        break;
                    case Keyboard.KEY_LEFT:
                        shiftDirection = ShiftDirection.LEFT;
                        break;
                    case Keyboard.KEY_RIGHT:
                        shiftDirection = ShiftDirection.RIGHT;
                        break;
                }
            }
        }
    }
    private void resetValues() {
        wasEscPressed = false;
        wasRotateRequested = false;
        shiftDirection = ShiftDirection.AWAITING;
    }
    public boolean wasEscPressed() {
        return wasEscPressed;
    }
    public ShiftDirection getShiftDirection() {
        return shiftDirection;
    }
    public boolean wasRotateRequested() {
        return wasRotateRequested;
    }
    public boolean wasBoostRequested() {
        return Keyboard.isKeyDown(Keyboard.KEY_DOWN);
    }
}
