package com.company;

import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Invest extends Square {
    public Invest() {
        super("|I|");
    }

    @Override
    public void activate(Player player) {
        if(player.isPlanActivated() && player.getStealPlan()=="Hostages"){
            player.changeMoney(100);
        }
        Scanner scanner = null;
        Scanner reader = new Scanner(System.in);
        String name = null;
        int investment=0;
        double returnRate=0;
        int riskMin=0;
        int riskMax=0;
        try{
            scanner = new Scanner(new FileReader("Investments.txt"));
            for(int i=0;i<6;i++){
                investment=scanner.nextInt();
                returnRate=scanner.nextDouble();
                riskMin=scanner.nextInt();
                riskMax=scanner.nextInt();
                name=scanner.nextLine();
                System.out.println("("+ (i+1) + ") : " + name + " | min : " + investment + " | risk/reward : " + returnRate);
            }
            System.out.println("(N) : No, I don't want to invest");
            char choose = reader.next().charAt(0);
            if (choose >= '1' && choose <= '6') {
                scanner.close();
                scanner = new Scanner(new FileReader("Investments.txt"));
                int pos = Character.getNumericValue(choose);
                for (int i = 0; i < pos; i++) {
                    investment=scanner.nextInt();
                    returnRate=scanner.nextDouble();
                    riskMin=scanner.nextInt();
                    riskMax=scanner.nextInt();
                    name=scanner.nextLine();
                }
                System.out.println("how much do you want to invest");
                int money = reader.nextInt();
                if(money<investment){
                    System.out.println("Your investment is not high enough");
                }
                else{
                    System.out.println("Successfully invested");
                    player.addInvestment(new Investment(name,money,returnRate,riskMin,riskMax));
                    player.changeMoney(money);
                }

            }

        } catch(IOException e){
            e.printStackTrace();
        } finally {
            scanner.close();
        }
    }
}
