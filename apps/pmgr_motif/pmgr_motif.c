/*
          Copyright (C) 1993, 1994, RSNA and Washington University

          The software and supporting documentation for the Radiological
          Society of North America (RSNA) 1993, 1994 Digital Imaging and
          Communications in Medicine (DICOM) Demonstration were developed
          at the
                  Electronic Radiology Laboratory
                  Mallinckrodt Institute of Radiology
                  Washington University School of Medicine
                  510 S. Kingshighway Blvd.
                  St. Louis, MO 63110
          as part of the 1993, 1994 DICOM Central Test Node project for, and
          under contract with, the Radiological Society of North America.

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND NEITHER RSNA NOR
          WASHINGTON UNIVERSITY MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          jointly owned by RSNA and Washington University, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include the three paragraphs of
          the copyright notice.
*/
/* Copyright marker.  Copyright will be inserted above.  Do not remove */

/*
**                   Electronic Radiology Laboratory
**                 Mallinckrodt Institute of Radiology
**              Washington University School of Medicine
**
** Module Name(s):	main
** Author, Date:	Chander Sabharwal
** Intent:		This is the "main" program generated by uimx for
**			the Motif print manager program.  It performs some
**			initialization and then kicks off the Xt Loop
** Last Update:		$Author: smm $, $Date: 2002-10-31 23:36:07 $
** Source File:		$RCSfile: pmgr_motif.c,v $
** Revision:		$Revision: 1.17 $
** Status:		$State: Exp $
*/

static char rcsid[] = "$Revision: 1.17 $ $RCSfile: pmgr_motif.c,v $";


/*-----------------------------------------------------------
 * This is the project main program file for Xt generated
 * code. You may add application dependent source code
 * at the appropriate places.
 *
 * Do not modify the statements preceded by the dollar
 * sign ($), these statements will be replaced with
 * the appropriate source code when the main program is
 * generated.
 *
 * $Date: 2002-10-31 23:36:07 $  		$Revision: 1.17 $
 *-----------------------------------------------------------*/

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>

#include <Xm/Xm.h>

#include <stdio.h>

#include "dicom.h"
#include "ctnthread.h"
#include "condition.h"

#include "lst.h"
#include "tbl.h"
#include "manage.h"

static int jj;
extern DMAN_HANDLE *dmanHandle;
extern char *serverGroup;
char
   *icon_file = "icon.file",
   *icon_index = "icon.index",
   *db_file = "print.db";
extern CTNBOOLEAN silent;
CTNBOOLEAN Send_BIB_when_print = TRUE;
CTNBOOLEAN associationActive = FALSE;

/*----------------------------------------------------
 * UxXt.h needs to be included only when compiling a
 * stand-alone application.
 *---------------------------------------------------*/
#ifndef DESIGN_TIME
#include "UxXt.h"
#endif				/* DESIGN_TIME */

XtAppContext UxAppContext;
Widget UxTopLevel;
Display *UxDisplay;
int UxScreen;

/*----------------------------------------------
 * Insert application global declarations here
 *---------------------------------------------*/
static void usageerror();
char applicationTitle[20] = "PRINT_MANAGER";

