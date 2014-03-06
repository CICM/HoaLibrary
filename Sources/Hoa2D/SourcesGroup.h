/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef DEF_AMBISONICSOURCESGROUP
#define DEF_AMBISONICSOURCESGROUP

/*
class SourcesGroup
{
	
private:
    std::vector <Source*>   m_sources;
    std::string             m_description;
    long                    m_exist;
    color                   m_color;
    coordinatesCartesian    m_centroid;
    
    void computeCentroid();
    void shiftPolar(coordinatesPolar polarCoordinates);
	void shiftPolar(double aRadius, double anAngle);
    void shiftRadius(double aRadius);
    void shiftAngle(double anAngle);
    void shiftCartesian(coordinatesCartesian cartesianCoordinates);
    void shiftCartesian(double anAbscissa, double anOrdinate);
    void shiftAbscissa(double anAbscissa);
    void shiftOrdinate(double anOrdinate);
public:
	SourcesGroup(long deadOrAlive, std::string aDescription = "");
    
    void setExistence(long deadOrAlive);
    void setDescription(std::string aDescription);
    void setColor(color aColor);
    void addSource(Source* aSource);
    void sourceHasMoved(Source* aSource);
    void removeSource(Source* aSource);
    
    void setCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setCoordinatesPolar(double aRadius, double anAngle);
	void setRadius(double aRadius);
    void setAngle(double anAngle);
    void setCoordinatesCartesian(coordinatesCartesian cartesianCoordinates);
    void setCoordinatesCartesian(double anAbscissa, double anOrdinate);
	void setAbscissa(double anAbscissa);
	void setOrdinate(double anOrdinate);
    
    void setRelativeCoordinatesPolar(coordinatesPolar polarCoordinates);
	void setRelativeCoordinatesPolar(double aRadius, double anAngle);
	void setRelativeRadius(double aRadius);
    void setRelativeAngle(double anAngle);

    long   getExistence();
    coordinatesPolar        getCoordinatesPolar();
	double getRadius();
	double getAngle();
    coordinatesCartesian    getCoordinatesCartesian();
	double getAbscissa();
	double getOrdinate();
    long getNumberOfSources();
    std::string getDescription();
    color  getColor();
    
	~SourcesGroup();
};
*/
#endif
