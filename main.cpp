#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <sstream>
#include "artista.h"
#include "track.h"

using namespace std;

void printConsoleOrSaveFile(char &res);
void replace(string &aux);
bool verificaCaractere(string word);
void leArtistaCsv(ifstream &csvArtIn, ofstream &binArtOut, Artista &art, int &linhasArtistaCsv);
void geraVectorArtista(ifstream &binFile, int repeticoes,vector<Artista> &artistas, int tam, int &linhasArtistaCsv);
void leTrackCsv(ifstream &trackCsv, ofstream &trackBin, Track &track, int &linhasTrackCsv);
void geraVectorTrack(ifstream &csvTrackIn, int repeticoes, vector<Track> &tracks, int tam, int &linhasTrackCsv);
void geraArquivoFinal(ofstream &arquivoFinal ,string artistaCsvHeader, vector<Artista> artistas, string trackCsvHeader, vector<Track> tracks);
void imprime_Terminal(vector<Artista> &artistas, vector<Track> &tracks);






int main(int argc, char* argv[]){

    if(argc < 2){ // ./main ./input
        cout << "Informe um diretorio existente" << endl;
        return 0;
    }

    

    string dir = argv[1];
    string artistaCsv = dir + "/artists.csv";
    string artistaBin = dir + "/artists.bin";
    string trackCsv = dir + "/tracks.csv"; 
    string trackBin = dir + "/tracks.bin";
    string fileArtAndTracks = dir + "/artistsAndTracks.csv";

    string tmp;
    string aux = "";
    string artistaCsvHeader, trackCsvHeader;


    int qtdLinhas;
    int linhasArtistaCsv = 0, linhasTrackCsv = 0;

    
    ifstream csvArtIn, csvTrackIn;
    csvArtIn.open(artistaCsv);
    csvTrackIn.open(trackCsv);

    ofstream binArtOut, binTrackOut;
    binArtOut.open(artistaBin, ios::out | ios::binary);
    binTrackOut.open(trackBin, ios::out | ios::binary);

    ifstream binArtIn, binTrackIn;

    ofstream arquivo;
    arquivo.open(fileArtAndTracks);



    Artista art;
    vector<Artista> artV;
    
    Track track;
    vector <Track> tracks;
    int sizeTrackBin = 0; // precisa?

    

    

    //Parte comentada abaixo precisa ser implementada
    char res; //descomentar quando for implementar parte de gerar arquivo/imprimir no terminal
    cout << "Pressione a tecla 'c' para exibir os resultados no console." << endl << endl;
    cout << "Ou pressione a tecla 'a' para gerar um arquivo com os resultados." << endl << endl;
    cout << "Ou pressione a tecla 'e' para gerar um arquivo com os resultados." << endl << endl;
    cin >> res;
    cin.ignore();


    if(res != 'c' && res != 'a' && res != 'e'){
        printConsoleOrSaveFile(res);
    }

    if(res == 'c'){
        qtdLinhas = 10;
    }
    else if(res == 'a'){
        qtdLinhas = 100;
    }
    else{
        cout << "\nVoce escolheu sair do programa!" << endl;
        exit(1);
    }
  
   

    //pega dados de artists.csv e salva em objeto art da struct Artista
    //depois salva em binário em artists.bin 

    if(csvArtIn.is_open() && binArtOut.is_open())
    {
        getline(csvArtIn,artistaCsvHeader); // tirei o '\n' no 3º argumento, pois ele já pega a 1º linha toda
        leArtistaCsv(csvArtIn,binArtOut,art, linhasArtistaCsv);
        binArtOut.close();
        csvArtIn.close();
    }
    else
    {
        cout << "Erro ao abrir Artistas.csv" << endl;
        exit(1);
    } 

    // pega dados de track.csv e salva em objeto track da struct Track
    // depois salva em binário em tracks.bin

    if(csvTrackIn.is_open() && binTrackOut.is_open())
    {
        getline(csvTrackIn,trackCsvHeader); // tirei o '\n' no 3º argumento, pois ele já pega a 1º linha toda
        leTrackCsv(csvTrackIn,binTrackOut,track, linhasTrackCsv);
        csvTrackIn.close();
        binTrackOut.close();
    }
    else{
        cout << "Erro ao abrir track.csv" << endl;
        exit(1);
    }



    //lê dados aleatórios em artists.bin e tracks.bin e coloca em vetores 
    //para leitura ou para armazenar em novo arquivo artistsAndTracks.csv
    

    binArtIn.open(artistaBin, ios::in | ios::binary);
    binTrackIn.open(trackBin, ios::in  | ios::binary);

    

    if(binArtIn.is_open() && binTrackIn.is_open()){
        geraVectorArtista(binArtIn,qtdLinhas,artV,artista_Size(), linhasArtistaCsv);
        geraVectorTrack(binTrackIn,qtdLinhas,tracks,track_Size(), linhasTrackCsv);
        binTrackIn.close();
        binArtIn.close();            
    }

    
    if(res == 'c'){
        imprime_Terminal(artV, tracks);
    }
    else{
         arquivo.open(fileArtAndTracks, ios::out);
         if(arquivo.is_open()){
             geraArquivoFinal(arquivo, artistaCsvHeader, artV, trackCsvHeader, tracks);
         }
         arquivo.close();
    }

    return 0;
}





