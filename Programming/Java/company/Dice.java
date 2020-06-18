package com.company;

public class Dice {
    private int sides;

    public Dice(int sides) {
        this.sides = sides;
    }

    public int roll(){
        int roll = (int)((Math.random()*100)%sides + 1);
        return roll;
    }
}
