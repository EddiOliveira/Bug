#include <iostream>
#include <fstream>
#include <vector>

#include "artista.h"

using namespace std;


void artista_Save(Artista &art, ofstream &file)
{
    file.write(art.id, sizeof(art.id));
    file.write((char*)&art.followers, sizeof(art.followers));
    file.write(art.genres, sizeof(art.genres));
    file.write(art.name, sizeof(art.name));
    file.write((char*)&art.popularity, sizeof(art.popularity));
}

void artista_Read(Artista &art,ifstream &file, int n, int tam){

    
    file.seekg(n*tam, ios::beg);

    if(!file.eof()){
        file.read(art.id, sizeof(art.id));
        file.read((char*)&art.followers, sizeof(art.followers));
        file.read(art.genres, sizeof(art.genres));
        file.read(art.name, sizeof(art.name));
        file.read((char*)&art.popularity, sizeof(art.popularity));
    }
    else
        file.seekg(0, ios::beg);
}

int artista_Size()
{
    return  sizeof(char) * MAX_ID 
          + sizeof(char) * MAX_GENRES  
          + sizeof(char) * MAX_NAME
          + sizeof(float)
          + sizeof(int);   
}

void imprime_ArtistaV(vector<Artista> regArt)
{
    for(int i=0; i<regArt.size(); i++)
    {
        cout << "Id: " << regArt[i].id << endl;
        cout << "Followers: " <<  regArt[i].followers << endl;
        cout << "Genres: " <<  regArt[i].genres << endl;
        cout << "Name: " << regArt[i].name << endl;
        cout << "Popularity: " << regArt[i].popularity << endl << endl;
    }
}

void imprime_Artista(Artista &art)
{
    cout << "Id: " << art.id << endl;
    cout << "Followers: " <<  art.followers << endl;
    cout << "Genres: " <<  art.genres << endl;
    cout << "Name: " << art.name << endl;
    cout << "Popularity: " << art.popularity << endl << endl;
}
