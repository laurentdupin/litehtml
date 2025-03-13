#ifndef DLLMAIN_H
#define DLLMAIN_H

#include <string>

enum class LiteHTMLDrawCallType : int { NONE = 0, TEXT, IMAGE };

struct LiteHTMLDrawCall 
{
    LiteHTMLDrawCallType DrawCallType = LiteHTMLDrawCallType::NONE;
    std::string Text = "";
};

#endif  // DLLMAIN_H