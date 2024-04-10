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

        Ships opponentCarrier = new Ships(5);
        Ships opponentBattleship = new Ships(4);
        Ships opponentCruiser = new Ships(3);
        Ships opponentSubmarine = new Ships(3);
        Ships opponentDestroyer = new Ships(2);

        ArrayList<Ships> playerFleet = new ArrayList<>();
        playerFleet.add(carrier);
        playerFleet.add(battleship);
        playerFleet.add(cruiser);
        playerFleet.add(submarine);
        playerFleet.add(destroyer);

        ArrayList<Ships> opponentFleet = new ArrayList<>();
        opponentFleet.add(opponentCarrier);
        opponentFleet.add(opponentBattleship);
        opponentFleet.add(opponentCruiser);
        opponentFleet.add(opponentSubmarine);
        opponentFleet.add(opponentDestroyer);

        System.out.println("Battle ship has a 10 x 10 board size.");
        System.out.println("Ship maps");
        System.out.println("0 means no ship");
        System.out.println("1 means no ship and location was shot");
        System.out.println("2 means ship is there but not hit");
        System.out.println("3 means ship is there and was hit");

        System.out.println();

        System.out.println("Attack maps");
        System.out.println("0 means nothing has been done at this square");
        System.out.println("1 means the location was shot but no ship was on that square");
        System.out.println("2 means the location was shot and there is a ship on that square");
        playerMap.printMap();
        System.out.println("\n");

        placeShipInput(carrier, playerMap, scnr);
        placeShipInput(battleship, playerMap, scnr);
        placeShipInput(cruiser, playerMap, scnr);
        placeShipInput(submarine, playerMap, scnr);
        placeShipInput(destroyer, playerMap, scnr);

        clearTerminal();

        System.out.println("Now it is the opponents turn to place their ships");
        opponentMap.printMap();
        placeShipInput(opponentCarrier, opponentMap, scnr);
        placeShipInput(opponentBattleship, opponentMap, scnr);
        placeShipInput(opponentCruiser, opponentMap, scnr);
        placeShipInput(opponentSubmarine, opponentMap, scnr);
        placeShipInput(opponentDestroyer, opponentMap, scnr);

        clearTerminal();

        boolean gameDone = false;
        while(!gameDone){
            //players attack turn
            System.out.println("Player 1 Attack turn");
            System.out.println("Attack Map: ");
            playerAttackMap.printMap();
            System.out.println("\n\n\n");
            System.out.println("Player 1 ship map: ");
            playerMap.printMap();
            if(callAttack(scnr, opponentMap, playerAttackMap, opponentFleet)){
                System.out.println("Player 1 won!");
                gameDone = true;
            }
            clearTerminal();
            //opponents attack turn
            System.out.println("Player 2 Attack turn");
            System.out.println("Attack Map: ");
            opponentAttackMap.printMap();
            System.out.println("\n\n\n");
            System.out.println("Player 2 ship map: ");
            opponentMap.printMap();
            if(callAttack(scnr, playerMap, opponentAttackMap, playerFleet)){
                System.out.println("Player 2 won!");
                gameDone = true;
            }
            clearTerminal();
        }


    }

    public static void clearTerminal(){
        //placeholder for a better way of clearing terminal
        System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    public static int getXPlacementInput(Ships ship, Scanner scnr){
        int xPlacement;
        System.out.println("Where would you like to place your ship? ("+ship.getHp()+ " spaces)");
        System.out.print("x position: ");
        while(true){
            if(scnr.hasNextInt()){
                xPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to place your ship? ("+ship.getHp()+ " spaces)");
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
        System.out.println("Where would you like to place your ship? ("+ship.getHp()+ " spaces)");
        System.out.print("y position: ");
        while(true){
            if(scnr.hasNextInt()){
                yPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to place your ship? ("+ship.getHp()+ " spaces)");
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
                System.out.println("Invalid direction argument.");
                scnr.nextLine();
            }
        }
    }


    public static int getXPlacementInputAttack(Scanner scnr){
        int xPlacement;
        System.out.println("Where would you like to attack?");
        System.out.print("x position: ");
        while(true){
            if(scnr.hasNextInt()){
                xPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to attack?");
                System.out.print("x position: ");
                scnr.nextLine();
            }
        }
        //clear scanner
        scnr.nextLine();
        return xPlacement;
    }
    public static int getYPlacementInputAttack(Scanner scnr){
        int yPlacement;
        System.out.println("Where would you like to attack?");
        System.out.print("y position: ");
        while(true){
            if(scnr.hasNextInt()){
                yPlacement = scnr.nextInt();
                break;
            }
            else{
                System.out.println("Invalid argument");
                System.out.println("Where would you like to attack?");
                System.out.print("y position: ");
                scnr.nextLine();
            }
        }
        //clear scanner
        scnr.nextLine();
        return yPlacement;
    }

    public static void placeShipInput(Ships ship,Map map, Scanner scnr){
        //ask for user ship placement
        while (true) {
            //
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

    //returns true if all opponent ships are destroyed
    public static boolean callAttack(Scanner scnr, Map opponentMap, Map playerAttackMap, ArrayList<Ships> opponentFleet){
        boolean isRepeat= true;
        while(isRepeat){
            int x = getXPlacementInputAttack(scnr)-1;
            int y = getYPlacementInputAttack(scnr)-1;
            if(opponentMap.checkAttack(x, y) == 0){
                opponentMap.updateMap(x, y, 0);
                playerAttackMap.updateAttackMap(x, y, 0);
                isRepeat = false;
            }
            else if(opponentMap.checkAttack(x, y) == 1){
                opponentMap.updateMap(x, y, 1);
                //check and update
                for(int i = 0 ; i < opponentFleet.size(); i++){
                    for(int j = 0; j < opponentFleet.get(i).getHp(); j++){
                        int shipYCoordinate = opponentFleet.get(i).getLocation().get(j).get(0);
                        int shipXCoordinate = opponentFleet.get(i).getLocation().get(j).get(1);
                        //check the location for each ship in the fleet
                        if(shipYCoordinate == y && shipXCoordinate == x){
                            //change the correct section to be true
                            opponentFleet.get(i).getSectionsHit().set(j, true);
                        }
                    }
                }
                boolean allShipsDestroyed = true;
                for(int i = 0 ; i < opponentFleet.size(); i++){
                    for(int j = 0; j < opponentFleet.get(i).getHp(); j++){
                        if(opponentFleet.get(i).getSectionsHit().get(j) == false){
                            allShipsDestroyed = false;
                        }
                    }
                }
                playerAttackMap.updateAttackMap(x, y, 1);
                return allShipsDestroyed;
            }
            //otherwise the is attack is a repeat
        }
        return false;
    }
}