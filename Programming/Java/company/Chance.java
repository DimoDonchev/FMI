package com.company;

import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Chance extends Square {
    public Chance() {
        super("|C|");
    }

    @Override
    public void activate(Player player) {
        if (player.getStealPlan() == "World Conquer" && player.isPlanActivated()) {
            player.changeMoney(100);
        }

        boolean win;
        if (player.isTrapped("Gambling Boss") > 0) {
            win = false;
        } else {
            Dice dice = new Dice(10);
            int roll = dice.roll();
            if (roll % 2 == 0) {
                win = true;
            } else {
                win = false;
            }
        }

        String filename = null;
        if (win) {
            filename = "ChanceWin.txt";
        } else {
            filename = "ChanceLose.txt";
        }

        Dice dice100 = new Dice(100);
        int rollRes = dice100.roll();
        int pos;

        if (rollRes <= 39) {
            pos = 1;
        } else if (rollRes > 39 && rollRes <= 65) {
            pos = 2;
        } else if (rollRes > 65 && rollRes <= 79) {
            pos = 3;
        } else if (rollRes > 79 && rollRes <= 94) {
            pos = 4;
        } else {
            pos = 5;
        }
        Scanner scanner = null;
        String res = null;
        int money = 0;
        try {
            scanner = new Scanner(new FileReader(filename));
            for (int i = 0; i < pos; i++) {
                money = scanner.nextInt();
                res = scanner.nextLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            scanner.close();
        }

        System.out.println(res);
        player.changeMoney(money);

    }
}
