//Title: Song.cpp
//Author : Aditya Niroula
//Date : 11/2/2022
//Desc : Song file
#include "Song.h"


using namespace std;

//Name: Song - Default Constructor
//Precondition: None
//Postcondition: Creates a default song using "New Title", "New Artist", 0 , 0 and sets m_next = nullptr;
Song::Song() {
    m_title = "New Title";
    m_artist = "New Artist";
    m_rank = 0;
    m_year = 0;
    m_next = nullptr;
}

//Name: Song - Overloaded Constructor
//Precondition: Requires title, artist, year, and rank
//Postcondition: Creates a song based on passed parameters and sets m_next = nullptr;
Song::Song(string title, string artist, int year, int rank) {
    m_title = title;
    m_artist = artist;
    m_rank = rank;
    m_year = year;
    m_next = nullptr;
}

//Name: Mutators and Accessors
//May or may not be used specifically but implement all
//Precondition: None
//Postcondition: Sets and Gets private member variables
string Song::GetTitle(){
    return m_title;
} // return title
string Song::GetArtist(){
    return m_artist;
} // return artist
int Song::GetYear(){
    return m_year;
} // return year
int Song::GetRank(){
    return m_rank;
} // return rank (1-100 from that year)


void Song::SetTitle(string title){
    m_title = title;
} // sets title
void Song::SetArtist(string artist){
    m_artist = artist;
} //sets artist
void Song::SetYear(int year){
    m_year = year;
} //sets year
void Song::SetRank(int rank){
    m_rank = rank;
} //sets rank


// Linked List specific getters and setters
// Name: GetNext()
// Desc: Returns the pointer to the next song
// Preconditions: None (may return either song or nullptr)
// Postconditions: Returns m_next;
Song* Song::GetNext(){
    return m_next;
}
// Name: SetNext()
// Desc: Updates the pointer to a new target (either a song or nullptr)
// Preconditions: None
// Postconditions: Sets the next song
void Song::SetNext(Song* Song){
    m_next = Song;
}

