package com.company;

public class PartyHard extends Square{
    public PartyHard() {
        super("|P|");
    }

    @Override
    public void activate(Player player) {
        System.out.println(player.getName() + " goes partying and loses 25 money");
        player.changeMoney(-25);
    }
}
