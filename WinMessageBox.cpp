#include <iostream>
#include <sstream>
#include <wchar.h>
#include <windows.h>
using namespace std;

/*
    Written by davidhcefx, 2019.9.27.
    Button: { OK: 0x0, OKCancel: 0x1, YesNo: 0x4, YesNoCancel: 0x3 }
    Icon: { Information: 0x40, None: 0x00, Question: 0x20, Stop: 0x10, Warning: 0x30 }
    ReturnVal: { Fail: 0, OK: 1, Cancel: 2, Yes: 6, No: 7 }
    Ref: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
*/

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Syntax: messagebox <Title> <Msg> (Button) (Icon)\n";
        cout << "\tButton  =  ok | okcancel | yesno | yesnocancel (default=ok)\n";
        cout << "\tIcon    =  info | ques | stop | warn (default=info)\n";
        cout << "\t(Multi-byte characters are not supported)\n";
        cout << "Return: 0 = fail, 1 = ok, 2 = cancel, 6 = yes, 7 = no.\n";
        return 0;
    } else {
        // Warning: This method cannot deal with multibyte characters.
        wstringstream ss;
        ss << argv[1];
        wstring title = ss.str();
        ss.clear(), ss.str(L"");
        ss << argv[2];
        wstring msg = ss.str();

        unsigned int type = 0x40;
        if (argc >= 4) {
            string str(argv[3]);
            if (str == "okcancel") {
                type |= 0x1;
            } else if (str == "yesno") {
                type |= 0x4;
            } else if (str == "yesnocancel") {
                type |= 0x3;
            }
        }
        if (argc >= 5) {
            string str(argv[4]);
            if (str == "ques") {
                type = (type & 0x0f) | 0x20;
            } else if (str == "stop") {
                type = (type & 0x0f) | 0x10;
            } else if (str == "warn") {
                type = (type & 0x0f) | 0x30;
            }
        }
        return MessageBoxW(NULL, (LPCWSTR)msg.c_str(), (LPCWSTR)title.c_str(), type);
    }
}
