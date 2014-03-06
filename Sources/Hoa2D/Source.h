/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_AMBISONICSOURCE
#define DEF_AMBISONICSOURCE

/*
class Source
{
private:
	coordinatesPolar        m_coordinate_polar;
	color                   m_color;
    std::string             m_description;
    long                    m_exist;
    std::vector <long>      m_groups;
    
public:
    Source(long deadOrAlive, double aRadius = 0., double anAngle = 0.);
    Source(long deadOrAlive, coordinatesPolar polarCoordinates);
    Source(long deadOrAlive, coordinatesCartesian cartesianCoordinates);
    
    void setExistence(long deadOrAlive);
    void setCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setCoordinatesPolar(double aRadius, double anAngle);
	void setRadius(double aRadius);
    void setAngle(double anAngle);
    void setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
	void setAbscissa(double anAbscissa);
	void setOrdinate(double anOrdinate);
    void setColor(color aColor);
	void setDescription(std::string aDescription);
    void setGroup(long aGroupIndex);
	void removeGroup(long aGroupIndex);
    
    long   getExistence();
    coordinatesPolar        getCoordinatesPolar();
	double getRadius();
	double getAngle();
    coordinatesCartesian    getCoordinatesCartesian();
	double getAbscissa();
	double getOrdinate();
    color  getColor();
    std::string getDescription();
    long   getNumberOfGroups();
    long   getGroupIndex(long anIndex);
	
	~Source();
};
*/
#endif