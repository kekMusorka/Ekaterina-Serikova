package com.company;
import javax.swing.*;
import java.awt.*;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Dimension;

public class Main {
    static JFrame myFram = new JFrame("My lovely pet");
    static Dimension sSize;
    static Plot plot;
    static JTextField text = new JTextField();
    public static void main(String[] args) {
        Img.init();
        plot = new Plot();
        framInit(plot);
    }
    static public void framInit(Plot plot) {
        sSize = Toolkit.getDefaultToolkit ().getScreenSize ();
        System.out.println("    " + sSize.height + "   " + sSize.width + "  HI");
        text.setBackground(new Color(0, 0, 0, 0));
        text.setCaretColor(Color.white);
        text.setForeground(Color.white);
        text.setFont(new Font("Dialog", 2, 50));
        text.setHorizontalAlignment(JTextField.CENTER);
        text.setBorder(BorderFactory.createLineBorder(Color.WHITE));
        text.setVisible(false);
        text.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    plot.Enter();
                }
            }
        });
        myFram.setBounds(sSize.width/12,sSize.height/12, sSize.width*5/6, sSize.height*5/6);
        myFram.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        myFram.setLayout(null);

        JPanel graf = new JPanel() {
            Graphics2D g2;
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                g2 = (Graphics2D) g;

                plot.draw(g2);

                repaint();
            }
        };

        graf.addMouseMotionListener(new MyMouseMotionListener());
        graf.addMouseListener(new MyMouseListener());
        graf.add(text);

        myFram.setContentPane(graf);
        myFram.setVisible(true);
    }
}

