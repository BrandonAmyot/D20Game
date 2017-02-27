//!@file
//!@brief Character Observer header file.
//!This observer class is designed to observe the character classes created by teammate Vance DeWaele
#pragma once
#include "Subject.h"

class Subject;

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};
