package com.company;

import java.awt.*;

public class Plot {

    public int scen;

    public int mouseX;
    public int mouseY;

    public int[] list = {0, 1, 2, 3, 4};

    public Plot(){
        scen = 0;
    }

    public Plot(int scen){
        for (int i: list) {
            if(i == scen){
                this.scen = scen;
                return;
            }
        }

        this.scen = 0;
    }

    public void setScen(int scen){
        for (int i: list) {
            if(i == scen){
                this.scen = scen;
                return;
            }
        }

        this.scen = 0;
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
                Main.text.setVisible(false);
                chose(g2);
        }
    }

    //scen = 0
    public void menu(Graphics2D g2) {
        g2.drawImage(Img.s0bg, 0, 0, (int) (Img.s0bg.getWidth(null)/1.4), (int) (Img.s0bg.getHeight(null)/1.4), null);
        g2.drawImage(Img.s0cont, 155, 125, Img.s0cont.getWidth(null) / 2, Img.s0cont.getHeight(null) / 2, null);
        g2.drawImage(Img.s0start, 155, 285, Img.s0start.getWidth(null) / 2, Img.s0start.getHeight(null) / 2, null);
        g2.drawImage(Img.s0settings, 155, 450, Img.s0settings.getWidth(null) / 2, Img.s0settings.getHeight(null) / 2, null);
        //g2.drawOval(470, 535, 10, 10);
    }

    //scen = 1
    public void game(Graphics2D g2) {

    }

    public void chose(Graphics2D g2) {

    }

    //scen = 2
    public void begin(Graphics2D g2) {
        g2.drawImage(Img.beg_bg, 0, 0, (int) (Img.beg_bg.getWidth(null) / 1.065), (int) (Img.beg_bg.getHeight(null) / 1.16), null);
        g2.drawImage(Img.beg_chn, 410, 300, (int) (Img.beg_chn.getWidth(null)), (int) (Img.beg_chn.getHeight(null)), null);
        Main.text.setBounds(450, 380, 300, 80);
    }

    public void click() {
        System.out.println(mouseX + " " + mouseY);
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
                setScen(4);
                break;
        }
    }
}
