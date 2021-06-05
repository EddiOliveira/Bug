#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>

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

void artista_Read(Artista &art,ifstream &file, int n, int tam)
{
    // file.seekg(0, ios::end);
    // int fileSize = file.tellg();
    //file.seekg(0, ios::beg);
    // file.seekg(n*tam, ios::cur);
    int adress = n*tam;
    file.seekg(adress, ios::beg);

    //if(file.peek() != EOF)
    if(!file.eof())
    {
        file.read(art.id, sizeof(art.id));
        file.read((char*)&art.followers, sizeof(art.followers));
        file.read(art.genres, sizeof(art.genres));
        file.read(art.name, sizeof(art.name));
        file.read((char*)&art.popularity, sizeof(art.popularity));
    }
    else
        file.seekg(0, ios::beg);
}

// Abaixo tem uma função pra tentar salvar de dados binários 
// direto pra vetor, mas está dando erro
// void artista_Vector_Read(vector<Artista> &vec,ifstream &file, int i)
// {
//     file.read(vec[i].id, sizeof(vec[i].id));
//     file.read((char*)&vec[i].followers, sizeof(vec[i].followers));
//     file.read(vec[i].genres, sizeof(vec[i].genres));
//     file.read(vec[i].name, sizeof(vec[i].name));
//     file.read((char*)&vec[i].popularity, sizeof(vec[i].popularity));
// }

int artista_Size()
{
    return  sizeof(char) * MAX_ID 
          + sizeof(char) * MAX_GENRES  
          + sizeof(char) * MAX_NAME
          + sizeof(float)
          + sizeof(int);   
}

void registra_ArtistaV(vector<Artista> &regArt ,Artista &art)
{ 
    regArt.push_back(art);
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

bool verificaCaractere(string word)
{
    return word[word.size()-1] == ']' || word[word.size()-1] == '"';
}

