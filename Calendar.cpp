#include <iostream>
#include <sstream>
#include <thread>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>
#include <tchar.h>
#include "sql.h"
#include "sqlext.h"

using namespace std;

int nc;

static int cxClient, cyClient;
HDC hdc;
PAINTSTRUCT ps;

PAINTSTRUCT     pss;
BITMAP          bitmap;
HDC             hdcMem;
HGDIOBJ         oldBitmap;
HBITMAP         hBitmap;

#define MAX_STRING_LEN 255

HWND hwnd;
HWND hwndMain;
HWND hwndTab;
HWND hwnd0;
HWND hwnd1;
HWND hwnd2;
HWND hwnd3;
HINSTANCE hinst;
 
#define ID_TIMER 1
#define TWOPI (2 * 3.14159)

#define IDC_BTNMONPLUS 2
#define IDC_BTNMONMINUS 3
#define IDC_BTNYRPLUS 4
#define IDC_BTNYRMINUS 5
#define IDC_BTNTODAY 6
#define IDC_BTNPLANIT 7
#define IDC_BTNSAVE 8
#define IDC_BTNPREVDAY 9
#define IDC_BTNNEXTDAY 10

HINSTANCE hInst;

BOOL fist = TRUE;

BOOL dayFirst = TRUE;
BOOL monthFirst = TRUE;

int Left = -700, Top = 700, Width = 210, Height = 210;
int  _YYYY, _MM, _DD, _tempyy, _tempmm;

 int _NumberOfDays(int month, int year)
{

       int No_of_days = 0;
       switch (month)
       {
       case 1:
              No_of_days = 31;
              break;
       case 2:
              if (!((year % 4) || !(year % 100) && (year % 400)))
                     No_of_days = 29;
              else
                     No_of_days = 28;
              break;
       case 3:
              No_of_days = 31;
              break;
       case 4:
              No_of_days = 30;
              break;
       case 5:
              No_of_days = 31;
              break;
       case 6:
              No_of_days = 30;
              break;
       case 7:
              No_of_days = 31;
              break;
       case 8:
              No_of_days = 31;
              break;
       case 9:
              No_of_days = 30;
              break;
       case 10:
              No_of_days = 31;
              break;
       case 11:
              No_of_days = 30;
              break;
       case 12:
              No_of_days = 31;
              break;
       }

       return No_of_days;
}


int No_Of_Days()
{

       int d1, m1, y1;
       int d2, m2, y2;
       int D, M, Y;
       int Arr[12];
       int i, count;


       y1 =_YYYY;
       m1 = _MM;
       d1 = 01;


       y2 = 2015;
       m2 = 01;
       d2 = 01;

       if (y1 > y2 || (m1 > m2 && y1 == y2))
       {
              D = d1;
              M = m1;
              Y = y1;

              d1 = d2;
              m1 = m2;
              y1 = y2;

              d2 = D;
              m2 = M;
              y2 = Y;

       }

       count = 0;

       for (i = m1; i < (m2 + (y2 - y1) * 12); i++)

       {
              if (i > 12)
              {

                     i = 1;
                     y1 = y1 + 1;
              }

              Arr[0] = 31;
              if (!((y1 % 4) || !(y1 % 100) && (y1 % 400)))
              {
                     Arr[1] = 29;
              }
              else
              {
                     Arr[1] = 28;
              }
              Arr[2] = 31;
              Arr[3] = 30;
              Arr[4] = 31;
              Arr[5] = 30;
              Arr[6] = 31;
              Arr[7] = 31;
              Arr[8] = 30;
              Arr[9] = 31;
              Arr[10] = 30;
              Arr[11] = 31;

              count = count + (Arr[i - 1]);

       }

       count = count + d2 - d1;

       if (count < 0)
              count = count * -1;
  
       return count;
}


int Name_Of_Day()
{
       /* Assuming in 2015 on first january the day was thrusday. */
       /* Let S-1 M-2 T-3 W-4 T-5 F-6 S-7 */
        
       int _day = 5;
       int total_days = 0;

       total_days = No_Of_Days();

       if (_YYYY >= 2015)
       {

              for (int k = 1; k <= total_days; k++)
              {
                     _day++;
                     if (_day> 7)
                           _day = 1;
              }
       }
       else
       {
              for (int k = 1; k <= total_days; k++)
              {
                     _day--;
                     if (_day< 1)
                           _day = 7;
              }
       }

       return _day;

}

