package com.company;

public class Computer extends ElectricDevice
{
	public Computer(int powerConsumption)
	{
		super(powerConsumption);
	}

	public void plugIn()
	{
		isPlugged = true;
		System.out.println("Computer is plugged in");
	}

	@Override
	public void plugOut()
	{
		isPlugged = false;
		System.out.println("Computer is plugged out");
	}

	@Override
	public void switchOn()
	{
		isSwitched = true;
		System.out.println("Computer is switched on");
	}

	@Override
	public void switchOff()
	{
		isSwitched = false;
		System.out.println("Computer is switched off");
	}
}
