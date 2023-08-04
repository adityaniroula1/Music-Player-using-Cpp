//Title: Playlist.cpp
//Author : Aditya Niroula
//Date : 11/2/2022
//Desc : Playlist file

#include <iostream>
#include "Playlist.h"
#include "Song.h"
using namespace std;


// Name: Playlist() - Default Constructor
// Desc - Creates a new empty playlist
// Preconditions - None
// Postconditions - Sets everything to either nullptr or 0

Playlist::Playlist(){
    m_head = nullptr;
    m_size = 0;
    m_tail = nullptr;

}
// Name: ~Playlist - Destructor
// Desc - Removes all of the songs from the playlist
// Preconditions - Playlist must have songs
// Postconditions - Playlist will be empty and m_head and m_tail will be nullptr. Size will be 0

Playlist::~Playlist(){
    Song* temp = m_head;
    while (temp != nullptr){
        m_head = temp;
        temp = temp->GetNext();
        delete m_head;
    }
    m_head = nullptr;
    m_size = 0;
    m_tail = nullptr;
}
// Name: AddSong(string, string, int, int)
// Desc - Dynamically allocates new song using title, artist, year, and rank
// Preconditions - Playlist allocated
// Postconditions - New song inserted in end of list

void Playlist::AddSong(string title, string artist, int year, int rank){

    Song* NewSong = new Song(title, artist, year, rank);
    if(m_head == nullptr) {
        m_head = NewSong;
    }
    m_tail->SetNext(NewSong);
    m_tail = NewSong;
    m_size++;
    //NewSong->SetNext(nullptr);
    delete NewSong;
}
// Name: GetPlaylistDetails()
// Desc - Returns a song object from a specific location
// Preconditions - Playlist populated
// Postconditions - Returns the data (does not output it)

Song* Playlist::GetPlaylistDetails(int location) {
    Song *curr = m_head;
    //updating the address of node
    for (int i = 0; i < location - 1; i++){
        curr = curr->GetNext();
    }
    return curr;
}

// Name: Size
// Desc - Returns the m_size
// Preconditions - Playlist starts at size 0
// Postconditions - Returns the size

int Playlist:: Size(){
    return m_size;
}
// Name: PlayAt
// Desc - Passed the song that is to be played from the playlist
//       "Plays" a song by removing it from the playlist at a specific location
// Recommendations - Code this function last (dead last)
// Preconditions - Playlist has been populated
// Hint: Do not forget about removing from the front, middle, or end of the list
//       Could also remove the only node
// Postconditions - Playlist is reduced in size by one based on which song is played
void Playlist::PlayAt(int location) {
    //if front is removed the m_head will point to its next node
    if (location == 1){
        m_head = m_head->GetNext();
    //if end node, it will update m_tail and m_next
    }else if (location == m_size){
        m_tail = GetPlaylistDetails(location - 1);
        m_tail->SetNext(nullptr);
        // if middle node is removed, it will update the pointer of its previous node to its next node
    }else{
        GetPlaylistDetails(location - 1)->SetNext(GetPlaylistDetails(location + 1));
    }
    m_size--;
}

