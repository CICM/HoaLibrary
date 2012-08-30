#include "fileLoader.h"



double* Read_Wav (char *wave_file, double* datas) 
{  

    FILE *file;  
	WAVE sonValue;
	WAVE* son = &sonValue;
 
    file = fopen(wave_file, "rb");  
	
    if (file == NULL) 
	{  
        printf("nerreur: fichier  %s  introuvablen", wave_file);  
        exit(0);  
    }  

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


