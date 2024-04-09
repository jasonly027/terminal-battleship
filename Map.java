package org.example;
import java.util.ArrayList;

public class Map {





    private int[][] map = new int[10][10];
    //initialize map with just 0s
    public Map(){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                this.map[i][j] = 0;
            }
        }
    }
    public void addShip(ArrayList<ArrayList<Integer>> location){
        for(int i = 0; i < location.size(); i++){
            int x = location.get(i).get(0);
            int y = location.get(i).get(1);
            this.map[x][y] = 2;
        }
    }

    //status could be 0,1:  0 means miss, 1 means hit
    public void updateMap(int x, int y, int status){
        if(status == 0){
            //attack miss
            this.map[y][x] = 1;
        }
        else if(status == 1){
            //attack hit
            this.map[y][x] = 3;
        }
    }

    public void updateAttackMap(int x, int y, int status){
        if(status == 0){
            //attack miss
            this.map[y][x] = 1;
        }
        else if(status == 1){
            //attack hit
            this.map[y][x] = 2;
        }
    }

    public void printMap(){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                System.out.print(this.map[i][j] + " ");
            }
            System.out.println();
        }
    }
    public int[][] getMap(){
        return this.map;
    }

    //returning 0 means miss, 1 means hit, 2 means already shot there
    public int checkAttack(int x, int y){
        if(this.map[y][x] == 0){
            System.out.println("You missed.");
            return 0;
        }
        //bug where a ship was hit is printed twice since we called checkAttack in another if statement in callAttack function in main
        else if(this.map[y][x] == 2){
            System.out.println("A ship was hit!");
            return 1;
        }
        //map location is either 1 or 3 either case means that a hot was already taken there
        else{
            return 2;
        }
    }

}
