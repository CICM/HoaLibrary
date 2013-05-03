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

#define CICM_PI (3.141592653589793238462643383279502884)
#define CICM_2PI (6.283185307179586476925286766559005)
#define CICM_PI2 (1.57079632679489661923132169163975144)
#define CICM_PI4 (0.785398163397448309615660845819875721)
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
        double* datas = new double[(int)(Subchunk2Size + 1) / (int)Blockalign];
        
        for (int i=0; i < (int)Subchunk2Size/Blockalign; i++)
        {  
            
            fread(&data[i], Blockalign, 1, file);
            datas[i]  = (((double)data[i])/ pow(2. ,15));
        }  
        
        fclose(file);
        return datas;  
    }
    
    template<typename Type> static bool isInside(Type val, Type lo, Type hi)
	{
		return (val >= lo && val <= hi);
	}
    
    static double radToDeg(double radian)
    {
        return radian * (180 / CICM_PI);
    }
    
    static double degToRad(double degree)
    {
        return degree / (180 / CICM_PI);
    }
    
    static long mstosamps(double ms, double samplerate=44100.)
    {
        return samplerate * ms * 0.001;
    }
    
    static double sampstoms(double s, double samplerate=44100.)
    {
        return 1000. * s / samplerate;
    }
    
    static double atodb(double amp)
    {
        return (amp <=0.) ? -999. : (20. * log10(amp));
    }
    
    static double dbtoa(double dB)
    {
        return pow(10., dB * 0.05);
    }
    
    static double safediv(double num, double denom)
    {
        return denom == 0. ? 0. : num/denom;
    }
    
    static double scale(double in, double inlow, double inhigh, double outlow, double outhigh, double power)
    {
        double value;
        double inscale = safediv(1., inhigh - inlow);
        double outdiff = outhigh - outlow;
        
        value = (in - inlow) * inscale;
        if (value > 0.0)
            value = pow(value, power);
        else if (value < 0.0)
            value = -pow(-value, power);
        value = (value * outdiff) + outlow;
        
        return value;
    }
    
    static double scale(double in, double inlow, double inhigh, double outlow, double outhigh)
    {
        return ( (in - inlow) * safediv(1., inhigh - inlow) * (outhigh - outlow) ) + outlow;
    }
    
    static double phasewrap(double val) {
        const double twopi = CICM_PI*2.;
        const double oneovertwopi = 1./twopi;
        if (val>= twopi || val <= twopi) {
            double d = val * oneovertwopi;	//multiply faster
            d = d - (long)d;
            val = d * twopi;
        }
        if (val > CICM_PI) val -= twopi;
        if (val < -CICM_PI) val += twopi;
        return val;
    }
    
    static double wrap(double _val, double _lo, double _hi){
        double lo;
        double hi;
        if(_lo == _hi) return _lo;
        if (_lo > _hi) {
            hi = _lo; lo = _hi;
        } else {
            lo = _lo; hi = _hi;
        }
        const double range = hi - lo;
        if (_val >= lo && _val < hi) return _val;
        if (range <= 0.000000001) return lo;	// no point...
        const long numWraps = long((_val-lo)/range) - (_val < lo);
        return _val - range * double(numWraps);
    }
};

#endif