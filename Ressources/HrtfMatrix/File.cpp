#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

static char header[] = {"\n/*\n// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.\n// For information on usage and redistribution, and for a DISCLAIMER OF ALL\n// WARRANTIES, see the file, \"LICENSE.txt,\" in this distribution.\n*/\n"};

static char large_sep[] = {"\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////\n"};

static char small_sep[] = {"\n///////////////////////////////////////////////////////\n///////////////////////////////////////////////////////\n///////////////////////////////////////////////////////\n///////////////////////////////////////////////////////\n"};

static int frequence[] = {44100, 48000, 88200, 96000};

static int elevation[] = {-40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

static float* Read_Wav(char *wave_file, int* size)
{
    FILE *file;
    file = fopen(wave_file, "rb");
    
    if (file == NULL)
    {
        printf("nerreur: fichier  %s  introuvablen", wave_file);
        return NULL;
    }
    
    char ChunkID[4];                // contient les lettres "RIFF" pour indiquer que le fichier est codé selon la norme RIFF
    unsigned long ChunkSize;        // taille du fichier entier en octets (sans compter les 8 octets de ce champ (4o) et le champ précédent CunkID (4o)
    char Format[4];                 // correspond au format du fichier donc ici, contient les lettres "WAVE" car fichier est au format wave
    char Subchunk1ID[4];            // contient les lettres "fmt " pour indiquer les données à suivre décrivent le format des données audio
    unsigned long Subchunk1Size;    // taille en octet des données à suivre (qui suivent cette variable) 16 Pour un fichier PCM
    short AudioFormat;              // format de compression (une valeur autre que 1 indique une compression)
    short NumChannels;              // nombre de canaux: Mono = 1, Stereo = 2, etc..
    unsigned long SampleRate;       // fréquence d'échantillonage, ex 44100, 44800 (nombre d'échantillons par secondes)
    unsigned long ByteRate;         // nombre d'octects par secondes
    short Blockalign;               // nombre d'octects pour coder un échantillon
    short BitsPerSample;            // nombre de bits pour coder un échantillon
    char Subchunk2ID[4];            // contient les lettres "data" pour indiquer que les données à suivre sont les données audio (les échantillons et)
    unsigned long Subchunk2Size;    // taille des données audio (nombre total d'octets codant les données audio)
    short *data;                    // données audio... les échantillons
    
    fread(&ChunkID, 4, 1, file);
    fread(&ChunkSize, 4, 1, file);
    fread(&Format, 4, 1, file);
    fread(&Subchunk1ID, 4, 1, file);
    fread(&Subchunk1Size, 4, 1, file);
    fread(&AudioFormat, 2, 1, file);
    fread(&NumChannels, 2, 1, file);
    fread(&SampleRate, 4, 1, file);
    fread(&ByteRate, 4, 1, file);
    fread(&Blockalign, 2, 1, file);
    fread(&BitsPerSample, 2, 1, file);
    fread(&Subchunk2ID, 4, 1, file);
    fread(&Subchunk2Size, 4, 1, file);
    
    data = new short[(int)(Subchunk2Size + 1) / Blockalign];
    float* datas = new float[(int)(Subchunk2Size + 1) / (int)Blockalign];
    
    for (int i=0; i < (int)Subchunk2Size/Blockalign; i++)
    {
        
        fread(&data[i], Blockalign, 1, file);
        datas[i]  = (((float)data[i])/ pow(2. ,15));
    }
    *size = (int)Subchunk2Size/Blockalign;
    fclose(file);
    return datas;
}

int main()
{
    float* wavfile = NULL;
    int size;
    char path[2048];
    char path_temp1[2048];
    char path_temp2[2048];
    char temp[2048];
    int counter = 0;
    int countersample = 0;
    ofstream fichier("hrtfmatrix.cpp", ios::out | ios::trunc);
    if(fichier)
    {
        fichier << header << "\nnamespace Hoa3D\n{";
        
        for(int i = 0; i < 1; i++)
        {
            sprintf(path_temp1, "../MIT_HrtfDatabase/%i/elev0/L0e000a.wav", frequence[i]);
            wavfile = Read_Wav(path_temp1, &size);
            if(wavfile)
                free(wavfile);
            
            fichier << "\n" << large_sep << "// HRTF ARRAY " << frequence[i] << " SIZE " << size << large_sep << "\n";
            fichier << "static const float  MIT_HRTF_" << frequence[i] << "_2D[]"<< " = {\n";
            sprintf(path_temp1, "../MIT_HrtfDatabase/%i/", frequence[i]);
            
            sprintf(path_temp2, "%s",path_temp1);
            strcat(path_temp2, "elev0/");
            
            fichier << small_sep << "// HRTF ARRAY " << frequence[i] << " ELEVATION " << 0 << small_sep;
            
            for(int k = 0; k < 360; k += 5)
            {
                sprintf(path, "%s/",path_temp2);
                if(k < 10)
                    sprintf(temp, "L0e00%ia.wav", (int)k);
                else if(k < 100)
                    sprintf(temp, "L0e0%ia.wav", (int)k);
                else
                    sprintf(temp, "L0e%ia.wav", (int)k);
                
                strcat(path, temp);
                wavfile = Read_Wav(path, &size);
                if(wavfile && size == 512)
                {
                    for(int l = 0; l < size -1; l++)
                    {
                        if(l % 10 == 0)
                            fichier << "\n";
                        fichier << wavfile[l] << ",";
                        countersample++;
                    }
                    fichier << wavfile[size - 1] << ",";
                    countersample++;
                    counter++;
                    free(wavfile);
                    wavfile = NULL;
                }
                else
                {
                    wavfile = NULL;
                    fichier << "\n" << large_sep;
                }
            }
            fichier << "\n";
            
            fichier << "0";
            fichier << "};";
        }
        fichier << "\n\n}\n\n";
        //fichier << counter;
        //fichier << countersample;
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    return 0;
}

/*
int main()
{
    float* wavfile = NULL;
    int size;
    char path[2048];
    char path_temp1[2048];
    char path_temp2[2048];
    char temp[2048];
    
    ofstream fichier("hrtfmatrix.cpp", ios::out | ios::trunc);
    if(fichier)
    {
        fichier << header << "\nnamespace Hoa3D\n{";
        
        for(int i = 0; i < 4; i++)
        {
            sprintf(path_temp1, "../MIT_HrtfDatabase/%i/elev0/L0e000a.wav", frequence[i]);
            wavfile = Read_Wav(path_temp1, &size);
            if(wavfile)
                free(wavfile);
            
            fichier << "\n" << large_sep << "// HRTF ARRAY " << frequence[i] << " SIZE " << size << large_sep << "\n";
            fichier << "static const float  MIT_HRTF_" << frequence[i] << "[]"<< " = {\n";
            sprintf(path_temp1, "../MIT_HrtfDatabase/%i/", frequence[i]);
            int inc = -40;
            for(int j = 0; j < 14; j ++)
            {
                sprintf(path_temp2, "%s",path_temp1);
                sprintf(temp, "elev%i/", elevation[j]);
                strcat(path_temp2, temp);
                
                fichier << small_sep << "// HRTF ARRAY " << frequence[i] << " ELEVATION " << elevation[j] << small_sep;
                
                for(int k = 0; k < 360; k++)
                {
                    sprintf(path, "%s/",path_temp2);
                    if(k < 10)
                        sprintf(temp, "L%ie00%ia.wav", inc, (int)k);
                    else if(k < 100)
                        sprintf(temp, "L%ie0%ia.wav", inc, (int)k);
                    else
                        sprintf(temp, "L%ie%ia.wav", inc, (int)k);
                    
                    strcat(path, temp);
                    wavfile = Read_Wav(path, &size);
                    if(wavfile)
                    {
                        for(int l = 0; l < size - l; l++)
                        {
                            if(l % 10 == 0)
                                fichier << "\n";
                            fichier << wavfile[l] << ",";
                        }
                        fichier << wavfile[size - 1] << ",";
                        free(wavfile);
                        wavfile = NULL;
                    }
                    else
                        wavfile = NULL;
                }
                inc += 10;
                fichier << "\n";
            }
            fichier << "0";
            fichier << "};";
        }
        fichier << "\n\n}\n\n";
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    return 0;
}*/


