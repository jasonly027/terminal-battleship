package org.example;

import java.util.ArrayList;

public class Ships {
    private int hp;
    private ArrayList<ArrayList<Integer>> location = new ArrayList<ArrayList<Integer>>();
    public Ships(int hp){
        this.hp = hp;

    }

    //places a ship at a location either vertically or horizontally and stores it in the location array list
    //returns false if function failed and true if it ran successfully
    public boolean placeShip(int x, int y, boolean isHorizontal, Map map){
        if(!checkPlacement(x,y, isHorizontal, map)){
            System.out.println("invalid placement");
            return false;
        }

        if(isHorizontal){
            for(int i = 0; i < this.hp ; i++){
                ArrayList<Integer> temp = new ArrayList<>();
                //need to add it in reverse order since rows and columns are reversed in respect to x and y
                temp.add(y);
                temp.add(x+i);
                this.location.add(temp);
            }
        }
        else{
            for(int i = 0; i < this.hp ; i++){
                ArrayList<Integer> temp = new ArrayList<>();
                temp.add(y+i);
                temp.add(x);
                this.location.add(temp);
            }
        }
        return true;
    }
    public boolean checkPlacement(int x, int y, boolean isHorizontal, Map map){
        //makes sure that the placement is in bounds
        if(isHorizontal){
            if(this.hp + x > 10){
                return false;
            }
        }
        else{
            if(this.hp + y > 10){
                return false;
            }
        }
        //make sure that there isn't already a ship there
        if(isHorizontal){
            for(int i = 0; i <this.hp; i++ ){
                if(map.getMap()[y+i][x] != 0){
                    return false;
                }
            }
        }
        else{
            for(int i = 0; i <this.hp; i++ ){
                if(map.getMap()[y][x+i] != 0){
                    return false;
                }
            }
        }
        return true;
    }
    public int getHp(){
        return this.hp;
    }
    public ArrayList<ArrayList<Integer>> getLocation(){
        return this.location;
    }

}
