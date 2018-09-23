package com.company;

import java.awt.*;

public class Pet {

    int hp;
    int maxhp = 1024;

    int satiety;
    int maxSatiety = 1024;

    int happy;
    int maxHappy = 1024;

    int energy;
    int maxEnergy = 1024;

    int purity;
    int maxPurity = 1024;

    String name;

    public Pet(String name) {
        this.name = name;
        hp = maxhp;
        satiety = maxSatiety;
        happy = maxHappy;
        energy = maxEnergy;
        purity = maxPurity;
    }

    public Pet(int hp, int satiety, int happy, int energy, int purity, String name) {
        this.hp = hp;
        this.satiety = satiety;
        this.happy = happy;
        this.energy = energy;
        this.purity = purity;
        this.name = name;
    }

    public void setHp(int hp) {
        if(hp > maxhp) {
            this.hp = maxhp;
            return;
        }

        if(hp < 0) {
            this.hp = 0;
            return;
        }

        this.hp = hp;
    }

    public void setSatiety(int satiety) {
        if(satiety > maxSatiety){
            this.satiety = maxSatiety;
            return;
        }

        if(satiety < 0){
            this.satiety = 0;
            return;
        }

        this.satiety = satiety;
    }

    public void setHappi(int happy) {
        if(happy > maxHappy){
            this.happy = maxHappy;
            return;
        }

        if(happy < 0){
            this.happy = 0;
            return;
        }

        this.happy = happy;
    }

    public void setEnergy(int energy) {
        if(energy > maxEnergy){
            this.energy = maxEnergy;
            return;
        }

        if(energy < 0){
            this.energy = 0;
            return;
        }

        this.energy = energy;
    }

    public void setPurity(int purity) {
        if(purity > maxPurity){
            this.purity = maxPurity;
            return;
        }

        if(purity < 0){
            this.purity = 0;
            return;
        }

        this.purity = purity;
    }

    public void addHp(int hp){
        setHp(this.hp + hp);
    }

    public void addSatiety(int satiety){
        setSatiety(this.satiety + satiety);
    }

    public void addHappi(int happi){
        setHappi(this.happy + happi);
    }

    public void addEnergy(int energy){
        setEnergy(this.energy + energy);
    }

    public void addPurity(int purity){
        setPurity(this.purity + purity);
    }

    static Pet open(String name){
        return null;
    }

    static void save(Pet pet) {

    }

    public void draw(Graphics g2) {

    }
}
