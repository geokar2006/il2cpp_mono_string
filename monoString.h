#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <dlfcn.h>

typedef struct _monoString {
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

    void create(const char *s) {
        std::string str = std::string(s);
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        std::wstring wa = convert.from_bytes(str);
        length = str.length();
        std::u16string basicString = std::u16string(wa.begin(), wa.end());
        const char16_t *cStr = basicString.c_str();
        memcpy(getChars(), cStr, getLength() * 2);
    }

    void create(std::string str) {
        create(str.c_str());
    }

    static _monoString *New(const char *str) {
        _monoString *s = (_monoString *) calloc(1, (sizeof(_monoString) + ((strlen(str) + 1) * 2)));
        s->create(str);
        return s;
    }

    static _monoString *New(std::string str) {
        return New(str.c_str());
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

} monoString;

monoString *
CreateMonoString(const char *str,
                 bool il2cpp = true) { //private unsafe string CreateString(sbyte* value)
    if (!il2cpp) {
        monoString *(*String_CreateString)(void *instance, const char *str);
#ifdef __arm__ //armeabi-v7a
        String_CreateString = (monoString *(*)(void *,
                                               const char *)) getAbsoluteAddress(
                libName, 0x0);
#elif defined(__i386__) //x86
        String_CreateString = (monoString *(*)(void *,
                const char *)) getAbsoluteAddress(
                libName, 0x0);
#elif defined(__aarch64__) //arm64-v8a
        String_CreateString = (monoString *(*)(void *, const char *)) getAbsoluteAddress(libName, 0x0);
#endif
        return String_CreateString(NULL, str);
    } else {
        monoString *(*CreateIl2CppString_t)(const char *) = nullptr;
        void *h = nullptr;
        while (!h) {
            h = dlopen("libil2cpp.so", 4);
        }
        do {
            CreateIl2CppString_t = (monoString *(*)(const char *)) dlsym(h, "il2cpp_string_new");
        } while (!CreateIl2CppString_t);
        return CreateIl2CppString_t(str);
    }
    return 0;
}

monoString *CreateMonoString(std::string str, bool il2cpp = true) {
    return CreateMonoString(str.c_str(), il2cpp);
}