// ***************************** FIM DA MAIN ****************************************



void printConsoleOrSaveFile(char &res)
{
    while(res != 'c' && res != 'a' && res != 'e')
    {
        cout << "\nErro: voce digitou uma tecla errada" << endl;
        cout << "Pressione a tecla 'c' para exibir os resultados no console." << endl;
        cout << "Ou pressione a tecla 'a' para gerar um arquivo com os resultados." << endl;
        cout << "Ou pressione a tecla 'e' para sair do programa." << endl;
        cin >> res;
        cin.ignore();
    }
}

void replace(string &aux)
{
    int i = aux.size() - 1;

    while( i >= 0 && aux[i] == ' ' )
    {
        i--;
    }

    while( i >= 0 && aux[i] != ' ' )
    {
        aux[i] = ' ';
        i--;
    }
}


void leArtistaCsv(ifstream &csvArtIn, ofstream &binArtOut, Artista &art, int &linhasArtistaCsv){
    cout << "Lendo do arquivo artists.csv" << endl;
    string line;
    string tmp;
    string aux = "";

    //csvArtIn.ignore(1000, '\n'); //ignora linha até encontrar 1000 caracteres ou quebra de linha

    while(getline(csvArtIn, line)){
            linhasArtistaCsv++;
            stringstream sstr(line);

            getline(sstr, tmp, ',');
            strcpy(art.id, tmp.c_str());

            getline(sstr, tmp, ',');
            art.followers = atof(tmp.c_str());

            

            // if(sstr.peek() == '\"')
            // {
            //     sstr.get();
            //     getline(sstr, tmp, '\"');
            //     strcpy(art.genres, tmp.c_str());
            // }
            // else if(sstr.peek() == '[')
            // {
            //     sstr.get();
            //     getline(sstr, tmp, ']');
            //     strcpy(art.genres, tmp.c_str());
            // }

            getline(sstr, tmp, ',');     

            while(!verificaCaractere(tmp)){
                aux += tmp + " ";
                getline(sstr, tmp, ',');  
            }
            aux += tmp;
            strcpy(art.genres, aux.c_str());
            aux = "";

            // o código abaixo o getline pega popularity
            // replace é uma função que substitui popularity por " "
            // while( getline(sstr, tmp, ',') )
            // { 
            //     aux += tmp + " ";
            // }
            // replace(aux);
            // strcpy(art.name, aux.c_str());
            // aux = "";


            string name = "";
            char c = sstr.peek();
            if(c == '\"')
            {
                c = sstr.get();

                while (sstr.get(c))
                {
                    if(c == ',' && isdigit(sstr.peek()))
                    {
                        break;
                    }
                    name += c;
                }
                
            }
            else
            {
                while (sstr.get(c))
                {
                    if(c == ',' && isdigit(sstr.peek()))
                    {
                        break;
                    }
                    name += c;
                }
            }
            strcpy(art.name, name.c_str());



            // if(sstr.peek() == '\"')
            // {
            //     sstr.get();
            //     getline(sstr, tmp, '\"');
            //     strcpy(art.name, tmp.c_str());
            // }
            // else
            // {
            //     sstr.get();
            //     getline(sstr, tmp, ',');
            //     strcpy(art.name, tmp.c_str());
            // }

  
            // if(tmp[0] == '"'){
            //     while (!verificaCaractere(tmp)){
            //         aux += tmp + " ";
            //         getline(sstr, tmp, ','); 
            //     }
            //     aux += tmp;
            //     strcpy(art.name, aux.c_str());
            //     aux = "";
            // }
            // else{  
            //     strcpy(art.name, tmp.c_str());
            // }



            getline(sstr, tmp, '\n');
            art.popularity = atoi(tmp.c_str());


            artista_Save(art,binArtOut);
        }
}



