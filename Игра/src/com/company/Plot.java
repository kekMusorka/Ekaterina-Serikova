package com.company;

import java.awt.*;
import com.company.Tetris.*;

public class Plot {

    public int scen;

    public int mouseX;
    public int mouseY;

    public int[] list = {0, 1, 2, 3, 4, 5, 6, 7};

    public Plot(){
        scen = 5;
    }

    public Plot(int scen){
        for (int i: list) {
            if(i == scen){
                this.scen = scen;
                return;
            }
        }

        this.scen = 5;
    }

    public void setScen(int scen){
        for (int i: list) {
            if(i == scen){
                this.scen = scen;
                return;
            }
        }

        this.scen = 5;
    }


    public void draw(Graphics2D g2){
        //System.out.println(scen);
        switch (scen){
            case 0:
                menu(g2);
                break;
            case 1:
                game(g2);
                break;
            case 2:
                begin(g2);
                Main.text.setVisible(true);
                break;
            case 4:
                sapper(g2);
                break;
            case 5:
                Main.text.setVisible(false);
                choice(g2);
        }
    }

    //scen = 0
    public void menu(Graphics2D g2) {
        g2.drawImage(Img.s0bg, 0, 0, (int) (Img.s0bg.getWidth(null)/1.4), (int) (Img.s0bg.getHeight(null)/1.4), null);
        g2.drawImage(Img.s0cont, 155, 125, Img.s0cont.getWidth(null) / 2, Img.s0cont.getHeight(null) / 2, null);
        g2.drawImage(Img.s0start, 155, 285, Img.s0start.getWidth(null) / 2, Img.s0start.getHeight(null) / 2, null);
        g2.drawImage(Img.s0settings, 155, 450, Img.s0settings.getWidth(null) / 2, Img.s0settings.getHeight(null) / 2, null);
    }

    //scen = 1
    public void game(Graphics2D g2) {

    }

    public void choice(Graphics2D g2) {
        g2.drawImage(Img.choice_bg, 0, 0, (int) (Img.choice_bg.getWidth(null) / 2.5), (int) (Img.choice_bg.getHeight(null) / 2.5), null);
        g2.drawImage(Img.ch_pet, 370, 50, (int)(Img.ch_pet.getWidth(null)), (int)(Img.ch_pet.getHeight(null)), null);
        g2.drawImage(Img.pt_cat, 210, 200, (int)(Img.pt_cat.getWidth(null)), (int)(Img.pt_cat.getHeight(null)), null);
        g2.drawImage(Img.pt_dog, 200, 340, (int)(Img.pt_dog.getWidth(null)), (int)(Img.pt_dog.getHeight(null)), null);
        g2.drawImage(Img.pt_pig, 190, 480, (int)(Img.pt_pig.getWidth(null)), (int)(Img.pt_pig.getHeight(null)), null);
        //System.out.println(mouseX + " " + mouseY);
        if (mouseX >= 210 && mouseY >= 200 && mouseX <= 300 && mouseY <= 250) {
            g2.drawImage(Img.ch_cat, 460, 180, (int)(Img.ch_cat.getWidth(null) / 2), (int)(Img.ch_cat.getHeight(null) / 2), null);
        }
        if (mouseX >= 200 && mouseY >= 340 && mouseX <= 320 && mouseY <= 390) {
            g2.drawImage(Img.ch_dog, 490, 150, (int)(Img.ch_dog.getWidth(null) / 2), (int)(Img.ch_dog.getHeight(null) / 2), null);
        }
        if (mouseX >= 190 && mouseY >= 480 && mouseX <= 350 && mouseY <= 530) {
            g2.drawImage(Img.ch_pig, 490, 150, (int)(Img.ch_pig.getWidth(null) / 2), (int)(Img.ch_pig.getHeight(null) / 2), null);
        }
        //g2.drawOval(350,530,20,20);
    }

    public void sapper(Graphics2D g2) {
        String[] args = {"me", "lol"};
        Main_sapper.main(args);
        scen = 1;
    }

    //scen = 2
    public void begin(Graphics2D g2) {
        g2.drawImage(Img.beg_bg, 0, 0, (int) (Img.beg_bg.getWidth(null) / 1.065), (int) (Img.beg_bg.getHeight(null) / 1.16), null);
        g2.drawImage(Img.beg_chn, 410, 300, (int) (Img.beg_chn.getWidth(null)), (int) (Img.beg_chn.getHeight(null)), null);
        Main.text.setBounds(450, 380, 300, 80);
    }

    public void click() {
        //System.out.println(mouseX + " " + mouseY);
        switch(scen) {
            case 0:
                if (mouseX >= 155 && mouseY >= 125 && mouseX <= 470 && mouseY <= 210) {
                    setScen(1);
                }
                if (mouseX >= 155 && mouseY >= 285 && mouseX <= 470 && mouseY <= 370) {
                    setScen(2);
                }
                if (mouseX >= 155 && mouseY >= 450 && mouseX <= 470 && mouseY <= 535) {
                    setScen(3);
                }
        }
    }
    public void Enter() {
        //System.out.println("    " + scen);
        switch(scen) {
            case 2:
                setScen(5);
                break;
        }
    }
}
