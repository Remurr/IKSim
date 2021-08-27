#include "playground_storage.h"

namespace
{
    PlaygroundStorage s_Inst;
}

PlaygroundStorage& PlaygroundStorage::Inst() { return s_Inst; }