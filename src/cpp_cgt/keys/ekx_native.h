#pragma once

#include "ek_native.h"
#include "e3util.h"

class NativeEvalKeyExt : public NativeEvalKey
{
    public:
        NativeEvalKeyExt(std::string name) : NativeEvalKey(User::Alice, name) {}

        void save();
        using NativeEvalKey::key;
};
