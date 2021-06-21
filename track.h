#ifndef __TRACK_H__
#define __TRACK_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>

#define MAX_ID 50
#define MAX_NAME 512
#define MAX_ARTISTS 512
#define MAX_ID_ARTISTS 512
#define MAX_RELEASE_DATE 128

using namespace std;

struct Track{
    char id[MAX_ID];
    char name[MAX_NAME];
    int popularity;
    int duration;
    int explicitt; // explicit parece ser uma palavra reservada
    char artist[MAX_ARTISTS];
    char idArtist[MAX_ID_ARTISTS];
    char releaseDate[MAX_RELEASE_DATE];
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int timeSignature;
};

void track_Save(Track &art, ofstream &file);
void track_Read(Track &track,ifstream &file, int n, int tam);
void imprime_TrackV(vector<Track> track);
void imprime_Track(Track &track);
int track_Size();

#endif // __TRACK_H__