package com.company;

public class Start extends Square{

    public Start() {
        super("|S|");
    }
    @Override
    public void activate(Player player) {
        System.out.println(player.getName() + " reaches the Start square");
        player.setAtStart(true);
    }
}
