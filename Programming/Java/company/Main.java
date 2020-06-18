package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        System.out.println("Choose number of players");
        int playerCount = reader.nextInt();
        Game game = new Game(playerCount);
        game.start();
    }
}
