package com.company;

import java.util.ArrayList;

public abstract class ComplexUnit implements Unit
{
    private ArrayList<Unit> units = new ArrayList<>();

    private String name;

    public ComplexUnit(String name)
    {
        this.name = name;
    }

    public void addSubunit(Unit unit)
    {
        units.add(unit);
    }

    public void removeSubunit(Unit unit)
    {
        units.remove(unit);
    }

    @Override
    public String showHierarchy()
    {
        String res = getClass().getSimpleName() + ": " + getName() + "\n";
        for (Unit unit : units)
        {
            res += ("  " + unit.showHierarchy() + "\n");
        }
        return res;
    }

    @Override
    public int getSquare()
    {
        int square = 0;
        for (Unit unit : units)
        {
            square += unit.getSquare();
        }
        return square;
    }

    @Override
    public int getPopulation()
    {
        int population = 0;
        for (Unit unit : units)
        {
            population += unit.getPopulation();
        }
        return population;
    }

    @Override
    public String getName()
    {
        return name;
    }

    public void setName()
    {
        this.name = name;
    }
}
