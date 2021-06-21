#include <iostream>
#include <fstream>
#include <vector>

#include "track.h"

using namespace std;


void track_Save(Track &track, ofstream &file)
{
    file.write(track.id, sizeof(track.id));
    file.write(track.name, sizeof(track.name));
    file.write((char*)&track.popularity, sizeof(track.popularity));
    file.write((char*)&track.duration, sizeof(track.duration));
    file.write((char*)&track.explicitt, sizeof(track.explicitt));
    file.write(track.artist, sizeof(track.artist));
    file.write(track.idArtist, sizeof(track.idArtist));
    file.write(track.releaseDate, sizeof(track.releaseDate));
    file.write((char*)&track.danceability, sizeof(track.danceability));
    file.write((char*)&track.energy, sizeof(track.energy));
    file.write((char*)&track.key, sizeof(track.key));
    file.write((char*)&track.loudness, sizeof(track.loudness));
    file.write((char*)&track.mode, sizeof(track.mode));
    file.write((char*)&track.speechiness, sizeof(track.speechiness));
    file.write((char*)&track.acousticness, sizeof(track.acousticness));
    file.write((char*)&track.instrumentalness, sizeof(track.instrumentalness));
    file.write((char*)&track.liveness, sizeof(track.liveness));
    file.write((char*)&track.valence, sizeof(track.valence));
    file.write((char*)&track.tempo, sizeof(track.tempo));
    file.write((char*)&track.timeSignature, sizeof(track.timeSignature));
}

void track_Read(Track &track,ifstream &file, int n, int tam)
{
    
    file.seekg(n * tam, ios::beg);

    if(!file.eof())
    {
        file.read(track.id, sizeof(track.id));
        file.read(track.name, sizeof(track.name));
        file.read((char*)&track.popularity, sizeof(track.popularity));
        file.read((char*)&track.duration, sizeof(track.duration));
        file.read((char*)&track.explicitt, sizeof(track.explicitt));
        file.read(track.artist, sizeof(track.artist));
        file.read(track.idArtist, sizeof(track.idArtist));
        file.read(track.releaseDate, sizeof(track.releaseDate));
        file.read((char*)&track.danceability, sizeof(track.danceability));
        file.read((char*)&track.energy, sizeof(track.energy));
        file.read((char*)&track.key, sizeof(track.key));
        file.read((char*)&track.loudness, sizeof(track.loudness));
        file.read((char*)&track.mode, sizeof(track.mode));
        file.read((char*)&track.speechiness, sizeof(track.speechiness));
        file.read((char*)&track.acousticness, sizeof(track.acousticness));
        file.read((char*)&track.instrumentalness, sizeof(track.instrumentalness));
        file.read((char*)&track.liveness, sizeof(track.liveness));
        file.read((char*)&track.valence, sizeof(track.valence));
        file.read((char*)&track.tempo, sizeof(track.tempo));
        file.read((char*)&track.timeSignature, sizeof(track.timeSignature));
    }
    else
    {
        file.seekg(0, ios::beg);
    }
}

int track_Size()
{
    return  sizeof(char) * MAX_ID  
            + sizeof(char) * MAX_NAME
            + sizeof(int)
            + sizeof(int)
            + sizeof(int)
            + sizeof(char) * MAX_ARTISTS
            + sizeof(char) * MAX_ID_ARTISTS   
            + sizeof(char) * MAX_RELEASE_DATE   
            + sizeof(float)
            + sizeof(float)
            + sizeof(int)
            + sizeof(float)
            + sizeof(int)
            + sizeof(float)
            + sizeof(float)
            + sizeof(float)
            + sizeof(float)
            + sizeof(float)
            + sizeof(float)
            + sizeof(int);
}

void imprime_TrackV(vector<Track> track){
    for(int i=0; i<track.size(); i++)
    {
        cout << "Id: " << track[i].id << endl;
        cout << "Name: " << track[i].name << endl;
        cout << "Popularity: " << track[i].popularity << endl;
        cout << "Duration: " << track[i].duration << endl;
        cout << "Explicit: " << track[i].explicitt << endl;
        cout << "Artist: " << track[i].artist << endl;
        cout << "Id artist: " << track[i].idArtist << endl;
        cout << "Release date: " << track[i].releaseDate << endl;
        cout << "Danceability: " << track[i].danceability << endl;
        cout << "Energy: " << track[i].energy << endl;
        cout << "Key: " << track[i].key << endl;
        cout << "Loudness: " << track[i].loudness << endl;
        cout << "Mode: " << track[i].mode << endl;
        cout << "Speechiness: " << track[i].speechiness << endl;
        cout << "Acousticness: " << track[i].acousticness << endl;
        cout << "Instrumentalness: " << track[i].instrumentalness << endl;
        cout << "Liveness: " << track[i].liveness << endl;
        cout << "Valence: " << track[i].valence << endl;
        cout << "Tempo: " << track[i].tempo << endl;
        cout << "Time signature: " << track[i].timeSignature << endl << endl;
    }
}

void imprime_Track(Track &track){
    cout << "Id: " << track.id << endl;
    cout << "Name: " << track.name << endl;
    cout << "Popularity: " << track.popularity << endl;
    cout << "Duration: " << track.duration << endl;
    cout << "Explicit: " << track.explicitt << endl;
    cout << "Artist: " << track.artist << endl;
    cout << "Id artist: " << track.idArtist << endl;
    cout << "Release date: " << track.releaseDate << endl;
    cout << "Danceability: " << track.danceability << endl;
    cout << "Energy: " << track.energy << endl;
    cout << "Key: " << track.key << endl;
    cout << "Loudness: " << track.loudness << endl;
    cout << "Mode: " << track.mode << endl;
    cout << "Speechiness: " << track.speechiness << endl;
    cout << "Acousticness: " << track.acousticness << endl;
    cout << "Instrumentalness: " << track.instrumentalness << endl;
    cout << "Liveness: " << track.liveness << endl;
    cout << "Valence: " << track.valence << endl;
    cout << "Tempo: " << track.tempo << endl;
    cout << "Time signature: " << track.timeSignature << endl;
}

