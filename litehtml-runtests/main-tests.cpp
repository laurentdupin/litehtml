#include <Windows.h>
#include <fstream>
#include <vector>

#include "../include/litehtml/dllmain.h"

typedef int (*GenerateDrawCallsType)(const char* contextname, const char *page, const char* css, int width, int height, int clipx, int clipy, int clipwidth, int clipheight);
typedef int (*CreateLiteHTMLContextType)(const char *contextname);
typedef int (*DeleteLiteHTMLContextType)(const char *contextname);
typedef int (*ClearFontsFromContextType)(const char* contextname);
typedef int (*AddFontToContextType)(const char *contextname, const char *font);
typedef LiteHTMLDrawCall* (*GetDrawCallType)(const char *contextname, int callindex);

int main()
{
    HMODULE hdll = LoadLibrary(L"litehtml.dll");
    
    if (hdll != 0)
    {
        std::ifstream htmlstream("Ex1.html");
        std::string htmlcontents((std::istreambuf_iterator<char>(htmlstream)), std::istreambuf_iterator<char>());

        std::ifstream cssstream("Ex1.css");
        std::string csscontents((std::istreambuf_iterator<char>(cssstream)), std::istreambuf_iterator<char>());

        auto GenerateDrawCalls = (GenerateDrawCallsType)GetProcAddress(hdll, "GenerateDrawCalls");
        auto CreateLiteHTMLContext = (CreateLiteHTMLContextType)GetProcAddress(hdll, "CreateLiteHTMLContext");
        auto DeleteLiteHTMLContext = (DeleteLiteHTMLContextType)GetProcAddress(hdll, "DeleteLiteHTMLContext");
        auto ClearFontsFromContext = (ClearFontsFromContextType)GetProcAddress(hdll, "ClearFontsFromContext");
        auto AddFontToContext = (AddFontToContextType)GetProcAddress(hdll, "AddFontToContext");
		auto GetDrawCall = (GetDrawCallType)GetProcAddress(hdll, "GetDrawCall");

        CreateLiteHTMLContext("DefaultContext");
		GenerateDrawCalls("DefaultContext", htmlcontents.c_str(), csscontents.c_str(), 1280, 720, 0, 0, 1280, 720);

        for (int i = 0; ; ++i)
        {
            auto drawcallptr = GetDrawCall("DefaultContext", i);

			if (drawcallptr == NULL)
            {
                break;
            }

            printf("%s\n", drawcallptr->Text.c_str());
        }

		DeleteLiteHTMLContext("DefaultContext");
    }
    else 
    {
	    return 1;
    }
	    
    return 0;
}