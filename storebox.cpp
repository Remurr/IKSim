#include "storebox.h"

namespace
{
    Storebox s_Inst;
}

Storebox& Storebox::Inst() { return s_Inst; }