package com.company;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class MyMouseListener implements MouseListener {
    public void mouseClicked(MouseEvent e) {

    }
    public void mousePressed(MouseEvent e) {

    }
    public void mouseReleased(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1) {
            Main.plot.click();
        }
    }
    public void mouseEntered(MouseEvent e) {

    }
    public void mouseExited(MouseEvent e) {

    }
}
