package com.company;

import javax.swing.*;
import java.util.ArrayList;

public class RoomDevices
{
    private ArrayList<ElectricDevice> devices;

    public RoomDevices()
    {
        devices = new ArrayList<>();
    }

    public void addDevice(ElectricDevice device)
    {
        devices.add(device);
    }

    public ArrayList<ElectricDevice> getRoomDevices()
    {
        return devices;
    }

    public int getPowerConsumption()
    {
        int power = 0;
        for (ElectricDevice device : devices)
        {
            if(device.isPlugged() && device.isSwitched())
            {
                power += device.getPowerConsumption();
            }
        }
        return power;
    }

    public void plugIn()
    {
        devices.forEach(x -> x.plugIn());
    }

    public void plugOut()
    {
        devices.forEach(x -> x.plugOut());
    }

    public void switchOn()
    {
        devices.forEach(x -> x.switchOn());
    }

    public void switchOff()
    {
        devices.forEach(x -> x.switchOff());
    }
}
