// Particle.cpp: implementation of the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Visualizer_X.h"
#include "Particle.h"
#include "strman.h"
#include <strstream>

#include "LineCommand.h"
#include "PolygonCommand.h"
#include "CylinderCommand.h"
#include "SphereCommand.h"
#include "TypeCommand.h"
#include "HemisphereCommand.h"
#include "QuartersphereCommand.h"
#include "TwoQuartersphereCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParticle::CParticle()
{
	m_bDrawn = TRUE;
	m_nType = 0;
	m_nApplyingCommand = 1;
	m_scale = 1.0;
}

CParticle::CParticle(const CParticle& particle)
{
	m_bDrawn = particle.m_bDrawn;
	m_nType = particle.m_nType;
	m_nApplyingCommand = particle.m_nApplyingCommand;
	m_scale = particle.m_scale;

	int i;
	for (i=0; i<particle.m_positionArray.size(); i++)
	{
		CPosition position = particle.m_positionArray[i]; 
		m_positionArray.push_back(position);
	}
	

	// formally put here, not working yet!!
	for (i=0; i<particle.m_commandArray.size(); i++)
	{
		CDrawingCommand* pCommand = particle.m_commandArray[i]->Clone();
	}

	m_drawingTemplate = particle.m_drawingTemplate;
}

CParticle::~CParticle()
{
	
}

void CParticle::Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
	if (m_bDrawn == FALSE)
		return;

	int i, nType;
	double pos[3], radius, xm[3];

	FindCenterofMass(xm);
		
	int nPositions = m_positionArray.size();
	for (i=0; i<nPositions; i++)
	{
		nType = m_positionArray[i].GetType();
		
		m_positionArray[i][0] = xm[0] + m_scale * (m_positionArray[i][0] - xm[0]);
		m_positionArray[i][1] = xm[1] + m_scale * (m_positionArray[i][1] - xm[1]);
		m_positionArray[i][2] = xm[2] + m_scale * (m_positionArray[i][2] - xm[2]);
		
		pos[0] = m_positionArray[i][0];
		pos[1] = m_positionArray[i][1];
		pos[2] = m_positionArray[i][2];
		
		if (hiddenType[nType] == TRUE)
			continue;
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nType]);
		
		radius = m_positionArray[i].GetRadius(); // * 0.02f
		
		glTranslatef((GLfloat)pos[0], (GLfloat)pos[1], (GLfloat)pos[2]);	
		
		glutSolidSphere(radius, nResolution, nResolution);
		
		glTranslatef(-(GLfloat)pos[0], -(GLfloat)pos[1], -(GLfloat)pos[2]);
	}

	if (m_nApplyingCommand == 1)
	{
		int nCommands = m_commandArray.size();
		for (i=0; i<nCommands; i++)
		{
			m_commandArray[i]->Zoom(0.02f);
			m_commandArray[i]->Execute(materialAmbient, materialDiffuse, hiddenType);
		}
	}
}

void CParticle::DrawPOV(std::ostream& os, GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
}

void CParticle::FindCenterofMass(double* xm)
{
	double x, y, z;
	xm[0] = xm[1] = xm[2] = 0.0;
	for (int i=0; i<m_positionArray.size(); i++)
	{
		x = m_positionArray[i][0];
		y = m_positionArray[i][1];
		z = m_positionArray[i][2];
		
		xm[0] += x;
		xm[1] += y;
		xm[2] += z;
	}

	xm[0] /= m_positionArray.size();
	xm[1] /= m_positionArray.size();
	xm[2] /= m_positionArray.size();
}

/////////////////////////////////////////////////////////////
// I/O

void CParticle::Read(std::istream& is)
{
	int i;

	for (i=0; i<m_positionArray.size(); i++)
		m_positionArray[i].Read(is);
	
}

void CParticle::Write(std::ostream& os, BOOL* nHiddenType)
{
	int nType;
	for (int i=0; i<m_positionArray.size(); i++)
	{
		nType = m_positionArray[i].GetType();
		if (nHiddenType[nType] == FALSE)
			m_positionArray[i].Write(os);		
	}
}