void WriteDays(HDC hdc, int left, int top)
{

       HFONT hfont;
       LOGFONT f = { 0 };
       HGDIOBJ holdfont;
       static HBRUSH hBrush;

       int No_of_days;
       int _left = left, _top = top;
       int _col = 0;
       int _i;

       hBrush = CreateSolidBrush(RGB(0,255,255));
      
       f.lfHeight = 110; /* font height */
       hfont = CreateFontIndirect(&f);
       holdfont = SelectObject(hdc, hfont);
       SetTextColor(hdc, RGB(255, 255, 255));
       SetBkMode(hdc, TRANSPARENT);


       No_of_days = _NumberOfDays((int)_MM, (int)_YYYY);

       left = left + (Name_Of_Day() - 1) * 200;

       for (int i = 0; i< No_of_days; i++)
       {

              if (left >= _left + 7*200)
              {
                     left = _left;
                     top -= 200;
              }


              /*****************************/
              if (_YYYY == _tempyy && _MM == _tempmm && _DD == i + 1)
              {
                     SelectObject(hdc, hBrush);
                     Ellipse(hdc, left-25, top+40+20, left+125, top-125);
                     _col = 1;

              }
              /*****************************/


              if (_col == 1)
              {
                     SetTextColor(hdc, RGB(255, 255, 255));
                     _col = 0;
              }
              else if (left == _left)
                     SetTextColor(hdc, RGB(255, 0, 0));
              else
                     SetTextColor(hdc, RGB(255, 255, 255));

              _i = i + 1;
              char buffer[13];
              _itoa(_i, buffer, 10);
              sprintf(buffer,"%d",_i);
              TextOut(hdc, left, top, buffer, 2);

              left += 200;

       }

}


void Draw(HDC hdc)
{

       HFONT hfont;
       LOGFONT f = { 0 };
       HGDIOBJ holdfont;

       int left = Left, top = Top;
      
       int _left = -400;

       f.lfHeight = 110; /* font height */
       hfont = CreateFontIndirect(&f);
       holdfont = SelectObject(hdc, hfont);
       SetTextColor(hdc, RGB(255, 0, 0));
       SetBkMode(hdc, TRANSPARENT);


       /******************************************/

             
              TextOut(hdc, left+10, top+40+8, _T("S"), 2);
              left += 200;
              SetTextColor(hdc, RGB(255, 255, 255));
              SetBkMode(hdc, TRANSPARENT);
              TextOut(hdc, left + 10, top+40+ 8, _T("M"), 2);
              left += 200;
              TextOut(hdc, left + 10, top+40+ 8, _T("T"), 2);
              left += 200;
              TextOut(hdc, left + 10, top+40+ 8, _T("W"), 2);
              left += 200;
              TextOut(hdc, left + 10, top+40+ 8, _T("T"), 2);
              left += 200;
              TextOut(hdc, left + 10, top+40+ 8, _T("F"), 2);
              left += 200;
              TextOut(hdc, left + 10, top+40+ 8, _T("S"), 2);
              left += 200;
             
      

       /*******************************************/

              SetTextColor(hdc, RGB(0, 128, 255));
              SetBkMode(hdc, TRANSPARENT);

              switch (_MM)
              {
              case 1:
                     TextOut(hdc, _left, top+40+ 200, _T("January"), 7);
                     break;
              case 2:
                     TextOut(hdc, _left, top+40+ 200, _T("February"), 8);
                     break;
              case 3:
                     TextOut(hdc, _left, top+40+ 200, _T("March"), 5);
                     break;
              case 4:
                     TextOut(hdc, _left, top+40+ 200, _T("April"), 5);
                     break;
              case 5:
                     TextOut(hdc, _left, top+40+ 200, _T("May"), 3);
                     break;
              case 6:
                     TextOut(hdc, _left, top+40+ 200, _T("June"), 4);
                     break;
              case 7:
                     TextOut(hdc, _left, top+40+ 200, _T("July"), 4);
                     break;
              case 8:
                     TextOut(hdc, _left, top+40+ 200, _T("August"), 6);
                     break;
              case 9:
                     TextOut(hdc, _left, top+40+ 200, _T("September"), 9);
                     break;
              case 10:
                     TextOut(hdc, _left, top+40+ 200, _T("October"), 7);
                     break;
              case 11:
                     TextOut(hdc, _left, top+40+ 200, _T("November"), 8);
                     break;
              case 12:
                     TextOut(hdc, _left, top+40+ 200, _T("December"), 8);
                     break;
              }


              int i = _YYYY;
              wchar_t w[36] = {0};
              _itow(i, w, 10);
              
              
              TextOut(hdc, _left+500, top+40+200, (LPCSTR)w, 10);
}

void Init()
{
      
       static SYSTEMTIME st;

       GetLocalTime(&st);

       _YYYY = st.wYear;
       _MM =  st.wMonth;
       _DD = st.wDay;

       _tempyy = _YYYY;
       _tempmm = _MM;

}

void ClearScreen(HDC hdc)
{
    HBRUSH yellow_brush2 = CreateSolidBrush(RGB(155,169,60));
    RECT rrect3 = {-3000, 940, 4000, -760};
    FillRect(hdc, &rrect3, yellow_brush2);
    DeleteObject(yellow_brush2);

    HBRUSH yellow_brush = CreateSolidBrush(RGB(255,199,90));
    RECT rrect = {-1000, 940, 1000, -760};
    FillRect(hdc, &rrect, yellow_brush);
    DeleteObject(yellow_brush);
}


void SetIsotropic(HDC hdc, int cxClient, int cyClient)
{
       SetMapMode(hdc, MM_ISOTROPIC);
       SetWindowExtEx(hdc, 1000, 1000, NULL);
       SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
       SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
}

