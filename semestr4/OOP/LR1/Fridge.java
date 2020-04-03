package com.company;

public class Fridge extends ElectricDevice
{
    public Fridge(int powerConsumption)
    {
        super(powerConsumption);
    }

    @Override
    public void plugIn()
    {
        isPlugged = true;
        System.out.println("Fridge is plugged in");
    }

    @Override
    public void plugOut()
    {
        isPlugged = false;
        System.out.println("Fridge is plugged out");
    }

    @Override
    public void switchOn()
    {
        isSwitched = true;
        System.out.println("Fridge is switched on");
    }

    @Override
    public void switchOff()
    {
        isSwitched = false;
        System.out.println("Fridge is switched off");
    }
}
