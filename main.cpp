/**
 * @file main.cpp
 * @author Jhonathan Tepan (jhonathan.tepan51@myhunter.cuny.edu)
 * @brief testing out the BST Playlist and it is many different functions that apply to this Binary search tree. 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<iostream>
#include "Playlist.hpp"

int main(){
    //constructor at work creates a Playlist names spotify
    Playlist spotify; 
    //we add songs(nodes) to spotify 
    spotify.add("Humble", "Kendrick Lamar");
    spotify.add("Espresso", "Sabrina Carpenter");
    spotify.add("Nights", "Frank Ocean");
    spotify.add("Nights", "Frank Ocean");
    //this one does not get added because the song name is empty
    spotify.add("", "Frank Ocean");

    Playlist apple_music;
    apple_music.add("Not Like Us", "Sadab");

    //move constructor
    Playlist sadabs_music = std::move(apple_music);

    //copy constructor at work 
    Playlist jhonathans_music =  sadabs_music;

    sadabs_music.add("My Favorite Things", "John Coltrane");
    sadabs_music.add("Not Afraid" , "MnMs");

    //copy assignment operator at work 
    spotify =  sadabs_music;

    //move assignment operator 
    jhonathans_music = std::move(spotify);

    //isEmpty function and clear function 
    if( jhonathans_music.isEmpty()){
        std::cout<<"there is no music in this playlist" <<std::endl;
    }
    else{
        std::cout<<"hola como estas" <<std::endl;
    }
    jhonathans_music.clear();
    if( jhonathans_music.isEmpty()){
        std::cout<<"there is no music in this playlist" <<std::endl;
    }
    else{
        std::cout<<"there is music in this playlist" <<std::endl;
    }

    //testing the height function
    int height_of_sadabs_music = sadabs_music.getHeight();
    std::cout<<"This is the height of the Playlist tree sadabs music "<<height_of_sadabs_music <<std::endl;

    //testing get number of songs
    int num_of_songs = apple_music.getNumberOfSongs();

    //remove function should remove 'not afraid by MnMs' should not remove 'Not afraid by eminem'
    if(sadabs_music.remove("Not Afraid", "MnMs")){
        std::cout<< "song was succesfully removed" << std::endl;
    }
    if(!(sadabs_music.remove("Not Afraid", "Eminem"))){
        std::cout<< "song was not removed" << std::endl;
    }
    spotify.add("Nights" , "Frank Ocean");
    //testing the search function
    bool found = spotify.search( "Bad Blood", "Sabrina Carpenter");
    bool found2 = spotify.search("Nights", "Frank Ocean");
    if( found){
        std::cout<< "bad blood was found correctly " << std::endl;
    }
    else
        std::cout<<"bad blood was not found" <<std::endl;
    if(found2){
        std::cout<< "Nights by Frank Ocean was found " << std::endl;
    }
    else{
        std::cout<< "Nights by Frank Ocean was not found " << std::endl;
    } 
    sadabs_music.add("Beat It" , "Micheal Jackson");
    sadabs_music.add("Billie Jean" , "Micheal Jackson");
    sadabs_music.add("Beat It" , "Jhonathan");
    //testing preorder traverse
    std::vector<SongNode> songs_in_sadabs = sadabs_music.preorderTraverse();
    for(SongNode song: songs_in_sadabs){
        std::cout<< song.song_ <<" by "<<song.artist_ << std::endl;
    }
    std::cout<<std::endl;
    //testing inorder
    std::vector<SongNode> songs_in_sadabs2 = sadabs_music.inorderTraverse();
    for(SongNode song: songs_in_sadabs2){
        std::cout<< song.song_ <<" by "<<song.artist_ << std::endl;
    }
    std::cout<<std::endl;
    //testing postorder
    std::vector<SongNode> songs_in_sadabs3 = sadabs_music.postorderTraverse();
    for(SongNode song: songs_in_sadabs3){
        std::cout<< song.song_ <<" by "<<song.artist_ << std::endl;
    }
}