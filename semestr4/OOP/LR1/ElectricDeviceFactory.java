package com.company;

public class ElectricDeviceFactory
{
	public static ElectricDevice getInstance(ElectricDeviceType deviceType, int powerConsumption)
	{
		switch (deviceType)
		{
			case TV:
				return new TV(powerConsumption);

			case FRIDGE:
				return new Fridge(powerConsumption);

			case COMPUTER:
				return new Computer(powerConsumption);

			default:
				return null;
		}
	}
}
