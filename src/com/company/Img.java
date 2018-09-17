package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;

public class Img {

    static Image s0bg;
    static Image s0cont;
    static Image s0start;
    static Image s0settings;
    static Image beg_bg;
    static Image beg_chn;

    public static void init() {
        int i = 1;
        try {
            s0bg = ImageIO.read(new File("scen0/background.jpg"));
            ++i;
            s0cont = ImageIO.read(new File("scen0/continue.jpg"));
            ++i;
            s0start = ImageIO.read(new File("scen0/startagain.jpg"));
            ++i;
            s0settings = ImageIO.read(new File("scen0/settings.jpg"));
            ++i;
            beg_bg = ImageIO.read(new File("begin/background.jpg"));
            ++i;
            beg_chn = ImageIO.read(new File("begin/choose_nick.png"));
            ++i;
        } catch (Exception e){
            System.err.println("проблема с загруской картинок " + i);
            System.err.println(e.getLocalizedMessage());
        }
    }
}
