/***************
 *
 *  Minall by Ralph Yozzo
 *      Minimize all windows.
 *      Works best when run from the LaunchPad or an icon.
 *      Sometimes, the Desktop minimizes and sometimes it doesn't. Go figure.
 *
 ***************/

#define INCL_WINWINDOWMGR
#define INCL_BASE
#define INCL_BSE
#define INCL_WINWORKPLACE
#define INCL_WINMESSAGEMGR      /* Window Message Functions     */
#define INCL_WINWINDOWMGR       /* Window Manager Functions     */
#define INCL_WINMENUS
#define INCL_WINFRAMEMGR
#define INCL_DOSPROCESS
#define INCL_WINDIALOGS         /* Window Dialog Mgr Functions  */
#define INCL_WINPOINTERS        /* Window Pointer Functions     */
#include <os2.h>


#include <stdio.h>
#include <conio.h>

#define MAXWINDOWS 32


void main(int argc, char *argv[]);
void main(int argc, char *argv[])
{
 HWND ahwnd[MAXWINDOWS];  /* array of window handles. */
 SWP aSwp[MAXWINDOWS];    /* array of SWP structures. */
 CHAR ClassName[256];
 CHAR ClassName1[256];
 CHAR Title[256];
 HAB hab;
 SWP swp;
 LONG  xcoord,ycoord;
 LONG  i=1;
 HENUM  henum;            /* enumeration handle                   */
 HMQ   hmq;
 BOOL rcb;
 HWND hwndTitle;

 
 hab = WinInitialize(0);          /* initialize PM */
 
 hmq = WinCreateMsgQueue(hab, 0); /* create default size queue */

 if(argc>1){
     WinMessageBox(HWND_DESKTOP,
         HWND_DESKTOP,              /* client-window handle  */
         "Purpose:  Minimize windows in one fell swoop.\r\r"
         "Usage:    start minall",
         "Minall by Ralph Yozzo",
         0,                         /* message box id        */
         MB_NOICON | MB_OK);        /* icon and button flags */
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
    exit(100);
 }
 i=0;

 henum=WinBeginEnumWindows
       (HWND_DESKTOP);
 do
 {
        aSwp[i].hwnd = WinGetNextWindow (henum);
        aSwp[i].fl= SWP_MINIMIZE               ;
 
 }
 while((aSwp[i++].hwnd!=NULL) && i < MAXWINDOWS);
 
 WinEndEnumWindows(henum);
 
 WinSetMultWindowPos(hab,aSwp,i-1);

 WinDestroyMsgQueue(hmq);
 WinTerminate(hab);
}
