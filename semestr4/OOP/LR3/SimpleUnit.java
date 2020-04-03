package com.company;

public abstract class SimpleUnit implements Unit
{
    private int square;

    private int population;

    private String name;

    public SimpleUnit(int square, int population, String name)
    {
        this.square = square;
        this.population = population;
        this.name = name;
    }

    public void setSquare(int square)
    {
        this.square = square;
    }

    public void setPopulation(int population)
    {
        this.population = population;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    @Override
    public int getSquare()
    {
        return square;
    }

    @Override
    public int getPopulation()
    {
        return population;
    }

    @Override
    public String getName()
    {
        return name;
    }

    @Override
    public String showHierarchy()
    {
        return "  " + getClass().getSimpleName() + ": " + getName();
    }
}
