#include <iostream>
#include <fstream>
#include <cstring>
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


void artista_Save(Artista &art, ofstream &file)
{
    file.write(art.id, sizeof(art.id));
    file.write((char*)&art.followers, sizeof(art.followers));
    file.write(art.genres, sizeof(art.genres));
    file.write(art.name, sizeof(art.name));
    file.write((char*)&art.popularity, sizeof(art.popularity));
}

void artista_Read(Artista &art,ifstream &file)
{
    file.read(art.id, sizeof(art.id));
    file.read((char*)&art.followers, sizeof(art.followers));
    file.read(art.genres, sizeof(art.genres));
    file.read(art.name, sizeof(art.name));
    file.read((char*)&art.popularity, sizeof(art.popularity));
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


// *********************************** MAIN ******************************************************


int main()
{
    //pega dados de artistas.csv e salva em objeto da struct Artista
    ifstream fileIn;
    fileIn.open("artistas.csv");
    Artista art1;
    ofstream binFileOut;
    binFileOut.open("artistas.bin", ios::out | ios::binary);

    if(fileIn.is_open() && binFileOut.is_open())
    {
        string tmp;
        string aux = "";
        fileIn.ignore(1000, '\n'); //ignora linha até encontrar 1000 caracteres ou quebra de linha

        cout << "\n\nLeitura de art antes do bin: " << endl << endl;

        while(!fileIn.eof())
        {
            getline(fileIn, tmp, ',');
            strcpy(art1.id, tmp.c_str());

            getline(fileIn, tmp, ',');
            art1.followers = atof(tmp.c_str());

            getline(fileIn, tmp, ',');      


            while(!verificaCaractere(tmp))
            {
                aux += tmp + ',';
                getline(fileIn, tmp, ',');   
            }
            aux += tmp;
            strcpy(art1.genres, aux.c_str());
            aux = "";


            getline(fileIn, tmp, ',');   
            strcpy(art1.name, tmp.c_str());

            getline(fileIn, tmp, '\n');
            art1.popularity = atoi(tmp.c_str());


            imprime_Artista(art1);
            artista_Save(art1,binFileOut);
        }
        binFileOut.close();
        fileIn.close();
    }
    else
    {
        cout << "Erro" << endl;
        exit(1);
    } 

    ifstream binFileIn;
    binFileIn.open("artistas.bin", ios::in | ios::binary);

    if(binFileIn.is_open())
    {
        Artista art;

        cout << "\n\nLeitura de art depois do bin: " << endl;
        //while(!binFileIn.eof())
        //usar while(!binFileIn.eof()) estava lendo o último dado 2x
        while(binFileIn.peek()!=EOF)
        {   
            artista_Read(art, binFileIn);
            imprime_Artista(art);
            cout << endl;
        }
        binFileIn.close();
    }
    else
    {
        cout << "Erro ao abrir arquivo bin in";
        exit(2);
    }
    
return 0;
}