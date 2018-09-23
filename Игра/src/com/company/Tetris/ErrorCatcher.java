package com.company.Tetris;

public class ErrorCatcher {

    public static void wrongParameter(String eparameter, String eclass) {
        System.err.println("Wrong parameter "+eparameter+" occured in class "+eclass);
        System.exit(-2);
    }

    public static void graphicsFailure(Exception e) {
        System.err.println("GraphicsModule failed.");
        e.printStackTrace();
        System.exit(-3);
    }

}
