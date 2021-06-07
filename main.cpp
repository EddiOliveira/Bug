#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <sstream>

#include "artista.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    if(argc < 2) // ./main ./input
    {
        cout << "Uso: " << argv[0] << " diretorio arquivo de entrada" << endl;
        return 0;
    }

    string dir = argv[1];
    string artistaCsv = dir + "/artistas.csv";
    string artistaBin = dir + "/artistas.bin";

    srand(time(NULL));
    
    ifstream fileIn;
    fileIn.open(artistaCsv);

    ofstream binFileOut;
    binFileOut.open(artistaBin, ios::out | ios::binary);

    Artista art1;
    vector<Artista> artV;
    

    //pega dados de artistas.csv e salva em objeto art1 da struct Artista
    //depois salva em binário em artistas.bin 
    if(fileIn.is_open() && binFileOut.is_open())
    {
        string tmp;
        string aux = "";
        string line;
        fileIn.ignore(1000, '\n'); //ignora linha até encontrar 1000 caracteres ou quebra de linha

        cout << "\n\nLeitura de art antes do bin: " << endl << endl;

        // while(!fileIn.eof())
        while(getline(fileIn, line))
        {
            stringstream sstr(line);


            getline(sstr, tmp, ',');
            strcpy(art1.id, tmp.c_str());

            getline(sstr, tmp, ',');
            art1.followers = atof(tmp.c_str());

            getline(sstr, tmp, ',');     


            while(!verificaCaractere(tmp))
            {
                aux += tmp + ',';
                // getline(fileIn, tmp, ','); 
                getline(sstr, tmp, ',');  
            }
            aux += tmp;
            strcpy(art1.genres, aux.c_str());
            aux = "";


            getline(sstr, tmp, ',');  
            strcpy(art1.name, tmp.c_str());

            getline(sstr, tmp, ',');
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
    binFileIn.open(artistaBin, ios::in | ios::binary);

    if(binFileIn.is_open())
    {
        Artista art;
        int n; 
        int tam = artista_Size();
        int k = 0;
        int j;

        cout << "\n\ntamanho de strucu Artista: " << tam << endl << endl;
        cout << "Numero aleatorio: " << n << endl << endl; 

        cout << "Digite quantos dados vc quer armazenar: ";
        cin >> j;
        artV.resize(j);

        //while(!binFileIn.eof()) estava lendo o último dado 2x
        // while(binFileIn.peek() != EOF)
        while(k < j)
        {   
            n = rand()%5;
            artista_Read(artV[k], binFileIn, n, tam);
            //registra_ArtistaV(artV, art);
            k++;
        }
        binFileIn.close();
        cout << "\nRegistro realizado com sucesso!" << endl;
        cout << "\nLeitura de art aleatoria depois do bin usando vetor: " << endl << endl;
        imprime_ArtistaV(artV);
    }
    else
    {
        cout << "Erro ao abrir arquivo bin in";
        exit(2);
    }
    
return 0;
}
