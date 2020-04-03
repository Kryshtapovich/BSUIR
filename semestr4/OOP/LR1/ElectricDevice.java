package com.company;

public abstract class ElectricDevice {
	private int powerConsumption;

	protected boolean isSwitched;

	protected boolean isPlugged;

	public ElectricDevice(int powerConsumption)
	{
		setPowerConsumption(powerConsumption);
		isPlugged = false;
		isSwitched = false;
	}

	public void setPowerConsumption(int powerConsumption)
	{
		this.powerConsumption = powerConsumption;
	}

	public int getPowerConsumption()
	{
		return powerConsumption;
	}

	public boolean isPlugged()
	{
		return isPlugged;
	}

	public boolean isSwitched()
	{
		return isSwitched;
	}

	public abstract void plugIn();

	public abstract void plugOut();

	public abstract void switchOn();

	public abstract void switchOff();
}