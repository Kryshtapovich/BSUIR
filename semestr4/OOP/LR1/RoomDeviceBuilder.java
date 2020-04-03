package com.company;

public class RoomDeviceBuilder {
	private RoomDevices roomDevices;

	public RoomDeviceBuilder()
	{
		roomDevices = new RoomDevices();
	}

	public RoomDevices getRoomDevices()
	{
		return roomDevices;
	}

	public void setRoomDevice(ElectricDeviceType deviceType, int powerConsumption)
	{
		roomDevices.addDevice(ElectricDeviceFactory.getInstance(deviceType, powerConsumption));
	}
	public static void main(String[] args)
	{
		RoomDeviceBuilder builder = new RoomDeviceBuilder();
		builder.setRoomDevice(ElectricDeviceType.FRIDGE, 1200);
		builder.setRoomDevice(ElectricDeviceType.TV, 300);
		builder.setRoomDevice(ElectricDeviceType.COMPUTER, 540);

		RoomDevices roomDevices = builder.getRoomDevices();
		roomDevices.plugIn();
		System.out.println("Power consumption before switching on: " + roomDevices.getPowerConsumption());
		roomDevices.switchOn();
		System.out.println("Overall power consumption: " + roomDevices.getPowerConsumption());
		roomDevices.switchOff();
		roomDevices.plugOut();
	}
}
