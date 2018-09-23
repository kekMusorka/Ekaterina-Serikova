package com.company.Tetris;

import com.company.Tetris.ShiftDirection;

public interface KeyboardHandleModule {
    void update();
    boolean wasEscPressed();
    ShiftDirection getShiftDirection();
    boolean wasRotateRequested();
    boolean wasBoostRequested();
}
