package com.company;

import java.util.ArrayList;


public class Player implements Comparable<Player> {
    private String Name;
    private int money;
    private ArrayList<Investment> investments;
    private ArrayList<String> traps;
    private String stealPlan;
    private boolean isPlanActivated;
    private boolean atStart;
    private int playerPos;

    public Player(String name) {
        Name = name;
        money = 1000;
        investments = new ArrayList<Investment>();
        traps = new ArrayList<String>();
        chooseEvilPlan();
        isPlanActivated = false;
        atStart = false;
        playerPos = 0;
    }

    public String getStealPlan() {
        return stealPlan;
    }

    public boolean isPlanActivated() {
        return isPlanActivated;
    }

    public void activatePlan(){
        isPlanActivated = true;
    }

    public String getName() {
        return Name;
    }

    public int getMoney() {
        return money;
    }

    public int getPlayerPos() {
        return playerPos;
    }

    public void setPlayerPos(int newPos) {
        playerPos = newPos;
    }

    public void movePlayer(int move) {
        this.playerPos += move;
    }

    public boolean atStart() {
        return atStart;
    }

    public void setAtStart(boolean state) {
        atStart = state;
    }

    public void changeMoney(int sum) {
        money += sum;
    }

    public void addInvestment(Investment investment) {
        investments.add(investment);
    }

    //add trap interference
    public void InvestmentReport() {
        for (int i = 0; i < investments.size(); i++) {
            int investmentResult = investments.get(i).InvestmentResult();
            changeMoney(investmentResult);
        }
        investments.clear();
    }

    public void addTrap(String trapName) {
        traps.add(trapName);
    }

    public void chooseEvilPlan() {
        int planType = 1 + (int) (Math.random() * 2);
        switch (planType) {
            case 1:
                stealPlan = "World Domination";
                break;
            case 2:
                stealPlan = "Hostages";
                break;
            case 3:
                stealPlan = "Great Bank Heist";
                break;
        }
    }

    public int isTrapped(String trapName){
        int trapcount=0;
        for(int i = 0;i<traps.size();i++){
            if(traps.get(i)==trapName){
                trapcount++;
            }
        }

        return trapcount;
    }
    @Override
    public int compareTo(Player o) {
        if (money > o.getMoney()) {
            return 1;
        } else if (money == o.getMoney()) {
            return 0;
        } else return -1;

    }
}
