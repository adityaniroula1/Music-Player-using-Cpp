//Title: MusicPlayer.cpp
//Author : Aditya Niroula
//Date : 11/2/2022
//Desc : Musicplayer file

#include "MusicPlayer.h"
#include "Playlist.h"
#include "Song.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>


using namespace std;

//Name: MusicPlayer - Default Constructor
//Precondition: None
//Postcondition: Dynamically creates a new MusicPlayer [and populates m_filename FILE_NAME]
MusicPlayer::MusicPlayer(){
}

//Name: ~MusicPlayer - Destructor
//Precondition: None
//Postcondition: Destructs all songs in the catalog and all songs in the playlist
MusicPlayer::~MusicPlayer() {
    for(int i=0; i < m_songCatalog.size(); i++){
        delete m_songCatalog[i];
    }
    delete m_playList;
}

//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file of songs into the m_songCatalog (as song objects) using the DELIMITER
void MusicPlayer::LoadCatalog(string filename){
    string artist;
    string title;
    string y;
    string r;
    int year =0;
    int rank = 0;

    ifstream inputFile;
    inputFile.open(filename);
    for (int i = 0; i < 1200; i++){
        getline(inputFile, title, DELIMITER);
        getline(inputFile, artist, DELIMITER);
        getline(inputFile, y, DELIMITER);
        getline(inputFile, r, '\n');
        year = stoi(y);
        rank = stoi(r);
        Song* newSong = new Song(title, artist, year, rank);
        m_songCatalog.push_back(newSong);
        }
    inputFile.close();
}

//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu. Calls until user chooses to quit.
void MusicPlayer::MainMenu(){
    int option = 0;
    while (option != 5) {
        cout << "What would you like to do?" << endl;
        cout << "1. Display Songs by Year" << endl;
        cout << "2. Add Song" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Play Song" << endl;
        cout << "5. Quit" << endl;

        cin >> option;
        //input validation
        while (option < 1 or option > 5) {
            cout << "What would you like to do?" << endl;
            cout << "1. Display Songs by Year" << endl;
            cout << "2. Add Song" << endl;
            cout << "3. Display Playlist" << endl;
            cout << "4. Play Song" << endl;
            cout << "5. Quit" << endl;

            cin >> option;
        }

        //calling selected functions
        if (option == 1){
            DisplaySongs();
        }else if(option == 2){
            AddSong();
        }else if (option == 3){
            DisplayPlaylist();
        }else if(option == 4) {
            PlaySong();
        }
    }
    cout << "Thank You for using UMBC Music Player" << endl;

}
//Name: DisplaySongs
//Precondition: User enters year using constants above (2010-2021)
//Postcondition: Lists all songs (numbered) for that year by ranking
void MusicPlayer::DisplaySongs(){
    int year;
    cout << "Which year would you like to display? (2010-2021)" << endl;
    cin >> year;
    while (year < LOW_YEAR or year > HIGH_YEAR){
        cout << "Which year would you like to display? (2010-2021)" << endl;
        cin >> year;
    }
    cout << "******" << year << "*****" << endl;
    //looping through the songs to check the year and then print
    //cout  << m_songCatalog[1]->GetYear() << endl;
    for (unsigned i = 0; i < m_songCatalog.size(); i++) {
        if (m_songCatalog[i]->GetYear() == year){
            cout << *m_songCatalog[i] << endl;
        }
    }
}

//Name: AddSong
//Precondition: m_songCatalog is populated and m_playList exists
//Postcondition: Displays the songs for a specific year. Adds a song to the m_playList by dynamically allocating a new song based on the song in the catalog
//               and inserting it in the end.
//               May have duplicate songs on a playlist.
//               If the user chooses 2010, the user does not have to choose something from 2010 but it does need to be valid (between 1 - 1200)
void MusicPlayer::AddSong(){
    int Musicyear, rank, num, year;
    string title, artist;
    cout << m_playList->Size();
    if (m_playList->Size() == 0){
        cout << "***Current Playlist is Empty***" << endl;
    }
    cout << "Choose the songs you would like to add to the playlist." << endl;
    cout << "Which year would you like to display? (2010-2021)" << endl;
    cin >> Musicyear;
    cout << "******" << Musicyear << "*****" << endl;
    //display the songs of that year
    for (unsigned i = 0; i < m_songCatalog.size(); i++) {
        if (m_songCatalog[i]->GetYear() == Musicyear) {
            cout << *m_songCatalog[i];
        }
    }
    cout << "Enter the number of the song you would like to add:" << endl;
    cin >> num;
    //input validation
    while (num < 1 or num > 1200) {
        cout << "Enter the number of the song you would like to add:" << endl;
        cin >> num;
    }
    //dynamically allocating new song and then passing it to input in playlist
    title = m_songCatalog[num]->GetTitle();
    artist = m_songCatalog[num]->GetArtist();
    year = m_songCatalog[num]->GetYear();
    rank = m_songCatalog[num]->GetRank();
    Song *newSong = new Song(title, artist, year, rank);
    m_playList->AddSong(title, artist, year, rank);
    delete newSong;

}

//Name: DisplayPlaylist
//Precondition: None (can be empty)
//Postcondition: Displays the playlist or tells the user it is empty
void MusicPlayer::DisplayPlaylist(){
    //checking if playlist is empty
    if (m_playList->Size() == 0){
        cout << "***Current Playlist is Empty***" <<endl;
    }else{
        cout << "Your Playlist" << endl;
        for (int i = 0; i < m_playList->Size(); i++ ){
            cout << *m_playList->GetPlaylistDetails(i) << endl;
        }
    }
}

//Name: PlaySong
//Precondition: Playlist should be populated
//Postcondition: Allows the user to choose a song from the playlist to play.
//               Removes chosen song from playlist after "played"
void MusicPlayer::PlaySong(){
    if (m_playList->Size() == 0){
        cout << "***Current Playlist is Empty***" << endl;
    }else {
        int num = 0;
        DisplayPlaylist();
        cout << "Which song would you like to play?" << endl;
        cin >> num;
        while (num < 0 or num > m_playList->Size()) {
            cout << "Which song would you like to play?" << endl;
            cin >> num;
        }
        cout << "Played : " << *m_playList->GetPlaylistDetails(num) << endl;
    //calling play at to remove the song that was played
        m_playList->PlayAt(num);
    }
}