int CParticle::ReadDrawingTemplate(const char* sFileName)
{
	int nNumBeads;
	char str[64];
	std::string entry, value;
	
	std::ifstream ifs(sFileName);
	
	while (!ifs.eof())
	{
		ifs.getline(str, 64);

		Parse(str, entry, value);
	
		if (strcmp(entry.data(), "[Number of Beads]") == 0)
			nNumBeads = atoi(value.data());
		else
			m_drawingTemplate.m_drawingCommands.push_back(str);
	}

	ifs.close();

	return nNumBeads;
}

int CParticle::ReadDrawingTemplate(std::istream& is)
{
	int i, nNumBeads;
	std::string str, identifier;
	
	while (1)
	{
		is >> str;
		
		if (str.length() == 0)
			continue;
		else
			break;
	}

	// end of template part
	if (strcmp(str.data(), "#") == 0)
		return -1;

	is >> nNumBeads;

	while (1)
	{
		is >> identifier;

		if (strcmp(identifier.data(), ";") == 0)
			break;
		else
		{
			if (strcmp(identifier.data(), "[LINE]") == 0)
			{
				std::string sStartPoint, sEndPoint;
				is >> sStartPoint >> sEndPoint;

				str = identifier + "\t" + sStartPoint + "\t" + sEndPoint;
			}
		
			m_drawingTemplate.m_drawingCommands.push_back(str);
		}
	}

	for (i=0; i<nNumBeads; i++)
	{
		CPosition position;
		position.Read(is);
		m_positionArray.push_back(position);
	}	

	ParseDrawingTemplate();

	return 1;
}

void CParticle::ParseDrawingTemplate()
{
	int i;

	m_commandArray.clear();
	for (i=0; i<m_drawingTemplate.m_drawingCommands.size(); i++)
		AddDrawingCommand(m_drawingTemplate.m_drawingCommands[i].data());

		
	
}

CParticle::CDrawingTemplate CParticle::GetDrawingTemplate()
{
	return m_drawingTemplate;
}

void CParticle::SetDrawingTemplate(const CParticle::CDrawingTemplate& drawingTemplate)
{
	m_drawingTemplate = drawingTemplate;

	ParseDrawingTemplate();
}

/////////////////////////////////////////////////////////////
// Manipulate

void CParticle::Zoom(double scale)
{
	int i;

	for (i=0; i<m_positionArray.size(); i++)
		m_positionArray[i].SetRadius(scale);

	for (i=0; i<m_commandArray.size(); i++)
		m_commandArray[i]->Zoom(scale);

}

void CParticle::Translate(double tx, double ty, double tz, double boxSizex, double boxSizey, double boxSizez)
{
	int i;
	for (i=0; i<m_positionArray.size(); i++)
	{
		m_positionArray[i][0] += tx;
		m_positionArray[i][0] -= boxSizex * anint(m_positionArray[i][0] / boxSizex); 
		
		m_positionArray[i][1] += ty;
		m_positionArray[i][1] -= boxSizey * anint(m_positionArray[i][1] / boxSizey); 
		
		m_positionArray[i][2] += tz;
		m_positionArray[i][2] -= boxSizez * anint(m_positionArray[i][2] / boxSizez); 
	}
}

void CParticle::BoxScaling(double Lx, double Ly, double Lz, double boxSizex, double boxSizey, double boxSizez)
{
	int i, nBeads;
	double x, y, z;

	nBeads = m_positionArray.size();
	for (i=0; i<nBeads; i++)
	{
		x = m_positionArray[i][0];
		y = m_positionArray[i][1];
		z = m_positionArray[i][2];

		m_positionArray[i][0] = m_positionArray[i][0] / Lx * boxSizex;
		m_positionArray[i][1] = m_positionArray[i][1] / Ly * boxSizey;
		m_positionArray[i][2] = m_positionArray[i][2] / Lz * boxSizez;


	//	x = m_positionArray[i][0];
	//	y = m_positionArray[i][1];
	//	z = m_positionArray[i][2];
	}
}

/////////////////////////////////////////////////////////////
// Setting

void CParticle::AddSite(const CPosition& position)
{
	m_positionArray.push_back(position);
}

void CParticle::SetSite(int i, const CPosition& position)
{
	m_positionArray[i][0] = position[0];
	m_positionArray[i][1] = position[1];
	m_positionArray[i][2] = position[2];
}

void CParticle::SetSite(int i, double* position)
{
	m_positionArray[i][0] = position[0];
	m_positionArray[i][1] = position[1];
	m_positionArray[i][2] = position[2];
}

