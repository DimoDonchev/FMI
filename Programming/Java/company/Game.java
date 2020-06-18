package com.company;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Game {
    private Board board;
    private ArrayList<Player> players;
    private Dice dice;

    public Game(int playersCount) {
        board = new Board();
        players = new ArrayList<Player>(playersCount);
        Scanner reader = new Scanner(System.in);
        String name;
        for (int i = 0; i < playersCount; i++) {
            System.out.println("Player:" + (i+1));
            name = reader.next();
            players.add(new Player(name));
        }
        dice = new Dice(2);
    }

    public void start() {
        Collections.shuffle(players);
        boolean gameOver = false;
        boolean endOfCycle = false;
        board.printBoard();

        while (!gameOver) {

            if (endOfCycle) {//if all players have looped around the board
                processEndOfCycle();
            }

            endOfCycle = true;

            for (int i = 0; i < players.size(); i++) {
                if (!players.get(i).atStart()) {//move every player that hasnt made a full cycle
                    System.out.println(players.get(i).getName() + " has a Turn");
                    endOfCycle = false; //if at least 1 player is not at the end then we cannot end the cycle
                    int diceRes = dice.roll(); //roll the dice 1,2
                    players.get(i).movePlayer(diceRes); //move the player 1,2
                    System.out.println(players.get(i).getName() + " moves " + diceRes + " ahead and steps on " +
                            board.getSquareType(players.get(i).getPlayerPos()));

                    //if we jump over the Start Square we simply return to it
                    if (players.get(i).getPlayerPos() > 19) {
                        players.get(i).setPlayerPos(0);
                        players.get(i).setAtStart(true);
                    }

                    //activate square and check if player went broke
                    board.activateSquare(players.get(i).getPlayerPos(), players.get(i));
                    if (players.get(i).getMoney() < 0) {
                        //this can make the game easier to implement for more players
                        System.out.println(players.get(i).getName() + " Went Broke");
                        players.remove(i);
                        if (players.size() == 1) {
                            System.out.println(players.get(0).getName() + " Won the Game! Congatulations!");
                            gameOver = true;
                            break;
                        }

                    }
                }
            }

        }
    }

    private void processEndOfCycle() {
        System.out.println("END OF CYCLE");
        for (int i = 0; i < players.size(); i++) {
            players.get(i).InvestmentReport(); //process all investments for each player
            players.get(i).chooseEvilPlan(); //choose new evil plan
            players.get(i).setAtStart(false); //set that player can start new cycle
        }
        board.shuffle(); //shuffle positions
        board.printBoard();
        Collections.sort(players); // sort players by amount of money
        System.out.println("New Player Order is:");
        for (int i = 0; i < players.size(); i++) {
            System.out.println((i + 1) + " : " + players.get(i).getName() + " " + players.get(i).getMoney());
        }
    }

}
