#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

const string CHROME = "Google Chrome";
const string GOOGLE = "Google - Google Chrome";
const string FIREFOX = "Firefox";
const string IE = "Internet Explorer";

   vector<string> explode( const string &str, const string &delimiter)
    {
        vector<string> arr;

        int strleng = str.length();
        int delleng = delimiter.length();
        if (delleng==0)
            return arr;

        int i=0;
        int k=0;
        while( i<strleng )
        {
            int j=0;
            while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
                j++;
            if (j==delleng)
            {
                arr.push_back(  str.substr(k, i-k) );
                i+=delleng;
                k=i;
            }
            else
            {
                i++;
            }
        }
        arr.push_back(  str.substr(k, i-k) );
        return arr;
    }

    string GetActiveWindowTitle()
    {
        char wnd_title[256];
        HWND hwnd=GetForegroundWindow();
        GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
        return wnd_title;
    }

    void letspress_a_letter()
    {
        INPUT ip;
        // Set up a generic keyboard event.
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0; // hardware scan code for key
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Press the "A" key
        ip.ki.wVk = 0x41; // virtual-key code for the "a" key
        ip.ki.dwFlags = 0; // 0 for key press
        SendInput(1, &ip, sizeof(INPUT));

        // Release the "A" key
        ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
        SendInput(1, &ip, sizeof(INPUT));
    }

int main() 
{
    cout << "Driver iniciado" << endl;
    string delimitador = " - ";
    while(true)
    {
        Sleep(1000);
        string telaAtual = GetActiveWindowTitle();

        if( telaAtual.length() > 0 && explode(telaAtual,delimitador).back() == CHROME)
        {
            if(telaAtual == GOOGLE)
            {
                letspress_a_letter();
                cout << "Agra sim.. "<< endl;
            }
            cout << telaAtual<<endl;
            //cout << "Verificando Crachá RFID"<<endl;
        }
        // else{cout << "Nenhum programa aberto."<< endl;}
    }
    return 0;
}