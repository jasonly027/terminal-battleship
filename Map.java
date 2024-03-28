package org.example;
import java.util.ArrayList;

public class Map {





    private int[][] map = new int[10][10];
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
            this.map[x][y] = 1;
        }
    }

    public void updateMap(){

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

}
