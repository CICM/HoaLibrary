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

#define CICM_PI  (3.141592653589793238462643383279502884)
#define CICM_2PI (6.283185307179586476925286766559005)
#define CICM_PI2 (1.57079632679489661923132169163975144)
#define CICM_PI4 (0.785398163397448309615660845819875721)
#define NUMBEROFCIRCLEPOINTS 36000
#define NUMBEROFCIRCLEPOINTS_UI 360

// check maxversion
#define MAXVERSION maxversion()
#define MAXVERSION_LESSTHAN_500 (MAXVERSION < 1280)
#define MAXVERSION_500 (MAXVERSION >= 1280 && MAXVERSION < 1536)
#define MAXVERSION_600 (MAXVERSION >= 1536 && MAXVERSION < 1552)
#define MAXVERSION_GREATHERTHAN_610 (MAXVERSION >= 1552)

enum
{
    Hoa_Polar  = 0,
    Hoa_Cartesian
};

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
    
    template<typename Type> static void clip(Type *aValue, Type aMinimum = 0, Type aMaximum = 1)
	{
		if(*aValue < aMinimum)
			*aValue = aMinimum;
		else if(*aValue > aMaximum)
			*aValue = aMaximum;
	}

	template<typename Type> static Type clip_min(Type aValue, Type aMinimum = 0)
	{
        return (aValue > aMinimum) ? aValue : aMinimum;
	}

	template<typename Type> static Type clip_max(Type aValue, Type aMaximum = 0)
	{
        return (aValue < aMaximum) ? aValue : aMaximum;
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
    
    static long double factoriel(long double n)
	{
        long double j = 1;
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
    
    static std::string floatToString(float aValue, int numberOfDecimals = 2)
    {
        char number[256];
        if ( (aValue - long(aValue) != 0.) || numberOfDecimals <= 0)
        {
            sprintf(number, "%ld", long(aValue));
            return number;
        }
        else
        {
            switch (numberOfDecimals)
            {
                case 1: {sprintf(number, "%.1f", aValue); break;}
                case 2: {sprintf(number, "%.2f", aValue); break;}
                case 3: {sprintf(number, "%.3f", aValue); break;}
                case 4: {sprintf(number, "%.4f", aValue); break;}
                case 5: {sprintf(number, "%.5f", aValue); break;}
                default: {sprintf(number, "%f", aValue); break;}
            }
            return number;
        }
    }
    
    static std::string floatToStringOneDecimal(float aValue)
    {
        char number[256];
        (aValue - long(aValue) != 0.) ? sprintf(number, "%.1f", aValue) : sprintf(number, "%ld", long(aValue));
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
    
    template<typename Type> static bool isInside(Type val, Type v1, Type v2)
	{
        return (v1 <= v2) ? (val >= v1 && val <= v2) : (val >= v2 && val <= v1);
	}
    
    static bool isInsideRad(double radian, double loRad, double hiRad)
	{
        return isInside(radianWrap(radian-loRad), double(0), radianWrap(hiRad-loRad));
	}
    
    static bool isInsideDeg(double degree, double loDeg, double hiDeg)
	{
        return isInside(degreeWrap(degree-loDeg), double(0), degreeWrap(hiDeg-loDeg));
	}
    
    template<typename Type> static Type max(Type v1, Type v2)
	{
        return (v2 >= v1) ? v2 : v1;
	}
    
    template<typename Type> static Type min(Type v1, Type v2)
	{
        return (v1 <= v2) ? v1 : v2;
	}
    
    static double radianInterp(double _step, double _startRad, double _endRad)
    {
        _startRad = radianWrap(_startRad);
        _endRad   = radianWrap(_endRad);
        
        if ( radianWrap(_endRad - _startRad) <= CICM_PI ) // anti-clockwise
        {
            if (_endRad - _startRad >= 0)
                return radianWrap( _startRad + _step*(_endRad - _startRad) );
            else
                return radianWrap( _startRad + _step*( (_endRad+CICM_2PI) - _startRad) );
        }
        else // clockwise
        {
            if (_endRad - _startRad <= 0)
                return radianWrap( _startRad + _step*(_endRad - _startRad) );
            else
                return radianWrap( _startRad - _step*( (_startRad+CICM_2PI) - _endRad) );
        }
    }
    
    static double radToDeg(double radian)
    {
        return radian * 360. / CICM_2PI;
    }
    
    static double degToRad(double degree)
    {
        return degree / 360. * CICM_2PI;
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
    
    template<typename Type> static void sortVector(Type* array, int size)
    {
        Type tmp;
        int i,j;
        for(i = 0;i < size ; i++)
        {
            for(j=0;j < size;j++)
            {
                if(array[i] < array[j])
                {
                    tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                }
            }
        }
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
    
    static double radianWrap(double anAngle)
    {
        while(anAngle < 0.)
            anAngle += CICM_2PI;
        while(anAngle > CICM_2PI)
            anAngle -= CICM_2PI;
        
        return anAngle;
    }
    
    static double radianDistance(double anAngle1, double anAngle2)
    {
        double distance;
        anAngle1 = radianWrap(anAngle1);
        anAngle2 = radianWrap(anAngle2);
        if(anAngle1 > anAngle2)
            distance = anAngle1 - anAngle2;
        else
            distance = anAngle2 - anAngle1;
        
        return distance;
    }

    static double radianClosestDistance(double anAngle1, double anAngle2)
    {
        double minRad, maxRad;
        anAngle1 = radianWrap(anAngle1);
        anAngle2 = radianWrap(anAngle2);
        minRad = min(anAngle1, anAngle2);
        maxRad = max(anAngle1, anAngle2);
        
        if (maxRad - minRad <= CICM_PI)
            return maxRad - minRad;
        else
            return CICM_2PI - (maxRad - minRad);
    }
    
    static double degreeWrap(double anAngle)
    {
        while(anAngle < 0.)
            anAngle += 360.;
        while(anAngle > 360.)
            anAngle -= 360.;
        
        return anAngle;
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