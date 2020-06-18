package com.company;

public abstract class Square {
    private String Type;

    public  Square(String type) {
        Type = type;
    }

    public String getType() {
        return Type;
    }

    public abstract void activate(Player player);

}
