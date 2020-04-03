package com.company;

public class TV extends ElectricDevice
{
	public TV(int powerConsumption)
	{
		super(powerConsumption);
	}

	public void plugIn()
	{
		isPlugged = true;
		System.out.println("TV is plugged in");
	}

	@Override
	public void plugOut()
	{
		isPlugged = false;
		System.out.println("TV is plugged out");
	}

	@Override
	public void switchOn()
	{
		isSwitched = true;
		System.out.println("TV is switched on");
	}

	@Override
	public void switchOff()
	{
		isSwitched = false;
		System.out.println("TV is switched off");
	}
}