#ifdef _NO_PROTO
main(argc, argv)
int argc;
char *argv[];
#else
main(int argc, char *argv[])
#endif				/* _NO_PROTO */
{
    char
       *databaseName = "CTNControl";
    CONDITION
	cond;
    CTNBOOLEAN
	verboseTBL = FALSE,
	verboseSRV = FALSE;


    /*-----------------------------------------------------------
     * Declarations.
     * The default identifier - mainIface will only be declared
     * if the interface function is global and of type swidget.
     * To change the identifier to a different name, modify the
     * string mainIface in the file "xtmain.dat". If "mainIface"
     * is declared, it will be used below where the return value
     * of  PJ_INTERFACE_FUNCTION_CALL will be assigned to it.
     *----------------------------------------------------------*/

    Widget mainIface;

    /*---------------------------------
     * Interface function declaration
     *--------------------------------*/

    Widget create_applicationShell1(swidget);

    swidget UxParent = NULL;


    /*---------------------
     * Initialize program
     *--------------------*/

#ifdef XOPEN_CATALOG
    if (XSupportsLocale()) {
	XtSetLanguageProc(NULL, (XtLanguageProc) NULL, NULL);
    }
#endif

    SgePreInitialize(&argc, argv);
    UxTopLevel = XtAppInitialize(&UxAppContext, "pmgr_motif",
				 NULL, 0, &argc, argv, NULL, NULL, 0);

    UxDisplay = XtDisplay(UxTopLevel);
    UxScreen = XDefaultScreen(UxDisplay);

    /*
     * We set the geometry of UxTopLevel so that dialogShells that are
     * parented on it will get centered on the screen (if defaultPosition is
     * true).
     */

    XtVaSetValues(UxTopLevel,
		  XtNx, 0,
		  XtNy, 0,
		  XtNwidth, DisplayWidth(UxDisplay, UxScreen),
		  XtNheight, DisplayHeight(UxDisplay, UxScreen),
		  NULL);

    /*-------------------------------------------------------
     * Insert initialization code for your application here
     *------------------------------------------------------*/

    while (--argc > 0 && (*++argv)[0] == '-') {
	switch (*(argv[0] + 1)) {
	case 'a':
	    argv++;
	    argc--;
	    strcpy(applicationTitle, *argv);
	    break;
	case 'D':
	    argv++;
	    argc--;
	    db_file = *argv;
	    break;
	case 'f':
	    if (argc-- < 1)
		usageerror();
	    databaseName = *++argv;
	    break;
	case 'F':
	    argv++;
	    argc--;
	    icon_file = *argv;
	    break;
	case 'h':
	    usageerror();
	    break;
	case 'I':
	    argv++;
	    argc--;
	    icon_index = *argv;
	    break;
	case 's':
	    silent = TRUE;
	    break;
	case 'S':
	    printf("BIBs sent as they are filled with an image.\n");
	    Send_BIB_when_print = FALSE;
	    break;
	case 'x':
	    if (argc-- < 1)
		usageerror();
	    argv++;
	    if (strcmp(*argv, "TBL") == 0)
		verboseTBL = TRUE;
	    else if (strcmp(*argv, "SRV") == 0)
		verboseSRV = TRUE;
	    else
		usageerror();
	    break;
	case 'v':
	    printf("Forcing all facilities into verbose mode.\n");
	    verboseTBL = TRUE;
	    verboseSRV = TRUE;
	    break;
	default:
	    printf("Unrecognized option: %s\n", *argv);
	    break;
	}
    }

    if (argc < 1)
	usageerror();
    serverGroup = *argv;

    THR_Init();
    /*TBL_Debug(verboseTBL);*/
    SRV_Debug(verboseSRV);
    cond = DMAN_Open(databaseName, "", "", &dmanHandle);
    if (cond != DMAN_NORMAL) {
	COND_DumpConditions();
	exit(1);
    }
    /*----------------------------------------------------------------
     * Create and popup the first window of the interface.  The
     * return value can be used in the popdown or destroy functions.
     * The Widget return value of  PJ_INTERFACE_FUNCTION_CALL will
     * be assigned to "mainIface" from  PJ_INTERFACE_RETVAL_TYPE.
     *---------------------------------------------------------------*/

    mainIface = create_applicationShell1(UxParent);

    UxPopupInterface(mainIface, no_grab);

    /*-----------------------
     * Enter the event loop
     *----------------------*/

    XtAppMainLoop(UxAppContext);
    THR_Shutdown();
}

static void
usageerror()
{
    char msg[] = "\
Usage: pmgr_motif [switches] printerGroup\n\
\n\
    -a appTitle  Use appTitle as the AE Title of the print manager\n\
                 rather than the default (PRINT_MANAGER)\n\
    -D database  Set the print database name (default: print.db)\n\
    -f control   Set the control database name (default: CTNControl)\n\
    -F file      Set the icon file pathname (default: icon.file)\n\
    -h           Print help page\n\
    -I index     Set the icon index pathname (default: icon.index)\n\
    -s           Place print manager in silent mode\n\
    -S           Set Basic Image Box attributes as user creates\n\
                 each BIB rather than waiting until the end\n\
    -x fac       Place facility fac in verbose mode (DUL, DCM, SRV, TBL)\n\
    -v           Place all facilities in verbose mode\n\
\n\
    printerGroup The group name which identifies the set of printers\n\
                 which will be targets for this invocation\n";

    fprintf(stderr, msg);
    exit(1);
}
