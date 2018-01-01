#ifndef _MPxSelectionContext
#define _MPxSelectionContext
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related
// material (collectively the "Data") in these files contain unpublished
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its
// licensors,  which is protected by U.S. and Canadian federal copyright law
// and by international treaties.
//
// The Data may not be disclosed or distributed to third parties or be
// copied or duplicated, in whole or in part, without the prior written
// consent of Autodesk.
//
// The copyright notices in the Software and this entire statement,
// including the above license grant, this restriction and the following
// disclaimer, must be included in all copies of the Software, in whole
// or in part, and all derivative works of the Software, unless such copies
// or derivative works are solely in the form of machine-executable object
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE,
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES.
// ==========================================================================
//+
//
// CLASS:    MPxSelectionContext
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES


#include <maya/MPxContext.h>
#include <maya/MPoint.h>

// ****************************************************************************
// DECLARATIONS

class MString;

// ****************************************************************************
// CLASS DECLARATION (MPxSelectionContext)

//! \ingroup OpenMayaUI MPx
//! \brief Base class for interative selection tools 
/*!
This class is used in creating user defined tools that use the internal
selection mechanism in maya.
*/
class OPENMAYAUI_EXPORT MPxSelectionContext : public MPxContext
{
public:
	MPxSelectionContext ();
	virtual	~MPxSelectionContext ();

        // import base class overloaded virtual functions
        // to avoid function hidden warnings.
        using MPxContext::doPress; 
        using MPxContext::doRelease;
        using MPxContext::doDrag;
        using MPxContext::doHold;

	virtual MStatus		doPress ( MEvent & event );
	virtual MStatus		doRelease ( MEvent & event );
	virtual MStatus		doDrag ( MEvent & event );
	virtual MStatus		doHold ( MEvent & event );
	virtual MStatus 	helpStateHasChanged ( MEvent & );

	virtual MStatus     addManipulator( const MObject & manipulator );
	virtual MStatus     deleteManipulators();

	MStatus				setAllowPreSelectHilight();
	MStatus				setAllowSoftSelect();
	MStatus				setAllowSymmetry();
	MStatus				setAllowDoubleClickAction();

	MStatus				setImage( const MString & image, ImageIndex index );
	MString				image( ImageIndex index, MStatus * ReturnStatus = NULL ) const;
BEGIN_NO_SCRIPT_SUPPORT:
	//!     NO SCRIPT SUPPORT
	MStatus				getImage( MString & image, ImageIndex index ) const;
END_NO_SCRIPT_SUPPORT:

	// SCRIPT USE ONLY
	bool _isSelecting()
		{ return isSelecting(); }
	MPoint _startPoint()
		{ return startPoint(); }
	MPoint _lastDragPoint()
		{ return lastDragPoint(); }
	MPxToolCommand* _newToolCommand()
		{ return newToolCommand(); }
	//

protected:

	// These methods determine whether the tool will select
	// an object or operate on an object
	//!	USE _isSelecting() IN SCRIPT
	bool        isSelecting();

	// Get the world space location of the selection point
	//!	USE _startPoint() IN SCRIPT
	MPoint 		startPoint();		// point where dragging started
	//!	USE _lastDragPoint() IN SCRIPT
	MPoint 		lastDragPoint();	// preview drag point (both in WS)


	// Create an instance of a tool command for use in
	// this context.
	//
	//! CALL _newToolCommand() IN SCRIPT
	virtual MPxToolCommand *	newToolCommand();

public:
	// Temporarily putting these virtual functions at the end
	virtual void		abortAction();
	virtual bool		processNumericalInput( const MDoubleArray &values,
											   const MIntArray &flags,
											   bool isAbsolute );
	virtual bool		feedbackNumericalInput() const;
	virtual MSyntax::MArgType	argTypeNumericalInput( unsigned int index ) const;

	static const char*	className();

private:

};

#endif /* __cplusplus */
#endif /* _MPxSelectionContext */