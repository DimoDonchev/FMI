package com.company;

public class Steal extends Square {
    private boolean isOccupied;

    public Steal() {
        super("|L|");
        isOccupied = false;
    }

    @Override
    public void activate(Player player) {
        if(player.getStealPlan()=="Big Bank Heist" && player.isPlanActivated()){
            player.changeMoney(100);
        }
        if(player.isTrapped("Revision")>0){
            System.out.println("You are trapped by Revision and you cannot activate your evil plan");
            return;
        }
        if(!player.isPlanActivated()){
            if(!isOccupied){
                System.out.println("You activated your evil plan: " + player.getStealPlan());
                player.activatePlan();
                isOccupied = true;
            }
            else{
                System.out.println(player.getName() + " This Steal is already activated");
            }
        }  else {
            System.out.println("You have already activated your evil plan");
        }

        /*
        check if player has Stolen Big Bank Heist (+100 money)
        check if player is trapped by Revision (he cant steal)
        check if Square is not occupied
            {Initialise Steal Plan}
        otherwise do tc tc tc
         */
    }
}
