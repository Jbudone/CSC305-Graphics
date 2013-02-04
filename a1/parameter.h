#ifndef PARAMETER_H
#define PARAMETER_H

#include "vector.h"
#include "matrix.h"
#include <stdint.h>
#include <string>
#include <vector>

/**
 *	@class	AbstractParameter
 *	@brief	class representing a gpu shader parameter
 */
class AbstractParameter
{
public:

    /**
     *	@brief	enum for parameter types
     */
    typedef enum
    {
        TEXTURE_1D,		/**< one dimensional texture. */
        TEXTURE_2D,		/**< two dimensional texture. */
        TEXTURE_3D,		/**< three dimensional texture. */
        FLOAT,			/**< a floating point value. */
        VEC_2D,			/**< a two dimensional floating point vector. */
        VEC_3D,			/**< a three dimensional floating point vector. */
        VEC_4D,			/**< a four dimensional floating point vector. */
        MAT_2D,			/**< a two by two floating point matrix. */
        MAT_3D,			/**< a three by three floating point matrix. */
        MAT_4D			/**< a four by four floating point matrix. */
    } type;


    /**
     *	default constructor
     */
    AbstractParameter() : mHandle(0), mName()
    {

    }

    /**
     *	constructor with given values
     *	@param	m_Handle the handle in the shader file
     *	@param	m_Name	the name of the parameter in the shader file
     */
    AbstractParameter(uint32_t m_Handle, std::string m_Name) : mHandle(m_Handle), mName(m_Name)
    {
    }

    /**
     *	default destructor
     */
    virtual ~AbstractParameter()
    {
    }

    /**
     *	uploads the parameter
     */
    virtual void upload() = 0;

    /**
     *	resets the data
     */
    virtual void resetData() = 0;

    /**
     *	method to query the parameter handle
     *	@return	returns the member
     */
    inline uint32_t getHandle() const
    {
        return mHandle;
    }


protected:

    uint32_t		mHandle;		/**< the api side handle to the parameter. */
    std::string     mName;			/**< the name of the parameter in the shader file. */
};

/**
 *	@class	Parameter
 *	@brief	the opengl template implementation of a AbstractParameter
 */
template <class T>
class Parameter : public AbstractParameter
{
public:

    /**
     *	default constructor
     */
    Parameter() : AbstractParameter(), mCPUData(NULL)
    {

    }

    /**
     *	constructor with given values
     *	@param	m_Handle the handle in the shader file
     *	@param	m_Name	the name of the parameter in the shader file
     */
    Parameter(uint32_t m_Handle, std::string m_Name) : AbstractParameter(m_Handle, m_Name), mCPUData(NULL)
    {

    }

    /**
     *	copy constructor
     *	@param	m_Other the other parameter
     */
    Parameter(const Parameter & m_Other) : AbstractParameter(m_Other), mCPUData(m_Other.mCPUData)
    {

    }

    /**
     *	default destructor
     */
    virtual ~Parameter()
    {
        mCPUData = NULL;
    }

    /**
     *	sets the cpu data pointer
     *	@param	m_CPUData the pointer to the cpu data
     */
    void setData(const T * m_CPUData)
    {
        mCPUData = m_CPUData;
    }

    /**
     *	uploads the parameter
     */
    virtual void upload();

    /**
     *	resets the data pointer
     */
    virtual void resetData()
    {
        mCPUData = NULL;
    }

    /**
     *	assignment operator
     *	@param	m_Other the other Parameter
     *	@return	returns reference to self
     */
    Parameter & operator=(const Parameter & m_Other)
    {
        if(this != &m_Other)
        {
            mHandle = m_Other.mHandle;
            mName = m_Other.mName;
            mCPUData = m_Other.mCPUData;
        }
        return *this;
    }

private:

    const T	* mCPUData;		/**< pointer to the cpu data of the parameter. */

};

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<int>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<float>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<Vector3>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<Vector4>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<Matrix3x3>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<Matrix4x4>::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<std::vector<int> >::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<std::vector<float> >::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<std::vector<Vector3> >::upload();

/**
 *	uploads the parameter
 *	@param	m_Data the parameter
 */
template<>
void Parameter<std::vector<Vector4> >::upload();

#endif // PARAMETER_H
