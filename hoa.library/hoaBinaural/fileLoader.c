#include "fileLoader.h"



double* Read_Wav (char *wave_file, double* datas) 
{  

    FILE *file;  
	WAVE sonValue;
	WAVE* son = &sonValue;
 
    file = fopen(wave_file, "rb");  
	
    if (file == NULL) 
	{  
        post("nerreur: fichier  %s  introuvablen", wave_file);  
        exit(0);  
    }
	else {
		post("loading %s ", wave_file);
	}
//	char ChunkID[4];				// contient les lettres "RIFF" pour indiquer que le fichier est codé selon la norme RIFF  
//	unsigned long ChunkSize;        // taille du fichier entier en octets (sans compter les 8 octets de ce champ (4o) et le champ précédent CunkID (4o)  
//	char Format[4];					// correspond au format du fichier donc ici, contient les lettres "WAVE" car fichier est au format wave  
//	char Subchunk1ID[4];			// contient les lettres "fmt " pour indiquer les données à suivre décrivent le format des données audio  
//	unsigned long Subchunk1Size;    // taille en octet des données à suivre (qui suivent cette variable) 16 Pour un fichier PCM  
//	short AudioFormat;				// format de compression (une valeur autre que 1 indique une compression)  
//	short NumChannels;				// nombre de canaux: Mono = 1, Stereo = 2, etc..  
//	unsigned long SampleRate;       // fréquence d'échantillonage, ex 44100, 44800 (nombre d'échantillons par secondes)  
//	unsigned long ByteRate;         // nombre d'octects par secondes  
//	short Blockalign;				// nombre d'octects pour coder un échantillon  
//	short BitsPerSample;			// nombre de bits pour coder un échantillon  
//	char Subchunk2ID[4];			// contient les lettres "data" pour indiquer que les données à suivre sont les données audio (les échantillons et)  
//	unsigned long Subchunk2Size;    // taille des données audio (nombre total d'octets codant les données audio)  
//	short *data;  

    fread(&son->RIFF.ChunkID, 4, 1, file);  
    fread(&son->RIFF.ChunkSize, 4, 1, file);  
    fread(&son->RIFF.Format, 4, 1, file);  
    fread(&son->fmt.Subchunk1ID, 4, 1, file);  
    fread(&son->fmt.Subchunk1Size, 4, 1, file);  
    fread(&son->fmt.AudioFormat, 2, 1, file);  
    fread(&son->fmt.NumChannels, 2, 1, file);  
    fread(&son->fmt.SampleRate, 4, 1, file);  
    fread(&son->fmt.ByteRate, 4, 1, file);  
    fread(&son->fmt.Blockalign, 2, 1, file);  
    fread(&son->fmt.BitsPerSample, 2, 1, file);  
    fread(&son->data.Subchunk2ID, 4, 1, file);  
    fread(&son->data.Subchunk2Size, 4, 1, file);  
	
	son->data.data = new short[(int)(son->data.Subchunk2Size + 1) / (int)son->fmt.Blockalign];
	datas = new double[(int)(son->data.Subchunk2Size + 1) / (int)son->fmt.Blockalign];

	
    for (int i=0; i < (int)son->data.Subchunk2Size/son->fmt.Blockalign; i++)
	{  
        fread(&son->data.data[i], son->fmt.Blockalign, 1, file);
		datas[i]  = (((double)son->data.data[i])/ pow(2,15));
    }  

    fclose(file);  
    return datas;  
}  


