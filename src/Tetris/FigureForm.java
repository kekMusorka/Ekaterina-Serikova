package Tetris;

import Tetris.TpReadableColor;

import java.util.Random;

public enum FigureForm {

    I_FORM (CoordMask.I_FORM, TpReadableColor.BLUE),
    J_FORM (CoordMask.J_FORM, TpReadableColor.ORANGE),
    L_FORM (CoordMask.L_FORM, TpReadableColor.YELLOW),
    O_FORM (CoordMask.O_FORM, TpReadableColor.RED),
    S_FORM (CoordMask.S_FORM, TpReadableColor.AQUA),
    Z_FORM (CoordMask.Z_FORM, TpReadableColor.PURPLE),
    T_FORM (CoordMask.T_FORM, TpReadableColor.GREEN);

    private CoordMask mask;

    private TpReadableColor color;

    FigureForm(CoordMask mask, TpReadableColor color){
        this.mask = mask;
        this.color = color;
    }

    private static final FigureForm[] formByNumber = {I_FORM, J_FORM, L_FORM, O_FORM, S_FORM, Z_FORM, T_FORM,};

    public CoordMask getMask(){
        return this.mask;
    }

    public TpReadableColor getColor(){
        return this.color;
    }

    public static FigureForm getRandomForm() {
        int formNumber = new Random().nextInt(formByNumber.length);
        return formByNumber[formNumber];
    }

}