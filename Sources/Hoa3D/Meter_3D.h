/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_METER__
#define __DEF_HOA_3D_METER__

#include "Planewaves_3D.h"
#include "Clarkson-Delaunay.h"

namespace Hoa3D
{
    //! The planewaves peak level meter.
    /** The meter should be used to widen the sound propagation.
     */
    class Meter : public Planewaves
    {
    private:
		class Delaunay
		{
		private :
			triangulateio	m_in;
			triangulateio	m_delaunay;
			triangulateio	m_voronoy;
		public :
			Delaunay(unsigned int numberOfPoints)
			{
				assert(numberOfPoints > 0);
				m_in.numberofpoints				= numberOfPoints;
				m_in.numberofpointattributes	= 1;
				m_in.numberofsegments			= 0;
				m_in.numberofholes				= 0;
				m_in.numberofregions			= 1;

				m_in.pointlist			= (REAL *)malloc(m_in.numberofpoints * 2 * sizeof(REAL));
				m_in.pointmarkerlist	= (int *)malloc(m_in.numberofpoints * sizeof(int));
				m_in.pointattributelist = (REAL *)malloc(m_in.numberofpoints * sizeof(REAL));
				m_in.regionlist			= (REAL *)NULL;

				for(int i = 0, j = 0; i < m_in.numberofpoints; i++, j += 2)
				{
					m_in.pointlist[j] = 0.;
					m_in.pointlist[j+1] = 0.;
					m_in.pointmarkerlist[i] = i;
					m_in.pointattributelist[i] = 0;
				}

				m_delaunay.pointlist			= (REAL *)NULL;
				clear();
			};

			~Delaunay()
			{
				free(m_in.pointlist);
				free(m_in.pointattributelist);
				free(m_in.pointmarkerlist);
				//free(m_in.regionlist);
				clear();
			}

			void clear()
			{
				if(m_delaunay.pointlist)
				{
					free(m_delaunay.pointlist);
					free(m_delaunay.pointattributelist);
					free(m_delaunay.pointmarkerlist);
					free(m_delaunay.trianglelist);
					free(m_delaunay.triangleattributelist);
					free(m_delaunay.trianglearealist);
					free(m_delaunay.neighborlist);
					free(m_delaunay.segmentlist);
					free(m_delaunay.segmentmarkerlist);
					free(m_delaunay.edgelist);
					free(m_delaunay.edgemarkerlist);
					free(m_voronoy.pointlist);
					free(m_voronoy.pointattributelist);
					free(m_voronoy.edgelist);
					free(m_voronoy.normlist);
				}
				m_delaunay.pointlist			= (REAL *)NULL;
				m_delaunay.pointattributelist	= (REAL *)NULL;
				m_delaunay.pointmarkerlist		= (int *)NULL;
				m_delaunay.trianglelist			= (int *)NULL;
				m_delaunay.triangleattributelist= (REAL *)NULL;
				m_delaunay.neighborlist			= (int *)NULL;
				m_delaunay.segmentlist			= (int *)NULL;
				m_delaunay.segmentmarkerlist	= (int *)NULL;
				m_delaunay.edgelist				= (int *)NULL;
				m_delaunay.edgemarkerlist		= (int *)NULL;

				m_voronoy.pointlist				= (REAL *)NULL;
				m_voronoy.pointattributelist	= (REAL *)NULL;
				m_voronoy.edgelist				= (int *)NULL;
				m_voronoy.normlist				= (REAL *)NULL; 
			}

			void setPointPosition(unsigned int _index, double _azimuth, double _elevation, bool _bottom = 0)
			{
				assert(_index > m_in.numberofpoints);
				double abs = abscissa(1., _azimuth, _elevation);
				double ord = ordinate(1., _azimuth, _elevation);
				if((_bottom && _elevation > 0) || (!_bottom && _elevation < 0))
				{
					double rad = (1. - radius(abs, ord)) + 1.;
					double azy = azimuth(abs, ord);
					abs = abscissa(rad, azy);
					ord = ordinate(rad, azy);
					m_in.pointattributelist[_index] = 1;
				}
				m_in.pointlist[_index * 2] = abs;
				m_in.pointlist[_index * 2 + 1] = ord;
			};

			void perform()
			{
				clear();
				triangulate("pczevn", &m_in, &m_delaunay, &m_voronoy);
			};
		};
        unsigned int    m_ramp;
        unsigned int    m_vector_size;
        double*         m_channels_peaks;
		Delaunay*		m_delaunay;
    public:
        
        //! The meter constructor.
        /**	The meter constructor allocates and initialize the member values to computes spherical harmonics weighted coefficients depending of a decomposition order. The order must be at least 1.
         
            @param     order	The order.
         */
        Meter(unsigned int numberOfChannels);
        
        //! The meter destructor.
        /**	The meter destructor free the memory.
         */
        ~Meter();
        
        void setVectorSize(unsigned int vectorSize);
        
        //! Set the position of a channel.
        /** Set the position of a channel with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
         @param     index		The index of the channel.
         @param     azimuth		The azimuth.
         @param     elevation	The elevation.
         */
		void setChannelPosition(unsigned int index, double azimuth, double elevation);
        
		//! Set the position of the channels.
        /** Set the position of the channels with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param     azimuths		The azimuths.
            @param     elevations	The elevations.
         */
		void setChannelsPosition(double* azimuths, double* elevations);

		inline unsigned int getChannelNumberOfPoints(unsigned int index, bool top = 1) const
        {
            assert(index < m_number_of_channels);
			return 0;
        }

		inline double getChannelPointAzimuth(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return 0;
        }

		inline double getChannelPointElevation(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return 0;
        }

        inline double getChannelPeak(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_channels_peaks[index];
        }
        
        inline double getChannelEnergy(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return 20. * log10(m_channels_peaks[index]);
        }
       
        //! This method performs the widening with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The inputs array.
         */
        void process(const float* inputs);
        
        //! This method performs the widening with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The inputs array.
         */
        void process(const double* inputs);
    };
}

#endif



