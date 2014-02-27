#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

static float* Read_Wav(char *wave_file, int* size)
{
    FILE *file;
    file = fopen(wave_file, "rb");
    
    if (file == NULL)
    {
        //printf("nerreur: fichier  %s  introuvablen", wave_file);
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
    char repertoire[] = "../MIT_HrtfDatabase/";
    char frequence[4][512];
    char elevation[14][512];
    char path[2048];
    char path_temp1[2048];
    char path_temp2[2048];
    char temp[2048];
    
    sprintf(frequence[0], "44100/");
    sprintf(frequence[1], "48000/");
    sprintf(frequence[2], "88200/");
    sprintf(frequence[3], "96000/");
    
    sprintf(elevation[0], "elev-40");
    sprintf(elevation[1], "elev-30/");
    sprintf(elevation[2], "elev-20/");
    sprintf(elevation[3], "elev-10/");
    sprintf(elevation[4], "elev0");
    sprintf(elevation[5], "elev10/");
    sprintf(elevation[6], "elev20/");
    sprintf(elevation[7], "elev30/");
    sprintf(elevation[8], "elev40");
    sprintf(elevation[9], "elev50/");
    sprintf(elevation[10], "elev60/");
    sprintf(elevation[11], "elev70/");
    sprintf(elevation[12], "elev80/");
    sprintf(elevation[13], "elev90/");
    
    ofstream fichier("hrtfmatrix.cpp", ios::out | ios::trunc);
    if(fichier)
    {
        for(int i = 0; i < 1; i++)
        {
            sprintf(path_temp1, "%s%s",repertoire, frequence[i]);
            int inc = -40;
            for(int j = 0; j < 14; j ++)
            {
                sprintf(path_temp2, "%s",path_temp1);
                strcat(path_temp2, elevation[j]);
                
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
                        fichier << "\n";
                        fichier << "static const float  zaza[] = {";
                        for(int l = 0; l < size - l; l++)
                        {
                            if(l % 10 == 0)
                            {
                                fichier << "\n";
                            }
                            fichier << wavfile[l] << ",";
                        }
                        fichier << wavfile[size - 1] << "};";
                        free(wavfile);
                        wavfile = NULL;
                    }
                    else
                        wavfile = NULL;
                }
                inc += 10;
            }
        }
        
        
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    
    return 0;
}