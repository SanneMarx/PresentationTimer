#ifndef _DISPLAY_INTERFACE_H_
#define _DISPLAY_INTERFACE_H_

#ifdef ESP8266
    #include "PxMatrix.h"
    class Display: public PxMATRIX{
        using PxMATRIX::PxMATRIX;
    };
#else
    #include "x86Display.h"
    class Display: public X86Display{

    };
#endif

#endif