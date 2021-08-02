#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <dlfcn.h>

#if defined(__ARM_ARCH_7A__) //! armeabi-v7a
DWORD CreateString_offset = 0x0; // private unsafe string CreateString(sbyte* value)
#elif defined(__i386__) //! x86
DWORD CreateString_offset = 0x0; // private unsafe string CreateString(sbyte* value)
#elif defined(__aarch64__) //! arm64-v8a
DWORD CreateString_offset = 0x0; // private unsafe string CreateString(sbyte* value)
#else //! ?????
DWORD CreateString_offset = 0x0; // private unsafe string CreateString(sbyte* value)
#endif

struct monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[255];

    std::string get_string() {
        std::u16string u16_string(reinterpret_cast<const char16_t *>(chars));
        std::wstring wide_string(u16_string.begin(), u16_string.end());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        return convert.to_bytes(wide_string);
    }

    void set(std::string str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        std::wstring wa = convert.from_bytes(str);
        length = str.length();
        std::u16string basicString = std::u16string(wa.begin(), wa.end());
        const char16_t *cStr = basicString.c_str();
        memcpy(getChars(), cStr, getLength() * 2);
    }

    const char *get_const_char() {
        return get_string().c_str();
    }

    char *getChars() {
        return chars;
    }

    int getLength() {
        return length;
    }

};

monoString * CreateMonoString(const char *str, bool il2cpp = true) {
    void *h = nullptr;
    while (!h) {
        h = dlopen("libil2cpp.so", 4);
    }
    if (!il2cpp) {
        monoString *(*String_CreateString)(void *, const char *);
        *(void **) (&String_CreateString) = (void *) ((DWORD) h + CreateString_offset);
        return String_CreateString(NULL, str);
    } else {
        monoString *(*CreateIl2CppString_t)(const char *);
        do {
            CreateIl2CppString_t = (monoString *(*)(const char *)) dlsym(h, "il2cpp_string_new_wrapper");
        } while (!CreateIl2CppString_t);
        return CreateIl2CppString_t(str);
    }
}