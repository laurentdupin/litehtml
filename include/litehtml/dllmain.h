#ifndef DLLMAIN_H
#define DLLMAIN_H

#include <string>
#include <memory>

enum class LiteHTMLDrawCallType : int { NONE = 0, TEXT, IMAGE };

struct LiteHTMLDrawCall 
{
    LiteHTMLDrawCallType DrawCallType = LiteHTMLDrawCallType::NONE;
    const char *Text = "";
};

#endif  // DLLMAIN_H