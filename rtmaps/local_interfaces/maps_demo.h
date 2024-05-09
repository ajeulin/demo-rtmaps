// **********************************************************
//      2024 : Arthur JEULIN
//      Copyright (c) Coast Autonomous 
//      Created by Arthur JEULIN on 03/28/2024.
// **********************************************************
//
//  Module : Testing localization with GPS Data on the parking
//

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#ifndef MAPS_DEMO_H
#define MAPS_DEMO_H

// Includes maps sdk library header
#include <opencv2/opencv.hpp>

#define __IPL_H__
#include "maps.hpp"

// Declares a new MAPSComponent child class
class MAPS_DEMO : public MAPSComponent 
{
	// Use standard header definition macro
	MAPS_COMPONENT_STANDARD_HEADER_CODE(MAPS_DEMO)
private :
	// Place here your specific methods and attributes
  MAPSIOElt* iElts[2];
  MAPSInput*	_input[2];
  MAPSDelay	synch_tolerance; 
	bool _first_time ;

};

#endif /*MAPS_DEMO_H*/

