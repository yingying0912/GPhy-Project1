/***
	Create Interfaces
	ProjectEntries.CPP
	
		Objective: Interface to the Box2D TestBed framework

	TGD2251 Game Physics
	Copyright (C) by Ya-Ping Wong <ypwong@mmu.edu.my>
	Faculty of Computing & Informatics
	Multimedia University
***/

#include "Framework/Test.h"
#include "Framework/Render.h"
#include <freeglut/freeglut.h>
#include <cstring>

using namespace std;
#include "Project01.h"

TestEntry g_testEntries[] =
{
	{"Project01", Project01::Create},
	{NULL, NULL}
};
