#ifndef CIRCUIT_H
#define CIRCUIT_H

#define CIRCUIT_TYPE_POWER_SOURCE 0
#define CIRCUIT_TYPE_WIRE 1
#define CIRCUIT_TYPE_SWITCH 2
#define CIRCUIT_TYPE_ANDGATE 3
#define CIRCUIT_TYPE_ORGATE 4
#define CIRCUIT_TYPE_NORGATE 5
#define CIRCUIT_TYPE_NANDGATE 6
#define CIRCUIT_TYPE_XOR 7
#define CIRCUIT_TYPE_NOT 8
#define CIRCUIT_TYPE_ONE_WAY 9
#define CIRCUIT_TYPE_SINK 10

typedef struct _Point {
	unsigned short x;
	unsigned short y;
} Point;

typedef struct _CircuitWire {
	struct _CircuitElement** inputs;
	int inputsNext;
	Point* wireLocations;
	int wireLocNext;
	Point* wireInputsPlaceholder;
	int placeholderNext;
	char powered;
	char checkedThisCycle;
} Wire;


typedef struct _CircuitElement {
	Wire* inputs[4];
	int type;
	char powered;
	char isOpenSwitch;
	char checkedThisCycle;
	Point outputLoc;
} CircuitElement;

char isElementPowered(CircuitElement* self);
void freeElement(CircuitElement* self);

void checkGates();
void createCircuitElement(int xPos, int yPos, int tileId);
void resetCircuitNet();
void connectAllInputs();
void toggleSwitch(int x, int y);


#endif