void CParticle::SetType(int nType)
{
	int i;
	for (i=0; i<m_positionArray.size(); i++)
	{
		if (m_positionArray[i].GetType() > 0)
			m_positionArray[i].SetType(nType);
	}
}

/////////////////////////////////////////////////////////////
//

void CParticle::AddDrawingCommand(const char* command)
{
	std::string entry, value;
	CDrawingCommand* pCommand;

	Parse(command, entry, value);

	const char* str = entry.data();
	if (str[0] == '#') return;

	if (strcmp(entry.data(), "[LINE]") == 0)
	{
		int startPoint, endPoint;
		sscanf(value.data(), "%d\t%d", &startPoint, &endPoint);

		pCommand = new CLineCommand;
		((CLineCommand*)pCommand)->SetEndPoints(&m_positionArray[startPoint], &m_positionArray[endPoint]);

		m_commandArray.push_back(pCommand);
	}

	if (strcmp(entry.data(), "[POLYGON]") == 0)
	{
		int i, nVertices, *vertices;
		
		std::istrstream is(value.data());

		is >> nVertices;
		vertices = new int [nVertices];
		for (i=0; i<nVertices; i++)
			is >> vertices[i];

		pCommand = new CPolygonCommand;
		for (i=0; i<nVertices; i++)
			((CPolygonCommand*)pCommand)->AddVertex(&m_positionArray[vertices[i]]);	

		int nType = -1;
		is >> nType;
		if (nType >= 0)
			pCommand->SetColoringType(nType);

		m_commandArray.push_back(pCommand);

		delete [] vertices;
	}

	if (strcmp(entry.data(), "[CYL]") == 0)
	{
		int startPoint, endPoint, resolution=-1, nType=-1;
		double radius=1.0;
		string sep(" \t");
		int narg;
		vector<string> argv;
		SplitString(value.data(), sep, narg, argv);

		startPoint = atoi(argv[0].data());
		endPoint = atoi(argv[1].data());
		radius = atof(argv[2].data());
		if (narg == 4) resolution = atoi(argv[3].data());
		if (narg == 5) nType = atoi(argv[4].data());
	
	//	sscanf(value.data(), "%d\t%d\t%lf\t%d", &startPoint, &endPoint, &radius, &resolution);
	
		pCommand = new CCylinderCommand;
		((CCylinderCommand*)pCommand)->SetEndPoints(&m_positionArray[startPoint], &m_positionArray[endPoint]);
		((CCylinderCommand*)pCommand)->SetRadius(radius);
		if (narg == 4) ((CCylinderCommand*)pCommand)->SetResolution(resolution);
		if (narg == 5) pCommand->SetColoringType(nType);

		m_commandArray.push_back(pCommand);

	}

	if (strcmp(entry.data(), "[SPHERE]") == 0)
	{
		int center, resolution;
		double radius;
		string sep(" \t");
		int narg;
		vector<string> argv;
		SplitString(value.data(), sep, narg, argv);
		
		center = atoi(argv[0].data());
		radius = atof(argv[1].data());
		if (narg == 3) resolution = atoi(argv[2].data());

		pCommand = new CSphereCommand;
		((CSphereCommand*)pCommand)->SetCenter(&m_positionArray[center]);
		((CSphereCommand*)pCommand)->SetRadius(radius);
		if (narg == 3) ((CSphereCommand*)pCommand)->SetResolution(resolution);
		
		m_commandArray.push_back(pCommand);

	}

	if (strcmp(entry.data(), "[TYPE]") == 0)
	{
		int index;
		char type[10];
		sscanf(value.data(), "%d\t%s", &index, &type);

		pCommand = new CTypeCommand;
		((CTypeCommand*)pCommand)->SetTypeIndex(&m_positionArray[index], type);	

		m_commandArray.push_back(pCommand);

	}

	if (strcmp(entry.data(), "[NONPBC]") == 0)
	{
		int index;
		sscanf(value.data(), "%d", &index);
		
		m_positionArray[index].SetPBC(0);	

	}

	if (strcmp(entry.data(), "[HEMISPHERE]") == 0)
	{
		int startPoint, endPoint, resolution=8;
		double radius=1.0;
		string sep(" \t");
		int narg;
		vector<string> argv;
		SplitString(value.data(), sep, narg, argv);

		startPoint = atoi(argv[0].data());
		endPoint = atoi(argv[1].data());
		radius = atof(argv[2].data());
		if (narg == 4) resolution = atoi(argv[3].data());

	//	sscanf(value.data(), "%d\t%d\t%lf\t%d", &startPoint, &endPoint, &radius, &resolution);

		pCommand = new CHemisphereCommand;
		((CHemisphereCommand*)pCommand)->SetEndPoints(&m_positionArray[startPoint], &m_positionArray[endPoint]);
		((CHemisphereCommand*)pCommand)->SetRadius(radius);
		if (narg == 4) ((CHemisphereCommand*)pCommand)->SetResolution(resolution);

		m_commandArray.push_back(pCommand);
	}

	if (strcmp(entry.data(), "[QUARTERSPHERE]") == 0)
	{
		int startPoint, endPoint, resolution=8;
		double radius=1.0;
		string sep(" \t");
		int narg;
		vector<string> argv;
		SplitString(value.data(), sep, narg, argv);

		startPoint = atoi(argv[0].data());
		endPoint = atoi(argv[1].data());
		radius = atof(argv[2].data());
		if (narg == 4) resolution = atoi(argv[3].data());

	//	sscanf(value.data(), "%d\t%d\t%lf\t%d", &startPoint, &endPoint, &radius, &resolution);

		pCommand = new CQuartersphereCommand;
		((CQuartersphereCommand*)pCommand)->SetEndPoints(&m_positionArray[startPoint], &m_positionArray[endPoint]);
		((CQuartersphereCommand*)pCommand)->SetRadius(radius);
		if (narg == 4) ((CQuartersphereCommand*)pCommand)->SetResolution(resolution);

		m_commandArray.push_back(pCommand);
	}

	if (strcmp(entry.data(), "[TWOQUARTERS]") == 0)
	{
		int startPoint, endPoint, resolution=8;
		double radius=1.0;
		string sep(" \t");
		int narg;
		vector<string> argv;
		SplitString(value.data(), sep, narg, argv);

		startPoint = atoi(argv[0].data());
		endPoint = atoi(argv[1].data());
		radius = atof(argv[2].data());
		if (narg == 4) resolution = atoi(argv[3].data());

	//	sscanf(value.data(), "%d\t%d\t%lf\t%d", &startPoint, &endPoint, &radius, &resolution);

		pCommand = new CTwoQuartersphereCommand;
		((CTwoQuartersphereCommand*)pCommand)->SetEndPoints(&m_positionArray[startPoint], &m_positionArray[endPoint]);
		((CTwoQuartersphereCommand*)pCommand)->SetRadius(radius);
		if (narg == 4) ((CTwoQuartersphereCommand*)pCommand)->SetResolution(resolution);

		m_commandArray.push_back(pCommand);
	}
}

