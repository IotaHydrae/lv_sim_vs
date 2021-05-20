#include "Applications/Applications.h"
#include "FLT_theme.h"



/*Prototype*/

/**
 * @brief Entrance of FLT Project, should:
 * setrnv
 * call desktop app
 * @param  
*/
void FLT_Entry(void)
{
	/*Create a thread to update statusBar*/

	/* first app */
	desktop();
	//tile_test();
}

