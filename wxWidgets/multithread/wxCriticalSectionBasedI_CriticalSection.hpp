/*
 * wxCriticalSectionBasedI_CriticalSection.hpp
 *
 *  Created on: 08.04.2011
 *      Author: sgebauer
 */

#ifndef WXCRITICALSECTIONBASEDI_CRITICALSECTION_HPP_
#define WXCRITICALSECTIONBASEDI_CRITICALSECTION_HPP_

#include <Controller/multithread/I_CriticalSection.hpp>
#include <wx/thread.h> //class wxCriticalSection

class wxCriticalSectionBasedI_CriticalSection
	:
	public I_CriticalSection,
	public wxCriticalSection
{
public:
	wxCriticalSectionBasedI_CriticalSection();
	virtual ~wxCriticalSectionBasedI_CriticalSection();
    void Enter()
    {
    	wxCriticalSection::Enter();
    }
    void Leave()
    {
    	wxCriticalSection::Leave();
    }
};

#endif /* WXCRITICALSECTIONBASEDI_CRITICALSECTION_HPP_ */
