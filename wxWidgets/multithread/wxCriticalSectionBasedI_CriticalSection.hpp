/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
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
