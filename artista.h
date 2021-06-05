#ifndef __ARTISTA_H__
#define __ARTISTA_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;

#define MAX_ID 50
#define MAX_FOLLOWERS 10
#define MAX_GENRES 512
#define MAX_NAME 512
#define MAX_POPULARITY 10


struct Artista
{
    char id[MAX_ID]; 
    float followers;
    char genres[MAX_GENRES];
    char name[MAX_NAME]; 
    int popularity;
};


void artista_Save(Artista &art, ofstream &file);

void artista_Read(Artista &art,ifstream &file, int n, int tam);

int artista_Size();

void registra_ArtistaV(vector<Artista> &regArt ,Artista &art);

void imprime_ArtistaV(vector<Artista> regArt);

void imprime_Artista(Artista &art);

bool verificaCaractere(string word);

#endif // __ARTISTA_H__