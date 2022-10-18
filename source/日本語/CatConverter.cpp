//=============================================================================================
/**
 * @brief   CatConverter
 * @author  NekoSuzu@DonutSuZu
 * @date    2022.10.18
 */
//=============================================================================================
using namespace std;
//=============================================================================================
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <ostream>
#include <sstream> // std::stringstream
//=============================================================================================
std::string counter; //input


//G++ -finput-charset=UTF-8 -fexec-charset=CP932 main.cpp -o CatConverter

//G++ main.cpp -o CatConverter
//build:G++ CatConverter.cpp
// クリップボードにテキストデータをコピーする関数
BOOL SetClipboardText( const char *Str )
{
	int    BufSize;
	char  *Buf;
	HANDLE hMem;

	BufSize = strlen( Str ) + 1;                               // 確保するメモリのサイズを計算する
	hMem = GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, BufSize ); // 移動可能な共有メモリを確保する
	if ( !hMem ) return FALSE;

	Buf = (char *)GlobalLock( hMem ); // 確保したメモリをロックし，アクセス可能にする
	if ( Buf )
	{
		strcpy( Buf, Str );   // 文字列を複写する
		GlobalUnlock( hMem ); // メモリのロックを解除する
		if ( OpenClipboard(NULL) )
		{
			EmptyClipboard();                  // クリップボード内の古いデータを解放する
			SetClipboardData( CF_TEXT, hMem ); // クリップボードに新しいデータを入力する
			CloseClipboard();

			return TRUE;
		}
	}
	return FALSE;
}
//=============================================================================================
//Read include
int Line = 0;
std::string Data[1000000];
//
//Gen
std::string NamePoint;//success
std::string ADD,CON,OFF;
int Line2 = 0;
unsigned int CX;
unsigned int Cc;
std::stringstream ss;
const char *buffer;
std::string VLand;
//
//CODE only
void CODEGEN()
{
	while(1)
	{
		ADD = Data[0 + 2*Line2].substr(0, 2);
		while(1)
		{
			//@Offset 32bit
			if(ADD == "D3")
			{
				
				//printf("OFFset Name:");
				//cin >> CON; //Load
				//printf("\n");
				//NamePoint += "u32 " + CON + " = " + "0x" + Data[1 + 2*Line2] + ";\n";
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
			//@Offset 32bit
			if(ADD == "00")
			{
				//offset conv
				const std::string SS = OFF; //@offset
				const std::string SSS = Data[0 + 2*Line2];	//
				ss.str("");
				// 状態をクリアします。
				ss.clear(std::stringstream::goodbit);
				sscanf(SS.c_str()  , "%x", &CX); //16進へ
				sscanf(SSS.c_str()  , "%x", &Cc); //16進へ
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				unsigned int ssss = CX+Cc;
				ss << std::hex << ssss; //文字列へ
				VLand = ss.str();
				//
				NamePoint += "Process::White32(0x" + VLand + ",";
				break;
			}
			if(ADD == "D2")
			{
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
			//exit
			if(ADD == "#C")
			{
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
		}
		while(1)
		{
			//@Value
			//exit
			if(ADD == "D3")
			{
				//NamePoint += "u32 " + CON + " = " + "0x" + Data[1 + 2*Line2] + ";\n";
				OFF = Data[1 + 2*Line2];
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
			if(ADD == "00")
			{
				NamePoint += "0x" + Data[1 + 2*Line2] + ")" + ";\n";

				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
			if(ADD == "D2")
			{
				//std::cout << "DEV\n" << NamePoint << "\n"; //dev
				break;
			}
			//exit
			if(ADD == "#C")
			{
				break;
			}
		}
		//exit
		if(ADD == "#C")
		{
			NamePoint += "\n";
			NamePoint += "}";
			NamePoint += "\n";
			NamePoint += "変換したよ! by Cat Converter ny ねこ鈴.";
			NamePoint += "\n";
			//std::cout << "DEV\n" << NamePoint << "\n"; //dev
			buffer = NamePoint.c_str();
			SetClipboardText(buffer);
			printf("くクリップボードへコピーしました！\n");
			printf("完了！\n");
			//reset
			Line = 0;
			for(int y = 0;y < 1000000,y++;)
			{
				Data[y] = "";
			}
			//
			//Gen
			NamePoint = "";//success
			ADD = "";
			CON = "";
			OFF = "";
			Line2 = 0;
			CX = 0;
			Cc = 0;
			// バッファをクリアします。
			ss.str("");
			// 状態をクリアします。
			ss.clear(std::stringstream::goodbit);
			buffer = 0;
			VLand = "";
			break;
		}			
		CX = 0;
		Cc = 0;
		Line2++;
	}
}
//Core
int main()
{
	const char *fileName = "./Code.txt";
	std::ofstream ofs(fileName);
    if (!ofs)
    {
        std::cout << "開けなかった..." << std::endl;
        std::cin.get();
        return 0;
    }
	while(1)
	{
		HWND active_win= GetForegroundWindow();
		SetWindowPos(active_win, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | NULL);
		printf("OpenCat-Dev.Nekosuzu ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | NULL);
		printf("Cat Converter ベータ版 \n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | NULL | NULL);
		printf("コードを入力する方法! \n");
		//plus Entry point
		//printf("\n");		
		printf("a:テキストファイルから開く!(未実施)\n");
		printf("b:キーボードで入力する\n");
		//Plus entry point↑
		printf("選ぶ((aかb)エンターキーで決定):");
		cin >> counter;
		printf("\n");
		if(counter == "a")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | NULL);
			printf("未実施\n");
			//text Load
		}
		if(counter == "b")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | NULL);
			std::string HEX;	//Stream
			std::string NameHEX;	//Stream
			//Name
			std::string Name0 = "void ";
			std::string Name2 = "(MenuEntry *entry){ \n";
			std::string Name4;
			Name4 = "}";
			//End
			
			//input
			
			printf("名前:");
			cin >> NameHEX; //Load
			printf("\n");
			NamePoint += Name0 + NameHEX  + Name2;
			//std::cout << "DEV\n" << NamePoint << "\n"; //dev
			printf("コード:");
			cin >> HEX; //Load
			printf("\n");
			
			while(1)
			{
				//MODE Read@XXXXXXXX 00000000
				Data[Line] = HEX.substr(0 + Line*8, 8); //0 = ADD , 1= Value.*
				//std::cout << "DEV\n" << Data[Line] << "\n"; //dev
				if(Data[Line].length() != 8)
				{
					NamePoint = "";//success
					printf("エラー(コードが不正です!)\n");
					break;
				}
				//std::cout << "DEV\n" << Data[Line] << "\n"; //dev
				if(Data[Line] == "#CODEEND")
				{
					CODEGEN();//EntryPoint ++
					break; //ReadEnd
				}
				Line++;
			}
		}
	}
}