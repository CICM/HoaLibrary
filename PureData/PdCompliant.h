//
//  PdCompliant.h
//  hoa.recomposer_UI
//
//  Created by Manuel Deneu on 31/07/13.
//
//

#ifndef hoa_recomposer_UI_PdCompliant_h
#define hoa_recomposer_UI_PdCompliant_h


#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>


static const long hextable[] =
{
    [0 ... 255] = -1, // bit aligned access into this table is considerably
    ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, // faster for most modern processors,
    ['A'] = 10, 11, 12, 13, 14, 15,       // for the space conscious, reduce to
    ['a'] = 10, 11, 12, 13, 14, 15        // signed char.
};


/* ***** ***** ***** ***** ***** ***** ***** ***** */
// Max types

// t_pt
typedef struct
{
    int x;
    int y;
} t_pt;


// t_rect
typedef struct
{
    int x;
    int y;
    int w;
    int h;
} t_rect;

// t_jrgb values = 0..1
typedef struct
{
    float red;
    float green;
    float blue;
    
} t_jrgb;

// t_jrgb values = 0..1
typedef struct
{
    float red;
    float green;
    float blue;
    float alpha; /* useless */
    
} t_jrgba;


/* ***** ***** ***** ***** ***** ***** ***** ***** */
// Creation des couleurs


t_jrgba RGBAColor255(int r, int g, int b, int a)
{
    t_jrgba C={ (float)r/255,
                (float)g/255,
                (float)b/255,
                (float)a/255};
    return C;
}

t_jrgba RGBAColor1(float r, float g, float b, float a)
{
    t_jrgba C={ r,
                g,
                b,
                a};
    return C;
}


/* ***** ***** ***** ***** ***** ***** ***** ***** */
// Conversion des couleurs vers TK
long hexdec(const char *hex)
{
    long ret = 0;
    while (*hex && ret >= 0) {
        ret = (ret << 4) | hextable[*hex++];
    }
    return ret;
}

int getTkColorFromRGB(t_jrgb val)
{
    int R=(int) floor(val.red*255);
    int G=(int) floor( val.green*255);
    int B=(int) floor(val.blue*255 );
    
    std::ostringstream oss;
    oss << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << R
        << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << G 
        << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << B ;
    std::string str=oss.str();
    
    
    return (int) hexdec(str.c_str());
}

int getTkColorFromRGB(t_jrgba val)
{
    t_jrgb _val = {val.red,
                   val.green,
                   val.blue
                   };
    return getTkColorFromRGB(_val);
}

int getTkColorFromRGB(int R, int G, int B)
{
    
    std::ostringstream oss;
    oss << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << R
    << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << G
    << std::setbase(16) << std::setiosflags(std::ios_base::uppercase) << std::setw(2) << std::setfill('0') << B ;
    std::string str=oss.str();

    
    return (int) hexdec(str.c_str());
    
}



#endif
