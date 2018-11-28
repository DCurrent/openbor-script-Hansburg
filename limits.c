#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/instance.c"

float dc_hansburg_get_max_height()
{
	return getscriptvar(DC_HANSBURG_VAR_KEY_MAX_HEIGHT);
}

void dc_hansburg_set_max_height(float value)
{
	int vartype = NULL();

	vartype = typeof(value);

	// Catch bad arguments here.
	if (vartype != openborconstant("VT_DECIMAL")
		&& vartype != openborconstant("VT_INTEGER"))
	{
		log("\n\n error: dc_hansburg_set_max_height(float value): {value} argument is an invalid type. Floating decimal or integer is required.");
		return;
	}

	setscriptvar(DC_HANSBURG_VAR_KEY_MAX_HEIGHT, value);
}

void dc_hansburg_set_disable_time(int value)
{
	int vartype = NULL();

	vartype = typeof(value);

	// Catch bad arguments here.
	if (vartype != openborconstant("VT_INTEGER")
		|| vartype != openborconstant("VT_EMPTY"))
	{
		log("\n\n error: dc_hansburg_set_disable_time(float value): {value} argument has invalid type. Integer or empty (NULL) value required.");
		return;
	}

	setindexedvar(DC_HANSBURG_VAR_KEY_DISABLE, value);
}

// Return true if disable time set by user. Clears timer
// if expired and not infinite.
int dc_hansburg_disable_check()
{
	int result = 0;
	int elapsed_time = 0;
	int time_disable = 0;
	int vartype = 0;

	time_disable = getindexedvar(DC_HANSBURG_VAR_KEY_DISABLE);

	vartype = typeof(time_disable);

	// Does time have any valid integer value?
	if (vartype == openborconstant("VT_INTEGER"))
	{
		// Is timer still active (greater than
		// current elapsed time) or infinite? if either
		// is true, than we return true. Elsewise
		// we should clear the timer and
		// do nothing. A default of false
		// will be returned instead.
		if (time_disable > elapsed_time
			|| time_disable != DC_HANSBURG_TIME_INFINITE)
		{
			// Result will be true.
			result = 1;
		}
		else
		{
			time_disable = NULL();

			setindexedvar(DC_HANSBURG_VAR_KEY_DISABLE, time_disable);
		}
	}

	return result;
}