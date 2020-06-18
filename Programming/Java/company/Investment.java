package com.company;

public class Investment {
    private String name;
    private int investment;
    private double returnRate;
    private int riskMin;
    private int riskMax;

    public Investment(String name, int investment, double returnRate, int riskMin, int riskMax) {
        this.name = name;
        this.investment = investment;
        this.returnRate = returnRate;
        this.riskMin = riskMin;
        this.riskMax = riskMax;
    }

    public int InvestmentResult(){
        int result = riskMin + (int)(Math.random() * ((riskMax - riskMin) + 1));
        if(result >= 0){
            result = 1;
        } else result = -1;

        return (int)(investment*returnRate*result);
    }
}
