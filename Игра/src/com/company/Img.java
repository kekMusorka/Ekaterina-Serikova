package com.company;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;

public class Img {
    static Image s0bg;
    static Image s0cont;
    static Image s0start;
    static Image s0settings;
    static Image beg_bg;
    static Image beg_chn;
    static Image choice_bg, ch_pet;
    static Image pt_cat, pt_dog, pt_pig;
    static Image ch_cat, ch_dog, ch_pig;
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
            choice_bg = ImageIO.read(new File("choice/background.jpg"));
            ++i;
            ch_pet = ImageIO.read(new File("choice/choosePet.png"));
            ++i;
            pt_cat = ImageIO.read(new File("choice/prntCat.png"));
            ++i;
            pt_dog = ImageIO.read(new File("choice/prntDog.png"));
            ++i;
            pt_pig = ImageIO.read(new File("choice/prntPiggy.png"));
            ++i;
            ch_cat = ImageIO.read(new File("choice/cat.png"));
            ++i;
            ch_dog = ImageIO.read(new File("choice/dog.png"));
            ++i;
            ch_pig = ImageIO.read(new File("choice/piggy.png"));
            ++i;
        } catch (Exception e){
            System.err.println("troubles with loading pictures in Img " + i);
            System.err.println(e.getLocalizedMessage());
        }
    }
}
