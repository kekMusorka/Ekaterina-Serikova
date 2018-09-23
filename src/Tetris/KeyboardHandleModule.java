package Tetris;

import Tetris.ShiftDirection;

public interface KeyboardHandleModule {
    void update();
    boolean wasEscPressed();
    ShiftDirection getShiftDirection();
    boolean wasRotateRequested();
    boolean wasBoostRequested();
}
