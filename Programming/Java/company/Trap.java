package com.company;

import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Trap extends Square {

    private boolean isSet;
    private String trapName;
    private String playerName;


    public Trap() {
        super("|T|");
        isSet = false;
        trapName = null;
        playerName = null;
    }

    @Override
    public void activate(Player player) {
        if (isSet) { //if there is a set trap
            if (playerName == player.getName()) {
                Dice dice = new Dice(10);
                if (dice.roll() % 3 == 0) {
                    System.out.println("You managed to escape your own trap");
                    return;
                } else {
                    player.addTrap(trapName);
                }
            } else {
                player.addTrap(trapName);
            }
        }
        else { //if there is no set trap
            if (player.isTrapped("Propaganda") > 0) {
                System.out.println("You are trapped by propaganda and cannot set a trap");
                return;
            }
            Scanner reader = new Scanner(System.in);
            int cost = 0;
            Scanner scanner = null;
            try {
                scanner = new Scanner(new FileReader("Traps.txt"));
                System.out.println("Would You like to set a trap?");
                for (int i = 0; i < 5; i++) {
                    cost = scanner.nextInt();
                    trapName = scanner.nextLine();
                    System.out.println("(" + (i + 1) + ")" + " : " + trapName + ": " + cost);
                }
                System.out.println("(N) : No, Thank you");
                char choose = reader.next().charAt(0);
                if (choose >= '1' && choose <= '5') {
                    scanner.close();
                    scanner = new Scanner(new FileReader("Traps.txt"));
                    int pos = Character.getNumericValue(choose);
                    for (int i = 0; i < pos; i++) {
                        cost = scanner.nextInt();
                        trapName = scanner.nextLine();
                    }
                    isSet=true;
                    playerName=player.getName();
                    player.changeMoney(-cost);
                    System.out.println("Trap Laid. Remaining Money : " + player.getMoney() );
                }


            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                scanner.close();
            }
        }

    }
}
