// **********************************************************
//      2024 : Arthur JEULIN
//      Copyright (c) Coast Autonomous 
//      Created by Arthur JEULIN on 03/10/2024.
// **********************************************************
//
//  Module : Testing Component in RTMaps to Load IMGs and GPS Data
//

// Includes the header of this component
#include "maps_demo.h"	

// Declaration of an input accepting uncompressed images (in the IplImage format).
MAPS_BEGIN_INPUTS_DEFINITION(MAPS_DEMO)
 		MAPS_INPUT("iInput_1", MAPS::FilterFloat64, MAPS::LastOrNextReader)
 		MAPS_INPUT("iInput_2", MAPS::FilterFloat64, MAPS::LastOrNextReader)
MAPS_END_INPUTS_DEFINITION

// Declaration of an output of IplImage type (uncompressed images).
MAPS_BEGIN_OUTPUTS_DEFINITION(MAPS_DEMO)
 		MAPS_OUTPUT("oOutput", MAPS::Float64, NULL,NULL,1)
MAPS_END_OUTPUTS_DEFINITION

// Use the macros to declare the properties
MAPS_BEGIN_PROPERTIES_DEFINITION(MAPS_DEMO)
    MAPS_PROPERTY("synch_tolerance",1000,false,false)
MAPS_END_PROPERTIES_DEFINITION

// Use the macros to declare the actions
MAPS_BEGIN_ACTIONS_DEFINITION(MAPS_DEMO)
MAPS_END_ACTIONS_DEFINITION

MAPS_COMPONENT_DEFINITION(MAPS_DEMO,"demo",
													"1.0",128,MAPS::Threaded,MAPS::Threaded,
			  -1,
			  -1,
			  -1,
			  -1)

void MAPS_DEMO::Birth()
{
	_first_time = true;
  _input[0] = &Input("iInput_1");
  _input[1] = &Input("iInput_2");
	synch_tolerance = GetIntegerProperty("synch_tolerance");
}


void MAPS_DEMO::Core() 
{

	MAPSTimestamp t = SynchroStartReading2(2,_input,iElts,synch_tolerance);
	if (iElts[0] == nullptr || iElts[1] == nullptr){
    ReportWarning("No Input Data");
    MAPS::Sleep(1'000);
		return;
  }

  double* input_1 = &iElts[0]->Float64();
  double* input_2 = &iElts[1]->Float64();


  double result = input_1[0] + input_2[0];

  MAPSIOElt* ioEltOut = StartWriting(Output("oOutput"));

  ioEltOut->Float64() = result;

  ioEltOut->Timestamp() = iElts[0]->Timestamp();

	StopWriting(ioEltOut);
  MAPS::Sleep(500'000);
}


void MAPS_DEMO::Death()
{
}