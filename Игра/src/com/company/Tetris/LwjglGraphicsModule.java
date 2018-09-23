package com.company.Tetris;

import org.lwjgl.LWJGLException;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.util.Color;
import org.lwjgl.util.ReadableColor;

import static org.lwjgl.opengl.GL11.*;
import static com.company.Tetris.Constants.*;

public class LwjglGraphicsModule implements GraphicsModule {

    public LwjglGraphicsModule() {
        initOpengl();
    }

    private void initOpengl() {
        try {
            Display.setDisplayMode(new DisplayMode(Constants.SCREEN_WIDTH, Constants.SCREEN_HEIGHT));
            Display.setTitle("Tetris for my pet");
            Display.create();
        } catch (LWJGLException e) {
            ErrorCatcher.graphicsFailure(e);
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, Constants.SCREEN_WIDTH,0, Constants.SCREEN_HEIGHT,1,-1);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_TEXTURE_2D);
        glClearColor(1,1,1,1);
    }
    private void drawCell(int x, int y, Color color) {
        glColor3ub(color.getRedByte(), color.getGreenByte(), color.getBlueByte());
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(x,y + Constants.CELL_SIZE);
        glTexCoord2f(1,0);
        glVertex2f(x + Constants.CELL_SIZE,y+ Constants.CELL_SIZE);
        glTexCoord2f(1,1);
        glVertex2f(x + Constants.CELL_SIZE, y);
        glTexCoord2f(0,1);
        glVertex2f(x, y);
        glEnd();
    }
    public void draw(GameField field) {
        for(int x = 0; x < COUNT_CELLS_X; x++){
            for(int y = 0; y < COUNT_CELLS_Y; y++){
                TpReadableColor color = field.getColor(x,y);
                drawCell(x*CELL_SIZE, y*CELL_SIZE, convertColor(color));
            }
        }

        Figure figure = field.getFigure();
        TpReadableColor color = figure.getColor();
        for(Coord coord : figure.getCoords()){
            drawCell(coord.x * CELL_SIZE, coord.y * CELL_SIZE, convertColor(color));
        }

        Display.update();
    }
    private Color convertColor(TpReadableColor color) {
        switch (color){
            case RED:
                return new Color(ReadableColor.RED);
            case GREEN:
                return new Color(ReadableColor.GREEN);
            case BLUE:
                return new Color(ReadableColor.BLUE);
            case AQUA:
                return new Color(ReadableColor.CYAN);
            case YELLOW:
                return new Color(ReadableColor.YELLOW);
            case ORANGE:
                return new Color(ReadableColor.ORANGE);
            case PURPLE:
                return new Color(ReadableColor.PURPLE);
            case BLACK:
                return new Color(ReadableColor.BLACK);
            default:
                return new Color(ReadableColor.WHITE);
        }
    }
    public boolean isCloseRequested() {
        return Display.isCloseRequested();
    }
    public void destroy() {
        Display.destroy();
    }
    public void sync(int fps) {
        Display.sync(fps);
    }
}
