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


// *********************************** MAIN ******************************************************


int main()
{
    srand(time(NULL));
    
    ifstream fileIn;
    fileIn.open("artistas.csv");

    ofstream binFileOut;
    binFileOut.open("artistas.bin", ios::out | ios::binary);

    Artista art1;
    vector<Artista> artV;
    

    //pega dados de artistas.csv e salva em objeto art1 da struct Artista
    //depois salva em binário em artistas.bin 
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



    //lê dados aleatórios em artistas.bin e coloca em vetor para leitura
    ifstream binFileIn;
    binFileIn.open("artistas.bin", ios::in | ios::binary);

    if(binFileIn.is_open())
    {
        Artista art;
        int n; 
        int tam = artista_Size();
        int k = 0;

        cout << "\n\ntamanho de strucu Artista: " << tam << endl << endl;
        cout << "Numero aleatorio: " << n << endl << endl; 

        //while(!binFileIn.eof()) estava lendo o último dado 2x
        // while(binFileIn.peek() != EOF)
        while(k < 3)
        {   
            n = rand()%5;
            artista_Read(art, binFileIn, n, tam);
            registra_ArtistaV(artV, art);
            k++;
        }
        binFileIn.close();
        cout << "Registro realizado com sucesso!" << endl;
        cout << "\nLeitura de art depois do bin usando vetor: " << endl << endl;
        imprime_ArtistaV(artV);
    }
    else
    {
        cout << "Erro ao abrir arquivo bin in";
        exit(2);
    }
    
return 0;
}