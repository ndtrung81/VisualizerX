# Microsoft Developer Studio Project File - Name="Visualizer_X" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Visualizer_X - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Visualizer_X.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Visualizer_X.mak" CFG="Visualizer_X - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Visualizer_X - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Visualizer_X - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Visualizer_X - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Release/"
# ADD F90 /include:"Release/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glaux.lib glu32.lib /nologo /subsystem:windows /profile /debug /machine:I386

!ELSEIF  "$(CFG)" == "Visualizer_X - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\Codes\Output"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=df.exe
# ADD BASE F90 /include:"Debug/"
# ADD F90 /include:"Debug/"
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glaux.lib glu32.lib glut32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Visualizer_X - Win32 Release"
# Name "Visualizer_X - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArrowObject.cpp
# End Source File
# Begin Source File

SOURCE=.\BODDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BondObject.cpp
# End Source File
# Begin Source File

SOURCE=.\CellsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeTypeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ClusteringDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CurrentDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomCommandLineInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CylinderCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\DiffractionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawingCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawingObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawnButton.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawnEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FFTStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GLEnabledView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\HemisphereCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\LightDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LineCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MaterialsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelessDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\myfft.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Particle.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticlesPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParticleTemplateDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygonCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\Position.cpp
# End Source File
# Begin Source File

SOURCE=.\PreprocPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\QuartersphereCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\RDFDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplicateDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Serie.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecialEffectsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\SphereCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\SphereObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strman.cpp
# End Source File
# Begin Source File

SOURCE=.\Texture.cpp
# End Source File
# Begin Source File

SOURCE=.\TwoQuartersphereCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\TypeCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewParticleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Visualizer_X.cpp
# End Source File
# Begin Source File

SOURCE=.\Visualizer_X.rc
# End Source File
# Begin Source File

SOURCE=.\Visualizer_XDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Visualizer_XView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArrowObject.h
# End Source File
# Begin Source File

SOURCE=.\BODDialog.h
# End Source File
# Begin Source File

SOURCE=.\BondObject.h
# End Source File
# Begin Source File

SOURCE=.\BuildingBlock.h
# End Source File
# Begin Source File

SOURCE=.\CellsDialog.h
# End Source File
# Begin Source File

SOURCE=.\ChangeTypeDialog.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ClusteringDialog.h
# End Source File
# Begin Source File

SOURCE=.\CurrentDialog.h
# End Source File
# Begin Source File

SOURCE=.\CustomCommandLineInfo.h
# End Source File
# Begin Source File

SOURCE=.\CylinderCommand.h
# End Source File
# Begin Source File

SOURCE=.\DiffractionDialog.h
# End Source File
# Begin Source File

SOURCE=.\DlgToolBar.h
# End Source File
# Begin Source File

SOURCE=.\DrawingCommand.h
# End Source File
# Begin Source File

SOURCE=.\DrawingObject.h
# End Source File
# Begin Source File

SOURCE=.\DrawnButton.h
# End Source File
# Begin Source File

SOURCE=.\DrawnEdit.h
# End Source File
# Begin Source File

SOURCE=.\FFTStatic.h
# End Source File
# Begin Source File

SOURCE=.\FormatDialog.h
# End Source File
# Begin Source File

SOURCE=.\GLEnabledView.h
# End Source File
# Begin Source File

SOURCE=.\GraphCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HelpDialog.h
# End Source File
# Begin Source File

SOURCE=.\HemisphereCommand.h
# End Source File
# Begin Source File

SOURCE=.\LightDialog.h
# End Source File
# Begin Source File

SOURCE=.\LineCommand.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MaterialsDialog.h
# End Source File
# Begin Source File

SOURCE=.\matrix.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\ModelessDialog.h
# End Source File
# Begin Source File

SOURCE=.\myfft.h
# End Source File
# Begin Source File

SOURCE=.\ObjectDialog.h
# End Source File
# Begin Source File

SOURCE=.\Particle.h
# End Source File
# Begin Source File

SOURCE=.\ParticlesPage.h
# End Source File
# Begin Source File

SOURCE=.\ParticleTemplateDialog.h
# End Source File
# Begin Source File

SOURCE=.\PolygonCommand.h
# End Source File
# Begin Source File

SOURCE=.\Position.h
# End Source File
# Begin Source File

SOURCE=.\PreprocPage.h
# End Source File
# Begin Source File

SOURCE=.\ProjectionDialog.h
# End Source File
# Begin Source File

SOURCE=.\QuartersphereCommand.h
# End Source File
# Begin Source File

SOURCE=.\RDFDialog.h
# End Source File
# Begin Source File

SOURCE=.\ReadDialog.h
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\ReplicateDialog.h
# End Source File
# Begin Source File

SOURCE=.\ResizingDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Serie.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\SpecialEffectsPage.h
# End Source File
# Begin Source File

SOURCE=.\Sphere.h
# End Source File
# Begin Source File

SOURCE=.\SphereCommand.h
# End Source File
# Begin Source File

SOURCE=.\SphereObject.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrMan.h
# End Source File
# Begin Source File

SOURCE=.\Texture.h
# End Source File
# Begin Source File

SOURCE=.\TwoQuartersphereCommand.h
# End Source File
# Begin Source File

SOURCE=.\TypeCommand.h
# End Source File
# Begin Source File

SOURCE=.\ViewParticleDialog.h
# End Source File
# Begin Source File

SOURCE=.\Visualizer_X.h
# End Source File
# Begin Source File

SOURCE=.\Visualizer_XDoc.h
# End Source File
# Begin Source File

SOURCE=.\Visualizer_XView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\diffract.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_mate.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_rdf.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_visu.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Visualizer_X.ico
# End Source File
# Begin Source File

SOURCE=.\res\Visualizer_X.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Visualizer_XDoc.ico
# End Source File
# Begin Source File

SOURCE=.\visualizerX.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Visualizer_X : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:103
# 	2:21:SplashScreenInsertKey:4.0
# End Section
