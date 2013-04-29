/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef DEF_CICM_TOOLS
#define DEF_CICM_TOOLS

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
using namespace std;
#include <string>

#define CICM_PI 3.141592653589793238462643383279502884
#define CICM_2PI CICM_PI * 2.
#define CICM_PI2 CICM_PI / 2.
#define NUMBEROFCIRCLEPOINTS 36000

//#define round(x) ((fabs(ceil(x) - (x)) < fabs(floor(x) - (x))) ? ceil(x) : floor(x))

class Tools
{
public:
	Tools();
	~Tools();
	template<typename Type> static Type clip(Type aValue, Type aMinimum = 0, Type aMaximum = 1)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		else if(aValue > aMaximum)
			aValue = aMaximum;
		return aValue;
	}

	template<typename Type> static Type clip_min(Type aValue, Type aMinimum = 0)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		return aValue;
	}

	template<typename Type> static Type clip_max(Type aValue, Type aMinimum = 0)
	{
		if(aValue < aMinimum)
			aValue = aMinimum;
		return aValue;
	}

	template<typename Type> static Type clip_power_of_two(Type aValue)
	{
		if(aValue < 2)
		aValue = 2;
		else if(aValue&(aValue-1) != 0)
		{
			while (aValue&(aValue-1) != 0) 
				aValue--;
		}
		return aValue;
	}

	template<typename Type> static Type log2(Type n)
	{
		return log((double)n) / log(2.);
	}

	template<typename Type> static Type radius(Type x, Type y)
	{
		return sqrt(x*x + y*y);
	}

	template<typename Type> static Type angle(Type x, Type y)
	{
		return atan2(y, x);
	}

	template<typename Type> static Type ordinate(Type radius, Type angle)
	{
		return radius * sin(angle);
	}

	template<typename Type> static Type abscisse(Type radius, Type angle)
	{
		return radius * cos(angle);
	}
	
	template<typename Type> static Type distance_euclidean(Type x1, Type y1, Type x2, Type y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
    
    template<typename Type> static Type factoriel(Type n)
	{
        Type j = 1;
        for(int i = 1; i <= n; i++)
        {
            j = i * j;
        }
        return j;
	}
    
    static std::string intToString(int aValue)
    {
        char number[256];
        sprintf(number, "%i", aValue);
        return number;
    }
    
    static double* Read_Wav(char *wave_file)
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
};

#endif