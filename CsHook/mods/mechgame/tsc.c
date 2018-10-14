#include "stdafx.h"
#include "player.h"
#include "map.h"

// return 1 to finish command and halt parsing
// return 0 to finish command and continue parsing
// return -1 to continue searching for existing command
int tscHook() {
	char* nextCommand;
	int argVal, arg2, arg3, arg4;
	char strBuf[32];

	char* scriptPointer = *CS_scriptPointer + *CS_scriptOffset;
	int currentCommand = *(int*)scriptPointer;
	if (currentCommand == *(int*)"<END") {
		// we "hijack" this command in the vanilla parser to inject our hook,
		// so we must duplicate it here.
		*CS_gameState |= 3;
		*CS_tscState = 0;
		*CS_currentFacepic = 0;
		*CS_playerStateFlags &= -2;
		return 1;

	} else if (currentCommand == *(int*)"<NAM") {
		int count;
		*CS_scriptOffset += 4;
		scriptPointer += 4;
		nextCommand = strchr(scriptPointer, '<');
		if (nextCommand != NULL) {
			count = nextCommand - scriptPointer;
			*CS_scriptOffset += count;
			if (count > 31) count = 31;
			strncpy(strBuf, scriptPointer, count);
			strBuf[count] = 0;
			CS_setMapName(strBuf);
		}
		return 0;

	} else if (currentCommand == *(int*)"<CML") {
		//custom CMP, specifying which layer to set the tile to
		//<CMP  layer : xTile : yTile : target
		*CS_scriptOffset += 4;
		argVal = CS_atoi(*CS_scriptOffset);
		*CS_scriptOffset += 5;
		arg2 = CS_atoi(*CS_scriptOffset);
		*CS_scriptOffset += 5;
		arg3 = CS_atoi(*CS_scriptOffset);
		*CS_scriptOffset += 5;
		arg4 = CS_atoi(*CS_scriptOffset);

		setTile(arg2, arg3, argVal, arg4);
		//make a smoke
		CS_createNPC(4, arg2 * 16 * CS_SUBPX, arg3 * 16 * CS_SUBPX, 0, 0, 0, 0, 0x100);

		*CS_scriptOffset += 4;
		return 0;

	} else if (currentCommand == *(int*)"<FM2") {
		*CS_scriptOffset += 4;
		*CS_fadeOrganya = 0;
		return 0;
	}

	return -1;
}
