#include <Windows.h>
#include <fstream>

typedef int (*InitCaptureType)(const char *, const char *);

int main()
{
    HMODULE hdll = LoadLibrary(L"litehtml.dll");
    
    if (hdll != 0)
    {
        std::ifstream htmlstream("Ex1.html");
        std::string htmlcontents((std::istreambuf_iterator<char>(htmlstream)), std::istreambuf_iterator<char>());

        std::ifstream cssstream("Ex1.css");
        std::string csscontents((std::istreambuf_iterator<char>(cssstream)), std::istreambuf_iterator<char>());

        auto GenerateDrawCalls = (InitCaptureType)GetProcAddress(hdll, "GenerateDrawCalls");
		GenerateDrawCalls(htmlcontents.c_str(), csscontents.c_str());
    }
    else 
    {
	    return 1;
    }
	    
    return 0;
}