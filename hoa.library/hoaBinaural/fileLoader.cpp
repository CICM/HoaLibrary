#include "fileLoader.hpp"

double* Read_Wav (char *wave_file) 
{  
	FILE *file;  
    file = fopen(wave_file, "rb");  

    if (file == NULL) 
	{  
        printf("nerreur: fichier  %s  introuvablen", wave_file);  
        return NULL;
    }  
 
	char ChunkID[4];    // contient les lettres "RIFF" pour indiquer que le fichier est codé selon la norme RIFF  
	unsigned long ChunkSize;        // taille du fichier entier en octets (sans compter les 8 octets de ce champ (4o) et le champ précédent CunkID (4o)  
	char Format[4];        // correspond au format du fichier donc ici, contient les lettres "WAVE" car fichier est au format wave  
	char Subchunk1ID[4];    // contient les lettres "fmt " pour indiquer les données à suivre décrivent le format des données audio  
	unsigned long Subchunk1Size;    // taille en octet des données à suivre (qui suivent cette variable) 16 Pour un fichier PCM  
	short AudioFormat;        // format de compression (une valeur autre que 1 indique une compression)  
	short NumChannels;        // nombre de canaux: Mono = 1, Stereo = 2, etc..  
	unsigned long SampleRate;        // fréquence d'échantillonage, ex 44100, 44800 (nombre d'échantillons par secondes)  
	unsigned long ByteRate;            // nombre d'octects par secondes  
	short Blockalign;        // nombre d'octects pour coder un échantillon  
	short BitsPerSample;    // nombre de bits pour coder un échantillon   
	char Subchunk2ID[4];    // contient les lettres "data" pour indiquer que les données à suivre sont les données audio (les échantillons et)  
	unsigned long Subchunk2Size;    // taille des données audio (nombre total d'octets codant les données audio)  
	short *data;            // données audio... les échantillons  
	
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
	double* datas = new double[(int)(Subchunk2Size + 1) / (int)Blockalign];

	
    for (int i=0; i < (int)Subchunk2Size/Blockalign; i++)
	{  

        fread(&data[i], Blockalign, 1, file);
		datas[i]  = (((double)data[i])/ pow(2. ,15));
    }  

    fclose(file);
    return datas;  
}  


