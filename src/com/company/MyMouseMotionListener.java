package com.company;

import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import javax.swing.*;


import java.awt.*;

public class MyMouseMotionListener implements MouseMotionListener {
    @Override
    public void mouseDragged(MouseEvent e) {

    }

    @Override
    public void mouseMoved(MouseEvent e) {
        Main.plot.mouseX = e.getX();
        Main.plot.mouseY = e.getY();
    }

}
