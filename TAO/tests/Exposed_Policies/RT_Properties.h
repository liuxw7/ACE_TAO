//=============================================================================
/**
 *  @file    RT_Properties.h
 *
 *   Defines a series of "real time" property that an Object
 *   or a POA created on a RT-ORB can have.
 *
 *  @author  Angelo Corsaro <corsaro@cs.wustl.edu>
 */
//=============================================================================


#ifndef RT_PROPERTIES_H_
#define RT_PROPERTIES_H_

#include "tao/RTCORBA/RTCORBA.h"

class RT_Properties
{
public:
  // -- Ctor/Dtor --
  RT_Properties ();
  ~RT_Properties ();

  static RT_Properties * read_from (const ACE_TCHAR *file_name);

  // -- Accessor Methods --
  void priority (RTCORBA::Priority priority);
  RTCORBA::Priority priority ();

  void priority_bands (const RTCORBA::PriorityBands& priority_bands);
  const RTCORBA::PriorityBands& priority_bands ();

  void ior_source (const ACE_TCHAR *s);
  const ACE_TCHAR* ior_source ();

private:
  RTCORBA::Priority priority_;
  RTCORBA::PriorityBands priority_bands_;
  ACE_TString ior_source_;
};

#endif /* RT_PROPERTIES_H_ */
