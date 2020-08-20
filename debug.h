#pragma once

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <cstdlib>
#include "sequence.h"

#define PAUSE 

class Debug {
public:
    static void SetEncoding(String _encoding, const bool _isClear)
    {
        String command = "chcp ";
        if (_encoding == "UTF-8" || _encoding == "utf-8")
        {
            command += "65001 ";
        }
        else if (_encoding == "GBK" || _encoding == "gbk")
        {
            command += "936 ";
        }
        
        if (_isClear)
        {
            command += "& cls";
        }

        system(command.c_str());
    }

    static void SetEncoding(const char *_encoding, const bool _isClear = true)
    {
        SetEncoding(String(_encoding), _isClear);
    }

    inline static void Pause()
    {
        system("pause");
    }

};



#endif
