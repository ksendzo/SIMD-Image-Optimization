#ifndef OPERATION_ENUM_H
#define OPERATION_ENUM_H

enum operation_types {
	ADD, SUB, ISUB, MUL, DIV, IDIV,
	POW, LOG, ABS, MIN, MAX,
	INV, GRAY,
	FILTER
};

class Operation
{
	virtual void operation_opt() = 0;
	virtual void operation_nopt() = 0;
};

#endif 
