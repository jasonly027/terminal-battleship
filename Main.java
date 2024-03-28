package org.example;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        Map playerMap = new Map();
        Map opponentMap = new Map();
        Map playerAttackMap = new Map();
        Map opponentAttackMap = new Map();

        Ships carrier = new Ships(5);
        Ships battleship = new Ships(4);
        Ships cruiser = new Ships(3);
        Ships submarine = new Ships(3);
        Ships destroyer = new Ships(2);

        ArrayList<Ships> playerFleet = new ArrayList<>();
        playerFleet.add(carrier);
        playerFleet.add(battleship);
        playerFleet.add(cruiser);
        playerFleet.add(submarine);
        playerFleet.add(destroyer);

        System.out.println("Battle ship has a 10 x 10 board size.");
        System.out.println("Ship maps");
        System.out.println("0 means no ship");
        System.out.println("1 means ship is there and not hit");
        System.out.println("2 means ship is there and hit");

        System.out.println();

        System.out.println("Attack maps");
        System.out.println("0 means nothing has been done at this square");
        System.out.println("1 means the location was shot but no ship was on that square");
        System.out.println("2 means the location was shot and there is a square");
        playerMap.printMap();
        System.out.println("\n");

        placeShipInput(carrier, playerMap, scnr);
        placeShipInput(battleship, playerMap, scnr);
        placeShipInput(cruiser, playerMap, scnr);
        placeShipInput(submarine, playerMap, scnr);
        placeShipInput(destroyer, playerMap, scnr);



    }
    public static int getXPlacementInput(Ships ship, Scanner scnr){
        int xPlacement;
        System.out.println("Where would you like to place your carrier? ("+ship.getHp()+ "spaces)");
        System.out.print("x position: ");
        while(true){
            if(scnr.hasNextInt()){
                xPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to place your carrier? ("+ship.getHp()+ "spaces)");
                System.out.print("x position: ");
                scnr.nextLine();
            }
        }
        //clear scanner
        scnr.nextLine();
        return xPlacement;
    }
    public static int getYPlacementInput(Ships ship, Scanner scnr){
        int yPlacement;
        System.out.println("Where would you like to place your carrier? ("+ship.getHp()+ " spaces)");
        System.out.print("y position: ");
        while(true){
            if(scnr.hasNextInt()){
                yPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to place your carrier? ("+ship.getHp()+ " spaces)");
                System.out.print("y position: ");
                scnr.nextLine();
            }
        }
        //clear scanner
        scnr.nextLine();
        return yPlacement;
    }
    public static boolean getPlacementDirection(Scanner scnr){
        while(true){
            System.out.println("Do you want to place it horizontally to the right or vertically down? (h or v) ");
            String temp = scnr.nextLine();

            if(temp.equalsIgnoreCase("h")){
                return true;
            }
            else if(temp.equalsIgnoreCase("v")){
                return false;
            }
            else {
                System.out.println("Invalid direction argument, defaulting to horizontal");
                scnr.nextLine();
            }
        }
    }

    public static void placeShipInput(Ships ship,Map map, Scanner scnr){
        //ask for user ship placement
        while (true) {
            int xPlacement = getXPlacementInput(ship, scnr);
            int yPlacement = getYPlacementInput(ship, scnr);
            boolean isHorizontal = getPlacementDirection(scnr);

            //placement is decremented by 1 since the map is indexed starting at 0
            if(ship.placeShip(xPlacement-1,yPlacement-1, isHorizontal, map)){
                //adds ships location to map
                map.addShip(ship.getLocation());
                map.printMap();
                break;
            }
            System.out.println("Please input a valid ship placement");
            map.printMap();
        }
    }

}