void geraVectorArtista(ifstream &binFile, int repeticoes,vector<Artista> &artistas, int tam, int &linhasArtistaCsv){
    int n;
    artistas.resize(repeticoes); 
    srand(time(NULL));
    cout << "\n\nPreenchendo vetor de artistas" << endl << endl;
    for(int i = 0; i < repeticoes; i++){
            n = rand()%linhasArtistaCsv;
            artista_Read(artistas[i], binFile, i, tam);
    }
}


void leTrackCsv(ifstream &csvTrackIn, ofstream &binTrackOut, Track &track, int &linhasTrackCsv){
    cout << "Lendo do arquivo tracks.csv" << endl;
    string line;
    string tmp;
    string aux = "";

    //csvTrackIn.ignore(1000, '\n'); //ignora linha até encontrar 1000 caracteres ou quebra de linha

    while(getline(csvTrackIn, line)){
        linhasTrackCsv++;
        stringstream sstr(line);

        getline(sstr,tmp,',');
        strcpy(track.id, tmp.c_str());

        //297193

        // getline(sstr,tmp,',');
        // strcpy(track.name, tmp.c_str());

        // getline(sstr, tmp, ',');     

        // while(!verificaCaractere(tmp)){
        //     aux += tmp + " ";
        //     getline(sstr, tmp, ',');  
        // }
        // aux += tmp;
        // strcpy(track.name, aux.c_str());
        // aux = "";

        char c = sstr.peek();


        string name = "";
        if(c == '\"')
        {
            c = sstr.get();

            while (sstr.get(c))
            {
                if(c == ',' && isdigit(sstr.peek()))
                {
                    break;
                }
                name += c;
            }
            
        }
        else
        {
            while (sstr.get(c))
            {
                if(c == ',' && isdigit(sstr.peek()))
                {
                    break;
                }
                name += c;
            }
        }

        strcpy(track.name, name.c_str());

        

        getline(sstr,tmp,',');
        track.popularity = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.duration = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.explicitt = atoi(tmp.c_str());


        tmp = "";
        c = sstr.peek();
        if(c == '\"')
        {
            c = sstr.get();

            
            if(sstr.peek() == '[')
            {
                c = sstr.get();

                while (sstr.get(c))
                {
                    if(c == ']' && sstr.peek() == '\"')
                    {
                        break;
                    }
                    tmp += c;
                }
                sstr.get();
                sstr.get();
            }  
        }
        else
        {
            if(sstr.peek() == '[')
            {
                c = sstr.get();

                while (sstr.get(c))
                {
                    if(c == ']' && sstr.peek() == ',')
                    {
                        break;
                    }
                    tmp += c;
                }
                sstr.get();
            }  
        }
        strcpy(track.artist, tmp.c_str());

        



        // getline(sstr,tmp,',');

        // while(!verificaCaractere(tmp)){
        //     aux += tmp + " ";
        //     getline(sstr,tmp,',');
        // }
        // aux += tmp;
        // strcpy(track.artist, aux.c_str());
        // aux = "";

        tmp = "";
        c = sstr.peek();
        if(c == '\"')
        {
            c = sstr.get();
            
            if(sstr.peek() == '[')
            {
                c = sstr.get();

                while (sstr.get(c))
                {
                    if(c == ']' && sstr.peek() == '\"')
                    {
                        break;
                    }
                    tmp += c;
                }
                sstr.get();
                sstr.get();
            }  
        }
        else
        {
            if(sstr.peek() == '[')
            {
                c = sstr.get();

                while (sstr.get(c))
                {
                    if(c == ']' && sstr.peek() == ',')
                    {
                        break;
                    }
                    tmp += c;
                }
                sstr.get();
            }  
        }
        strcpy(track.idArtist, tmp.c_str());

        //cout << "\nIDARTIST.NAME: " << track.idArtist << endl;



        getline(sstr,tmp,',');
        strcpy(track.releaseDate, tmp.c_str());

        getline(sstr,tmp,',');
        track.danceability = atof(tmp.c_str());

        getline(sstr,tmp,',');
        track.energy = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.key = atoi(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.loudness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.mode = atoi(tmp.c_str());

        getline(sstr,tmp,',');
        track.speechiness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.acousticness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.instrumentalness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.liveness = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.valence = atof(tmp.c_str());
    
        getline(sstr,tmp,',');
        track.tempo = atof(tmp.c_str());
    
        getline(sstr,tmp,'\n');
        track.timeSignature = atoi(tmp.c_str());

        
        track_Save(track,binTrackOut);
    }
}

void geraVectorTrack(ifstream &binFile, int repeticoes, vector<Track> &tracks, int tam, int &linhasTrackCsv){
    int n;
    tracks.resize(repeticoes); 
    srand(time(NULL));
    cout << "\n\nPreenchendo vetor de tracks" << endl << endl;
    for(int i = 0; i < repeticoes; i++){
            n = rand()%linhasTrackCsv;
            track_Read(tracks[i], binFile, i, tam);
    }
}

bool verificaCaractere(string word){
    return word[word.size()-1] == ']' || word[word.size()-1] == '"';
}

void imprime_Terminal(vector<Artista> &artistas, vector<Track> &tracks){
    // cout << "\nImprimindo dados dos artistas:" << endl;
    // imprime_ArtistaV(artistas);
    cout << "\nImprimindo dados de tracks:" << endl;
    imprime_TrackV(tracks);
}

void geraArquivoFinal(ofstream &arquivoFinal, string artistaCsvHeader, vector<Artista> artistas, string trackCsvHeader, vector<Track> tracks){
    arquivoFinal << artistaCsvHeader;
    for(int i = 0; i < artistas.size(); i++){
        arquivoFinal << artistas[i].id;
        arquivoFinal << ',';
        arquivoFinal << artistas[i].followers;
        arquivoFinal << ',';
        arquivoFinal << artistas[i].genres;
        arquivoFinal << ',';
        arquivoFinal << artistas[i].name;
        arquivoFinal << ',';
        arquivoFinal << artistas[i].popularity;
        arquivoFinal << '\n';
    }

    arquivoFinal << '\n';
    arquivoFinal << trackCsvHeader;
    arquivoFinal << '\n';

    for(int i = 0; i < tracks.size(); i++){
        arquivoFinal << tracks[i].id;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].name;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].popularity;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].duration;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].explicitt;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].artist;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].idArtist;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].releaseDate;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].danceability;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].energy;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].key;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].loudness;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].mode;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].speechiness;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].acousticness;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].instrumentalness;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].liveness;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].valence;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].tempo;
        arquivoFinal << ',';
        arquivoFinal << tracks[i].timeSignature;
        arquivoFinal << '\n';
    }
}