void CParticle::ReleasePeriodicBoundaryConditions(double* L)
{
	int i, k, nBeads;
	double pivot[3], half_box[3];

	half_box[0] = 0.5 * L[0];
	half_box[1] = 0.5 * L[1];
	half_box[2] = 0.5 * L[2];

	// Set the pivot point to be the first bead
	pivot[0] = m_positionArray[0][0];
	pivot[1] = m_positionArray[0][1];
	pivot[2] = m_positionArray[0][2];

	nBeads = m_positionArray.size();
	double pos;
	for (i=1; i<nBeads; i++)
	{
		if (m_positionArray[i].GetPBC() == 0)
			continue;

		for (k=0; k<3; k++)
		{
			pos = m_positionArray[i][k];
			if (pos - pivot[k] > half_box[k])
			{
				m_positionArray[i][k] -= L[k];

			}
			else if (pos - pivot[k] <= -half_box[k])
			{
				m_positionArray[i][k] += L[k];
			
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//

CParticle::CDrawingTemplate::CDrawingTemplate()
{

}

CParticle::CDrawingTemplate::CDrawingTemplate(const CParticle::CDrawingTemplate& drawingTemplate)
{
	m_drawingCommands = drawingTemplate.m_drawingCommands;
}

CParticle::CDrawingTemplate& CParticle::CDrawingTemplate::operator = (const CParticle::CDrawingTemplate& drawingTemplate)
{
	m_drawingCommands = drawingTemplate.m_drawingCommands;

	return *this;
}

CParticle::CDrawingTemplate::~CDrawingTemplate()
{
	m_drawingCommands.clear();
}

/////////////////////////////////////////////////////////////////////////////
//