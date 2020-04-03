package com.company;

public class State extends ComplexUnit
{
    public State(String name)
    {
        super(name);
    }

    public static void main(String[] args)
    {
        State state = new State("Belarus");

        Region minskRegion = new Region("Minsk region");
        Region brestRegion = new Region("Brest region");
        Region grodnoRegion = new Region("Grodno region");

        state.addSubunit(minskRegion);

        state.addSubunit(brestRegion);
        state.addSubunit(grodnoRegion);

        City minsk = new City(349, 2000000, "Minsk");
        City borisov = new City(46, 143287, "Borisov");
        City zaslavl = new City(14, 14400, "Zaslavl");

        City brest = new City(146, 343985, "Brest");
        City baranovichi = new City(85, 179439, "Baranovichi");

        City grodno = new City(142, 368710, "Grodno");
        City lida = new City(46, 101165, "Lida");

        minskRegion.addSubunit(minsk);
        minskRegion.addSubunit(borisov);
        minskRegion.addSubunit(zaslavl);

        brestRegion.addSubunit(brest);
        brestRegion.addSubunit(baranovichi);

        grodnoRegion.addSubunit(grodno);
        grodnoRegion.addSubunit(lida);

        System.out.println(state.showHierarchy());
        System.out.println("Population: " + state.getPopulation());
        System.out.println("Square: " + state.getSquare());
    }
}
