package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;

public class ImgChoice {
    static Image background;
    public static void init() {
        int i = 1;
        try {
            background = ImageIO.read(new File("scen0/background.jpg"));
            ++i;
        } catch (Exception e){
            System.err.println("troubles with loading pictures in ImgChoice " + i);
            System.err.println(e.getLocalizedMessage());
        }
    }
}
