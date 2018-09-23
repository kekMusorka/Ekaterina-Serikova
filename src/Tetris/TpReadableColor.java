package Tetris;

import java.util.Random;

public enum TpReadableColor {
    BLACK, RED, GREEN, BLUE, AQUA, YELLOW, ORANGE, PURPLE;
    private static TpReadableColor[] colorByNumber = { BLACK, RED, GREEN, BLUE, AQUA, YELLOW, ORANGE, PURPLE, };
    public static TpReadableColor getRandomColor() {
        int colorNumber = new Random().nextInt(colorByNumber.length);
        return colorByNumber[colorNumber];
    }
}
