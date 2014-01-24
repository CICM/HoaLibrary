

#ifndef DEF_AMBISONICWIDER
#define DEF_AMBISONICWIDER

#include "../HoaAmbisonics/Ambisonic.h"

//!  An ambisonic wider.
/*! The wider class can be used to wide the diffusion of a localised sound. The order depending signals are weighted and appear in a logarithmic way to have linear changes. The class processing functions :
 */
//! sample by sample - in place.
//! sample by sample - in place - widening value setter.
//! sample by sample - not in place.
//! sample by sample - not in place - widening value setter.
//! samples block - in place.
//! samples block - in place - widening value setter.
//! samples block - not in place.
//! samples block - not in place - widening value setter.

class AmbisonicWider : public Ambisonic
{
private:
    cicm_vector_double*	m_wider_matrix;

	cicm_vector_float	m_harmonics_vector_float;
    cicm_vector_double	m_harmonics_vector_double;
    
    int*				m_index_vector;
	cicm_vector_float	m_vector_float;
    cicm_vector_double	m_vector_double;
    
	void computeWidenVector();
public:
    //! The wider constructor.
    /*!
     \param anOrder The ambisonic decomposition order.
     \param aVectorSize The size of the samples block.
     */
	AmbisonicWider(long anOrder = 1, long aVectorSize = 2);
    
    //! Set the widening value.
    /*!
     \param aWideningValue The widening value (between 0 and 1).
     */
	void setWidenValue(double aWideningValue);
    
    //! Set the size of the samples block.
    /*!
     \param aVectorSize The size of the samples block (must be a power of 2).
     */
	void setVectorSize(long aVectorSize);
    
    //! Retreive the name of an input.
    /*!
     \param anIndex The input index.
     */
    std::string  getInputName(long anIndex);
    
    //! Retreive the name of an output.
    /*!
     \param anIndex The outpout index.
     */
    std::string  getOutputName(long anIndex);
    
    //! The wider destructor.
	~AmbisonicWider();

//! @cond
	/************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
	inline void process(const double* inputs, double* outputs)
	{
		cicm_product_vec_vec_d(inputs, m_harmonics_vector_double, outputs, m_number_of_harmonics);
	}
    
    inline void process(float* inputs, float* outputs)
	{
		cicm_product_vec_vec_f(inputs, m_harmonics_vector_float, outputs, m_number_of_harmonics);
	}
    
	inline void process(double* inputs, double* outputs, const double aWideningValue)
	{
        double widenValue = Tools::clip(aWideningValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(inputs, outputs);
	}
    
    inline void process(float* inputs, float* outputs, const float aWideningValue)
	{
        float widenValue = Tools::clip(aWideningValue, 0., 1.);
		for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
		process(inputs, outputs);
	}
    
    /************************************* In Place *************************************/
    
    inline void process(double* ioVector)
	{
        cicm_product_vec_d(m_harmonics_vector_double, ioVector, m_number_of_harmonics);
	}
    
    inline void process(float* ioVector)
	{
        cicm_product_vec_f(m_harmonics_vector_float, ioVector, m_number_of_harmonics);
	}
    
    inline void process(double* ioVector, double aWideningValue)
	{
        double widenValue = Tools::clip(aWideningValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
           m_harmonics_vector_double[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(ioVector);
	}

	inline void process(float* ioVector, float aWideningValue)
	{
        float widenValue = Tools::clip(aWideningValue, 0., 1.);
        for(int i = 0; i < m_number_of_harmonics; i++)
            m_harmonics_vector_float[i] = m_wider_matrix[i][(int)(widenValue*(double)(NUMBEROFLINEARPOINTS-1))];
        process(ioVector);
	}

    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(const double* const* inputs, double** outputs)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(inputs[i], m_harmonics_vector_double[i], outputs[i], m_vector_size);
	}
    
    inline void process(const float* const* inputs, float** outputs)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(inputs[i], m_harmonics_vector_float[i], outputs[i], m_vector_size);
	}

	inline void process(const double* const* inputs, double** outputs, const double* wideningValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(wideningValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			cicm_product_vec_vec_d(inputs[i], m_vector_double, outputs[i], m_vector_size);
		}
	}
    
    inline void process(const float* const* inputs, float** outputs, const float* wideningValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(wideningValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			cicm_product_vec_vec_f(inputs[i], m_vector_float, outputs[i], m_vector_size);
		}
	}
    
    /************************************* In Place *************************************/
   
    inline void process(double** ioVectors)
	{
		for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_d(ioVectors[i], m_harmonics_vector_double[i], ioVectors[i], m_vector_size);
	}
   
    inline void process(float** ioVectors)
	{
        for(int i = 0; i < m_number_of_harmonics; i++)
			cicm_product_vec_sca_vec_f(ioVectors[i], m_harmonics_vector_float[i], ioVectors[i], m_vector_size);
	}
  
	inline void process(double** ioVectors, const double* wideningValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(wideningValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_double[j] = pointor[index];
			}
			cicm_product_vec_d(m_vector_double, ioVectors[i], m_vector_size);
		}
	}
    
    inline void process(float** ioVectors, const float* wideningValues)
	{
		int index;
		cicm_vector_double pointor;
		for(int i = 0; i < m_vector_size; i++)
			m_index_vector[i] = Tools::clip(wideningValues[i], 0., 1.) * (double)(NUMBEROFLINEARPOINTS-1);
		for(int i = 0; i < m_number_of_harmonics; i++)
		{
			pointor = m_wider_matrix[i];
			for(int j = 0; j < m_vector_size; j++)
			{
				index = m_index_vector[j];
				m_vector_float[j] = pointor[index];
			}
			cicm_product_vec_f(m_vector_float, ioVectors[i], m_vector_size);
		}
	}
    //! @endcond
};





#endif