LRESULT CALLBACK ChildrenProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
 
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
 
static HWND hBtnNextDay = NULL, hBtnPrevDay = NULL, hBtnSave = NULL, hEditDaily = NULL, hEdit = NULL, hBtnPlanIt = NULL, hBtnMonPlus = NULL, hBtnMonMinus = NULL, hBtnYrPlus = NULL, hBtnYrMinus = NULL, hBtnToday = NULL;

void con_exit(SQLHDBC con)
{
    unsigned char state[6], buf[200];
    long int code;
    short int buflen;
    SQLError(NULL, con, SQL_NULL_HSTMT, state, &code, buf, sizeof(buf), &buflen);
    buf[buflen] = 0;
    printf("conSQL error: %s - %ld - %s\n", state, code, buf);
    exit(1);
}

void stmt_exit(SQLHSTMT stmt)
{
    unsigned char state[6], buf[200];
    long int code;
    short int buflen;
    SQLError(NULL, NULL, stmt, state, &code, buf, sizeof(buf), &buflen);
    buf[buflen] = 0;
    printf("stmtSQL error: %s - %ld - %s\n", state, code, buf);
    exit(1);
}

void other_exit(char *msg)
{
    printf("%s\n", msg);
    //exit(1);
}

void CloseWindows()
{
    DestroyWindow(hBtnSave);
    DestroyWindow(hBtnPlanIt);
    DestroyWindow(hBtnMonPlus);
    DestroyWindow(hBtnMonMinus);
    DestroyWindow(hBtnYrPlus);
    DestroyWindow(hBtnYrMinus);
    DestroyWindow(hBtnToday);
}
 
char* t2_get_one(SQLHDBC con, string f2, string f3, string f4)
{
    SQLCHAR f1[6666];
    SQLHSTMT stmt;
    string sqlstr;
    int stat;
    /* get statement */
    sqlstr = "SELECT cont FROM t2 WHERE mnth = " + f2 + " and yr = " + f3+ " and dy =" +f4;

    char* c = const_cast<char*>(sqlstr.c_str());

    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR *)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLBindCol(stmt, 1, SQL_C_CHAR, &f1, sizeof(f1), NULL);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* process result */
    stat = SQLFetch(stmt);

    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        other_exit("Row not found");
    }

    /* close statement */
    SQLCloseCursor(stmt);
    SQLFreeStmt(stmt, 0);

    std::string s((char*)f1);
    char* e = const_cast<char*>(s.c_str());

    return e;
}

