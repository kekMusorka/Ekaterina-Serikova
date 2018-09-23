package com.company.Tetris;


public class Figure {
    private Coord metaPointCoords;
    private RotationMode currentRotation;
    private FigureForm form;

    public Figure(Coord metaPointCoords) {
        this(metaPointCoords, RotationMode.NORMAL, FigureForm.getRandomForm());
    }

    public Figure(Coord metaPointCoords, RotationMode rotation, FigureForm form){
        this.metaPointCoords = metaPointCoords;
        this.currentRotation = rotation;
        this.form = form;
    }

    public Coord[] getCoords(){
        return form.getMask().generateFigure(metaPointCoords, currentRotation);
    }

    public Coord[] getRotatedCoords(){
        return form.getMask().generateFigure(metaPointCoords, RotationMode.getNextRotationFrom(currentRotation));
    }

    public void rotate(){
        this.currentRotation = RotationMode.getNextRotationFrom(currentRotation);
    }

    public Coord[] getShiftedCoords(ShiftDirection direction){
        Coord newFirstCell = null;

        switch (direction){
            case LEFT:
                newFirstCell = new Coord(metaPointCoords.x - 1, metaPointCoords.y);
                break;
            case RIGHT:
                newFirstCell = new Coord(metaPointCoords.x + 1, metaPointCoords.y);
                break;
            default:
                ErrorCatcher.wrongParameter("direction (for getShiftedCoords)", "Figure");
        }

        return form.getMask().generateFigure(newFirstCell, currentRotation);
    }

    public void shift(ShiftDirection direction){
        switch (direction){
            case LEFT:
                metaPointCoords.x--;
                break;
            case RIGHT:
                metaPointCoords.x++;
                break;
            default:
                ErrorCatcher.wrongParameter("direction (for shift)", "Figure");
        }
    }

    public Coord[] getFallenCoords(){
        Coord newFirstCell = new Coord(metaPointCoords.x, metaPointCoords.y - 1);

        return form.getMask().generateFigure(newFirstCell, currentRotation);
    }

    public void fall(){
        metaPointCoords.y--;
    }

    public TpReadableColor getColor() {
        return form.getColor();
    }
}