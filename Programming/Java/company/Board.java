package com.company;

import java.util.ArrayList;
import java.util.Collections;

public class Board {
    private ArrayList<Square> squares;

    public Board() {
        squares = new ArrayList<Square>();

        for (int i = 0; i < 7; i++) {
            squares.add(new Trap());
        }
        for (int i = 0; i < 3; i++) {
            squares.add(new Invest());
            squares.add(new PartyHard());
            squares.add(new Chance());
            squares.add(new Steal());
        }
        squares.add(new Start());
        shuffle();
    }

    public void printBoard() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < 8; i++) {
            builder.append(squares.get(i).getType());
        }
        builder.append("\n" + squares.get(19).getType() + "                  " + squares.get(8).getType());
        builder.append("\n");
        builder.append(squares.get(18).getType() + "                  " + squares.get(9).getType() + "\n");
        for (int i = 17; i >= 10; i--) {
            builder.append(squares.get(i).getType());
        }
        System.out.println(builder.toString());
    }

    public String getSquareType(int pos) {
        return squares.get(pos).getType();
    }

    public void activateSquare(int pos, Player player) {
        squares.get(pos).activate(player);
    }

    /*
    shuffles all squares
    then finds the position of Start square and swaps it with position 0
     */
    public void shuffle() {
        Collections.shuffle(squares);
        int startPos = 0;
        for (int i = 0; i < squares.size(); i++) {
            if (getSquareType(i) == "|S|") {
                startPos = i;
                break;
            }
        }
        Collections.swap(squares, 0, startPos);
    }
}