void MakeWindow(int num, HWND hwnd2, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd2);
    
    HDC hdc2 = GetDC(hwnd);
    
    hwnd = hwnd2;

    static int cxClient, cyClient;
    PAINTSTRUCT ps;

    cxClient = LOWORD(lParam);
    cyClient = HIWORD(lParam);
    
    if(num==0)
    {
        CloseWindows();

        HBRUSH yellow_brush = CreateSolidBrush(RGB(130,210,90));
        RECT rrect = {0, 20, 4540, 740};
        FillRect(hdc, &rrect, yellow_brush);
        DeleteObject(yellow_brush);
        
        Init();

        char aa[100];
        sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
        SetWindowTextA(hwndMain,aa);

        SQLHENV env;
        SQLHDBC dbc;
        SQLHSTMT stmt;
        SQLRETURN ret; /* ODBC API return status */
        SQLSMALLINT columns; /* number of columns in result-set */
        int row = 0;

        /* Allocate an environment handle */
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
        /* We want ODBC 3 support */
        SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
        /* Allocate a connection handle */
        SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
        /* Connect to the DSN mydsn */
        /* You will need to change mydsn to one you have created and tested */
        SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                         NULL, 0, NULL, SQL_DRIVER_COMPLETE);
        /* Allocate a statement handle */
        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

        std::string q = std::to_string(_DD);
        char* b = const_cast<char*>(q.c_str());
        std::string s = std::to_string(_MM);
        char* c = const_cast<char*>(s.c_str());
        std::string t = std::to_string(_YYYY);
        char* d = const_cast<char*>(t.c_str());
        char* str = t2_get_one(dbc, c, d, b);

        if(dayFirst) {
            MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
            hEditDaily = CreateWindow(
            TEXT("EDIT"), str,
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
            ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE  |
            WS_VSCROLL | WS_HSCROLL,
            20, 80, 1000, 540, hwnd2,
            NULL, GetModuleHandle(NULL), NULL);
            dayFirst = FALSE;
            HFONT hFont=CreateFont(0,22,0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));
            SendMessage(hEditDaily,WM_SETFONT,(WPARAM)hFont,0);
        } else {
            MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
            MoveWindow(hEditDaily, 20, 80, 1000, 540, TRUE);
        }

        SetWindowText(hEditDaily, str);

        hBtnPrevDay = CreateWindow(TEXT("BUTTON"), TEXT("Previous Day <"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               920, 640, 190, 40,
               hwnd2,
               (HMENU)IDC_BTNPREVDAY,
               hInst, NULL);

        // Month--
        hBtnNextDay = CreateWindow(TEXT("BUTTON"), TEXT("Next Day >"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               1220, 640, 90, 40,
               hwnd2,
               (HMENU)IDC_BTNNEXTDAY,
               hInst, NULL);

        // Month++
        hBtnMonPlus = CreateWindow(TEXT("BUTTON"), TEXT("Month++"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               480, 640, 90, 40,
               hwnd2,
               (HMENU)IDC_BTNMONPLUS,
               hInst, NULL);

        // Month--
        hBtnMonMinus = CreateWindow(TEXT("BUTTON"), TEXT("Month- -"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               370, 640, 90, 40,
               hwnd2,
               (HMENU)IDC_BTNMONMINUS,
               hInst, NULL);

        // Year++
        hBtnYrPlus = CreateWindow(TEXT("BUTTON"), TEXT("Year++"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               250, 640, 100, 40,
               hwnd2,
               (HMENU)IDC_BTNYRPLUS,
               hInst, NULL);

        // Year--
        hBtnYrMinus = CreateWindow(TEXT("BUTTON"), TEXT("Year- -"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               130, 640, 100, 40,
               hwnd2,
               (HMENU)IDC_BTNYRMINUS,
               hInst, NULL);


        // Today
        hBtnToday = CreateWindow(TEXT("BUTTON"), TEXT("Today"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               10, 640, 100, 40,
               hwnd2,
               (HMENU)IDC_BTNTODAY,
               hInst, NULL);

       // PLAN MONTH IT
        hBtnPlanIt = CreateWindow(TEXT("BUTTON"), TEXT("Plan It"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               600, 640, 100, 40,
               hwnd2,
               (HMENU)IDC_BTNPLANIT,
               hInst, NULL);

       // Save
        hBtnSave = CreateWindow(TEXT("BUTTON"), TEXT("Save"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               780, 640, 100, 40,
               hwnd2,
               (HMENU)IDC_BTNSAVE,
               hInst, NULL);
    } else if(num==1) {
        
        CloseWindows();

        HBRUSH yellow_brush = CreateSolidBrush(RGB(240,169,40));
        RECT rrect = {0, 20, 4540, 740};
        FillRect(hdc, &rrect, yellow_brush);
        DeleteObject(yellow_brush);

        hdc = BeginPaint(hwnd, &ps);

        // Today

        Init();

        SetIsotropic(hdc2, cxClient, cyClient);
        SetTimer(hwnd, ID_TIMER, 1000, NULL);
        Draw(hdc2);
        WriteDays(hdc2, Left, Top - 200);

        ReleaseDC(hwnd, hdc2);
        EndPaint(hwnd, &ps);

        // Month++
        hBtnMonPlus = CreateWindow(TEXT("BUTTON"), TEXT("Month++"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               480, 640, 90, 40,
               hwnd,
               (HMENU)IDC_BTNMONPLUS,
               hInst, NULL);

        // Month--
        hBtnMonMinus = CreateWindow(TEXT("BUTTON"), TEXT("Month- -"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               370, 640, 90, 40,
               hwnd,
               (HMENU)IDC_BTNMONMINUS,
               hInst, NULL);

        // Year++
        hBtnYrPlus = CreateWindow(TEXT("BUTTON"), TEXT("Year++"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               250, 640, 100, 40,
               hwnd,
               (HMENU)IDC_BTNYRPLUS,
               hInst, NULL);

        // Year--
        hBtnYrMinus = CreateWindow(TEXT("BUTTON"), TEXT("Year- -"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               130, 640, 100, 40,
               hwnd,
               (HMENU)IDC_BTNYRMINUS,
               hInst, NULL);


        // Today
        hBtnToday = CreateWindow(TEXT("BUTTON"), TEXT("Today"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               10, 640, 100, 40,
               hwnd,
               (HMENU)IDC_BTNTODAY,
               hInst, NULL);

       // PLAN MONTH IT
        hBtnPlanIt = CreateWindow(TEXT("BUTTON"), TEXT("Plan It"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               600, 640, 100, 40,
               hwnd,
               (HMENU)IDC_BTNPLANIT,
               hInst, NULL);

       // Save
        hBtnSave = CreateWindow(TEXT("BUTTON"), TEXT("Save"),
               WS_CHILD | WS_VISIBLE |
               BS_PUSHBUTTON,
               780, 640, 100, 40,
               hwnd,
               (HMENU)IDC_BTNSAVE,
               hInst, NULL);

        MoveWindow(hEditDaily, 20, 80, 0, 0, TRUE);

        ReleaseDC(hwnd, hdc);
    }
}
 
char* t1_get_one(SQLHDBC con, string f2, string f3)
{
    SQLCHAR f1[6666];
    SQLHSTMT stmt;
    string sqlstr;
    int stat;
    /* get statement */
    sqlstr = "SELECT cont FROM t1 WHERE mnth = " + f2 + " and yr = " + f3;

    char* c = const_cast<char*>(sqlstr.c_str());

    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR *)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLBindCol(stmt, 1, SQL_C_CHAR, &f1, sizeof(f1), NULL);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* process result */
    stat = SQLFetch(stmt);

    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        other_exit("Row not found");
    }

    /* close statement */
    SQLCloseCursor(stmt);
    SQLFreeStmt(stmt, 0);

    std::string s((char*)f1);
    char* e = const_cast<char*>(s.c_str());
    return e;
}

void t1_put_one(SQLHDBC con, string f2, string f4, string f3)
{
    SQLCHAR f1[6666];
    SQLHSTMT stmt;
    string sqlstr;
    int stat;
    /* get statement */
    sqlstr = "SELECT cont FROM t1 WHERE mnth = " + f2 + " and yr = " + f4;

    char* c = const_cast<char*>(sqlstr.c_str());

    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR*)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLBindCol(stmt, 1, SQL_C_CHAR, &f1, sizeof(f1), NULL);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* process result */
    stat = SQLFetch(stmt);

    BOOL sx = TRUE;
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        sx = FALSE;
        other_exit("Row not found");
    }
    if(sx) {
    
        /* update statement */
        sqlstr = "UPDATE t1 SET cont = '"+f3+"' WHERE mnth = " + f2 + " and yr = " + f4.substr(0,4);

    } else {
        /* insert statement */
        sqlstr = "INSERT INTO t1 (cont, mnth, yr) VALUES ('"+f3+"', "+f2+"," + f4.substr(0,4) + ")";
    }
    c = const_cast<char*>(sqlstr.c_str());
    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR*)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* close statement */
    SQLCloseCursor(stmt);
    SQLFreeStmt(stmt, 0);
}

void t2_put_one(SQLHDBC con, string f2, string f4, string f3, string f5)
{
    SQLCHAR f1[6666];
    SQLHSTMT stmt;
    string sqlstr;
    int stat;
    /* get statement */
    sqlstr = "SELECT cont FROM t2 WHERE dy = " + f5 + " and mnth = " + f2 + " and yr = " + f4;

    char* c = const_cast<char*>(sqlstr.c_str());

    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR*)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLBindCol(stmt, 1, SQL_C_CHAR, &f1, sizeof(f1), NULL);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* process result */
    stat = SQLFetch(stmt);

    BOOL sx = TRUE;
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        sx = FALSE;
        
        other_exit("Row not found");
    }
    if(sx) {
    
        /* update statement */
        sqlstr = "UPDATE t2 SET cont = '"+f3+"' WHERE dy = " + f5 + " and mnth = " + f2 + " and yr = " + f4.substr(0,4);
        cout<<sqlstr;
    } else {
        /* insert statement */
        sqlstr = "INSERT INTO t2 (cont, mnth, yr, dy) VALUES ('"+f3+"', "+f2+"," + f4.substr(0,4) + ", " + f5 + ")";
    }
    c = const_cast<char*>(sqlstr.c_str());
    stat = SQLAllocStmt(con, &stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        con_exit(con);
    }

    stat = SQLPrepare(stmt, (SQLCHAR*)c, strlen(c));
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    stat = SQLExecute(stmt);
    if((stat != SQL_SUCCESS) && (stat != SQL_SUCCESS_WITH_INFO))
    {
        stmt_exit(stmt);
    }

    /* close statement */
    SQLCloseCursor(stmt);
    SQLFreeStmt(stmt, 0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    int iPage = TabCtrl_GetCurSel(hwndTab);

    hdc = GetDC(hwnd);
              
    switch(msg)
    {
       case WM_SIZE:
              cxClient = LOWORD(lParam);
              cyClient = HIWORD(lParam);

       case WM_COMMAND:
    
              switch (LOWORD(wParam))
              {
              case IDC_BTNMONPLUS: 

                     // Month++
                  if(iPage == 0) {
                     if (_YYYY < 2070)
                           _MM++;

                     if (_MM>12 && _YYYY < 2070)
                     {
                           _MM = 1;
                           _YYYY++;
                     }
                  char aa[100];sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,aa);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
                  } else if(iPage == 1) {

                     MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
      
                     if (_YYYY < 2070)
                           _MM++;

                     if (_MM>12 && _YYYY < 2070)
                     {
                           _MM = 1;
                           _YYYY++;
                     }

                    SetIsotropic(hdc, cxClient, cyClient);
                    ClearScreen(hdc);
                    Draw(hdc);
                    WriteDays(hdc, Left, Top - 200);

                    ReleaseDC(hwnd, hdc);
                            }
                     break;
              
              case IDC_BTNMONMINUS: 
              if(iPage == 0) {

                     // Month--
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);

                     if (_YYYY>1500)
                           _MM--;
                     if (_MM < 1 && _YYYY > 1500)
                     {
                           _MM = 12;
                           _YYYY--;
                     }
                  char aa[100];sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,aa);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
              } else if(iPage == 1) {

                     // Month--
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);

                     if (_YYYY>1500)
                           _MM--;
                     if (_MM < 1 && _YYYY > 1500)
                     {
                           _MM = 12;
                           _YYYY--;
                     }
                    
                    SetIsotropic(hdc, cxClient, cyClient);
                    ClearScreen(hdc);
                    Draw(hdc);
                    WriteDays(hdc, Left, Top - 200);

                    ReleaseDC(hwnd, hdc);
                    }
                     break;
             
              case IDC_BTNPREVDAY: {
                  _DD--;
                  char aa[100];sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,aa);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
                SQLHENV env;
                SQLHDBC dbc;
                SQLHSTMT stmt;
                SQLRETURN ret; /* ODBC API return status */
                SQLSMALLINT columns; /* number of columns in result-set */
                int row = 0;

                /* Allocate an environment handle */
                SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
                /* We want ODBC 3 support */
                SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
                /* Allocate a connection handle */
                SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
                /* Connect to the DSN mydsn */
                /* You will need to change mydsn to one you have created and tested */
                SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);
                /* Allocate a statement handle */
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

                std::string q = std::to_string(_DD);
                char* b = const_cast<char*>(q.c_str());
                std::string s = std::to_string(_MM);
                char* c = const_cast<char*>(s.c_str());
                std::string t = std::to_string(_YYYY);
                char* d = const_cast<char*>(t.c_str());
                char* str = t2_get_one(dbc, c, d, b);

                if(monthFirst) {
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
                    hEditDaily = CreateWindow(
                    TEXT("EDIT"), str,
                    WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
                    ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE  |
                    WS_VSCROLL | WS_HSCROLL,
                    20, 80, 1000, 540, hwndTab,
                    NULL, GetModuleHandle(NULL), NULL);
                    monthFirst = FALSE;
                } else {
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
                    MoveWindow(hEditDaily, 20, 80, 1000, 540, TRUE);
                }
                SetWindowText(hEditDaily, str);
                  break;
              }
              case IDC_BTNNEXTDAY: {
                  _DD++;
                  char bb[100];sprintf(bb,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,bb);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
                SQLHENV env;
                SQLHDBC dbc;
                SQLHSTMT stmt;
                SQLRETURN ret; /* ODBC API return status */
                SQLSMALLINT columns; /* number of columns in result-set */
                int row = 0;

                /* Allocate an environment handle */
                SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
                /* We want ODBC 3 support */
                SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
                /* Allocate a connection handle */
                SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
                /* Connect to the DSN mydsn */
                /* You will need to change mydsn to one you have created and tested */
                SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);
                /* Allocate a statement handle */
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

                std::string q = std::to_string(_DD);
                char* b = const_cast<char*>(q.c_str());
                std::string s = std::to_string(_MM);
                char* c = const_cast<char*>(s.c_str());
                std::string t = std::to_string(_YYYY);
                char* d = const_cast<char*>(t.c_str());
                char* str = t2_get_one(dbc, c, d, b);
        
                if(monthFirst) {
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
                    hEditDaily = CreateWindow(
                    TEXT("EDIT"), str,
                    WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
                    ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE  |
                    WS_VSCROLL | WS_HSCROLL,
                    20, 80, 700, 540, hwndTab,
                    NULL, GetModuleHandle(NULL), NULL);
                    monthFirst = FALSE;
                } else {
                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);
                    MoveWindow(hEditDaily, 20, 80, 1000, 540, TRUE);
                }
                SetWindowText(hEditDaily, str);

                 break;
              }
              case IDC_BTNYRPLUS: 
                  if(iPage == 0) {
                     if (_YYYY < 2070)
                           _YYYY++;
                      
                  char aa[100];sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,aa);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
                  } else if(iPage == 1) {

                     // Year++

                     if (_YYYY < 2070)
                           _YYYY++;

              SetIsotropic(hdc, cxClient, cyClient);
              ClearScreen(hdc);
              Draw(hdc);
              WriteDays(hdc, Left, Top - 200);

              ReleaseDC(hwnd, hdc);
              }
                     break;
              
              case IDC_BTNYRMINUS: 
                  if(iPage == 0) {
                     if (_YYYY > 1500)
                           _YYYY--;
                  char aa[100];sprintf(aa,"%d-%d-%d",_MM,_DD,_YYYY);
                  SetWindowTextA(hwndMain,aa);
                  ShowWindow(hwndMain, nc);
                  UpdateWindow(hwndMain);
                  } else if(iPage == 1) {

                     // Year--

                     if (_YYYY > 1500)
                           _YYYY--;

              SetIsotropic(hdc, cxClient, cyClient);
              ClearScreen(hdc);
              Draw(hdc);
              WriteDays(hdc, Left, Top - 200);

              ReleaseDC(hwnd, hdc);
              }
                    break;
              
              case IDC_BTNTODAY: 
              if(iPage == 1) {

                     // Today

                    MoveWindow(hEdit, 20, 80, 0, 0, TRUE);

                    Init();


              SetIsotropic(hdc, cxClient, cyClient);
              ClearScreen(hdc);
              Draw(hdc);
              WriteDays(hdc, Left, Top - 200);

              ReleaseDC(hwnd, hdc);
              }
                     break;
              
              case IDC_BTNPLANIT: {
              if(iPage == 1) {
 
                // Plan It (Month)

                SQLHENV env;
                SQLHDBC dbc;
                SQLHSTMT stmt;
                SQLRETURN ret; /* ODBC API return status */
                SQLSMALLINT columns; /* number of columns in result-set */
                int row = 0;

                /* Allocate an environment handle */
                SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
                /* We want ODBC 3 support */
                SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
                /* Allocate a connection handle */
                SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
                /* Connect to the DSN mydsn */
                /* You will need to change mydsn to one you have created and tested */
                SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);
                /* Allocate a statement handle */
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

                std::string s = std::to_string(_MM);
                char* c = const_cast<char*>(s.c_str());
                std::string t = std::to_string(_YYYY);
                char* d = const_cast<char*>(t.c_str());
                char* str = t1_get_one(dbc, c, d);

                HBRUSH yellow_brush = CreateSolidBrush(RGB(240,169,40));
                RECT rrect = {0, 20, 4540, 740};
                FillRect(hdc, &rrect, yellow_brush);
                DeleteObject(yellow_brush);
                
                _sleep(413);

                if(monthFirst) {
                    MoveWindow(hEditDaily, 20, 80, 0, 0, TRUE);
                    hEdit = CreateWindow(
                    TEXT("EDIT"), str,
                    WS_CHILD | WS_VISIBLE | ES_LEFT | ES_WANTRETURN |
                    ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE  |
                    WS_VSCROLL | WS_HSCROLL,
                    20, 80, 1000, 540, hwnd,
                    NULL, GetModuleHandle(NULL), NULL);
                    monthFirst = FALSE;
                    HFONT hFont=CreateFont(0,22,0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));
                    SendMessage(hEdit,WM_SETFONT,(WPARAM)hFont,0);
                } else {
                    MoveWindow(hEditDaily, 20, 80, 0, 0, TRUE);
                    MoveWindow(hEdit, 20, 80, 1000, 540, TRUE);
                }

                ShowWindow(hEdit, SW_SHOW);
                
                SetWindowText(hEdit, str);
                
                ReleaseDC(hwnd, hdc);
              }
                break;
              }
              case IDC_BTNSAVE: {
              if(iPage == 1) {

                // Save (Content)

                SelectObject(hdc, GetStockObject(GRAY_BRUSH));
                Rectangle(hdc, 1000, 340, 1000, 1360);

                SQLHENV env;
                SQLHDBC dbc;
                SQLHSTMT stmt;
                SQLRETURN ret; /* ODBC API return status */
                SQLSMALLINT columns; /* number of columns in result-set */
                int row = 0;

                /* Allocate an environment handle */
                SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
                /* We want ODBC 3 support */
                SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
                /* Allocate a connection handle */
                SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
                /* Connect to the DSN mydsn */
                /* You will need to change mydsn to one you have created and tested */
                SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);
                /* Allocate a statement handle */
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

                std::string s = std::to_string(_MM);
                std::string t = std::to_string(_YYYY);
     
                int len = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
                string conte;
                char *dd=(char*)malloc(len+1);
                SendMessage(hEdit, WM_GETTEXT, (WPARAM)len+1, (LPARAM)dd);
                
                conte = dd;
                
                t1_put_one(dbc, s, t, conte);

                ReleaseDC(hwnd, hdc);
              }
              else if(iPage == 0) {

                // Save (Fontent)

                SelectObject(hdc, GetStockObject(GRAY_BRUSH));
                Rectangle(hdc, 1000, 340, 1000, 1360);

                SQLHENV env;
                SQLHDBC dbc;
                SQLHSTMT stmt;
                SQLRETURN ret; /* ODBC API return status */
                SQLSMALLINT columns; /* number of columns in result-set */
                int row = 0;

                /* Allocate an environment handle */
                SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
                /* We want ODBC 3 support */
                SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
                /* Allocate a connection handle */
                SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
                /* Connect to the DSN mydsn */
                /* You will need to change mydsn to one you have created and tested */
                SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=mydsn;", SQL_NTS,
                                 NULL, 0, NULL, SQL_DRIVER_COMPLETE);
                /* Allocate a statement handle */
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

                std::string s = std::to_string(_MM);
                std::string t = std::to_string(_YYYY);
                std::string d = std::to_string(_DD);
     
                int len = SendMessage(hEditDaily, WM_GETTEXTLENGTH, 0, 0);
                string conte;
                char *dd=(char*)malloc(len+1);
                SendMessage(hEditDaily, WM_GETTEXT, (WPARAM)len+1, (LPARAM)dd);
                
                conte = dd;
                
                t2_put_one(dbc, s, t, conte, d);

                ReleaseDC(hwnd, hdc);
              }
                break;
              }
            }          
            case WM_CREATE: 
              hBitmap = (HBITMAP)LoadImage(hInst, "logo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

              SetIsotropic(hdc, cxClient, cyClient);
              SetTimer(hwnd, ID_TIMER, 1000, NULL);

            
              // Month++
              hBtnMonPlus = CreateWindow(TEXT("BUTTON"), TEXT("Month++"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     480, 640, 90, 40,
                     hwnd,
                     (HMENU)IDC_BTNMONPLUS,
                     hInst, NULL);

              // Month--
              hBtnMonMinus = CreateWindow(TEXT("BUTTON"), TEXT("Month- -"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     370, 640, 90, 40,
                     hwnd,
                     (HMENU)IDC_BTNMONMINUS,
                     hInst, NULL);

              // Year++
              hBtnYrPlus = CreateWindow(TEXT("BUTTON"), TEXT("Year++"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     250, 640, 100, 40,
                     hwnd,
                     (HMENU)IDC_BTNYRPLUS,
                     hInst, NULL);

              // Year--
              hBtnYrMinus = CreateWindow(TEXT("BUTTON"), TEXT("Year- -"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     130, 640, 100, 40,
                     hwnd,
                     (HMENU)IDC_BTNYRMINUS,
                     hInst, NULL);


              // Today
              hBtnToday = CreateWindow(TEXT("BUTTON"), TEXT("Today"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     10, 640, 100, 40,
                     hwnd,
                     (HMENU)IDC_BTNTODAY,
                     hInst, NULL);

             // PLAN MONTH IT
              hBtnPlanIt = CreateWindow(TEXT("BUTTON"), TEXT("Plan It"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     600, 640, 100, 40,
                     hwnd,
                     (HMENU)IDC_BTNPLANIT,
                     hInst, NULL);

             // Save
              hBtnSave = CreateWindow(TEXT("BUTTON"), TEXT("Save"),
                     WS_CHILD | WS_VISIBLE |
                     BS_PUSHBUTTON,
                     780, 640, 100, 40,
                     hwnd,
                     (HMENU)IDC_BTNSAVE,
                     hInst, NULL);

              ReleaseDC(hwnd, hdc);
              break;
        
       case WM_TIMER: 
                if(fist) {
                   CloseWindows();
                   hdc = GetDC(hwnd);
                   SetIsotropic(hdc, cxClient, cyClient);
                   ClearScreen(hdc);
                   Draw(hdc);
                   WriteDays(hdc, Left, Top - 200);
                   ReleaseDC(hwnd, hdc);
                   fist = FALSE;
                }
                break;
       
       case WM_PAINT: 
           CloseWindows();
           if(fist) {
            hdc = BeginPaint(hwnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);

            oldBitmap = SelectObject(hdcMem, hBitmap);

            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, 0, 0, 1740, 740, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oldBitmap); DeleteObject(oldBitmap); DeleteObject(hdcMem);
            DeleteDC(hdcMem); DeleteObject(hBitmap);

            Sleep(4500);

              SetIsotropic(hdc, cxClient, cyClient);
              Init();
              Draw(hdc);
              WriteDays(hdc, Left, Top-200);

              EndPaint(hwnd, &ps);
           } else {
              hdc = BeginPaint(hwnd, &ps);
              SetIsotropic(hdc, cxClient, cyClient);
             
              Draw(hdc);
              WriteDays(hdc, Left, Top-200);

              EndPaint(hwnd, &ps);
           }
            break;
       
        case WM_CLOSE: 
            DestroyWindow(hwnd);
            break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_NOTIFY: 
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                { 
                    int iPage = TabCtrl_GetCurSel(hwndTab);
                    CloseWindows();
                    if(iPage == 0)
                        MakeWindow(0, hwnd, lParam);
                    if(iPage == 1) {
                        MakeWindow(1, hwnd, lParam);
                    }
                    break;
                } 
            }
            break;
        
        default: 
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    MSG Msg;
    hinst=hInstance;
 
 
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
 
    RegisterClassEx(&wc);
 
 
    hwndMain = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "myWindowClass",
        "Calendar Planner",
        WS_OVERLAPPEDWINDOW,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);
 
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwndMain, GWL_STYLE) & ~WS_MINIMIZEBOX);
 
    ShowWindow(hwndMain, nCmdShow);
    UpdateWindow(hwndMain);
    InitCommonControls();
    hwndTab=CreateWindowEx(0, 
                "SysTabControl32", 
                "",
                WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,
                0, 0, 
                GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
                hwndMain, 
                NULL, 
                hInstance, 
                NULL); 
 
    TCITEM tie;
    tie.mask = TCIF_TEXT; 
    tie.pszText = "D a i l y"; 
    TabCtrl_InsertItem(hwndTab, 0, &tie);
 
    tie.mask = TCIF_TEXT; 
    tie.pszText = "Month ly"; 
    TabCtrl_InsertItem(hwndTab, 1, &tie);

    TabCtrl_SetCurSel(hwndTab, 1);
    ShowWindow(hwndTab, SW_SHOW);
    UpdateWindow(hwndTab);
 
    WNDCLASSEX wcx;
    wcx.cbSize        = sizeof(WNDCLASSEX);
    wcx.style         = 0;
    wcx.lpfnWndProc   = ChildrenProc;
    wcx.cbClsExtra    = 0;
    wcx.cbWndExtra    = 0;
    wcx.hInstance     = hInstance;
    wcx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcx.lpszMenuName  = NULL;
    wcx.lpszClassName = "TabChild";
    wcx.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
 
    nc = nCmdShow;
    
    RegisterClassEx(&wcx);
 
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}