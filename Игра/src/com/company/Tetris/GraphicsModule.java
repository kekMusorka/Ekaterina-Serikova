package com.company.Tetris;

import com.company.Tetris.GameField;

public interface GraphicsModule {
    void draw(GameField field);
    boolean isCloseRequested();
    void destroy();
    void sync(int fps);
}
