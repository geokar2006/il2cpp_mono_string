#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <dlfcn.h>

#define ALLOC_PTRFREE(obj, vt, size) do { (obj) = (_monoString*)malloc ((size)); (obj)->klass = (vt); (obj)->monitor = NULL;} while (0)

struct _monoString;
typedef struct {
    _monoString *string_class;
} Il2CppDefaults_string;
Il2CppDefaults_string il2cpp_defaults;
typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[32];

    std::string get_string() {
        std::u16string u16_string(reinterpret_cast<const char16_t *>(getChars()));
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
        _monoString *s;
        size_t size = (sizeof(_monoString) + ((strlen(str) + 1) * 2));
        ALLOC_PTRFREE(s, il2cpp_defaults.string_class, size);
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

monoString *(*CreateIl2CppString_t)(const char *);

void load_il2cpp_string() {
    void *h = nullptr;
    while (!h) {
        h = dlopen("libil2cpp.so", 4);
    }
    CreateIl2CppString_t = nullptr;
    do {
        CreateIl2CppString_t = (monoString *(*)(const char *)) dlsym(h, "il2cpp_string_new");
    } while (!CreateIl2CppString_t);
}

monoString *CreateIl2CppString(const char *str) {
    if (CreateIl2CppString_t == nullptr) load_il2cpp_string();
    return CreateIl2CppString_t(str);
}

monoString *CreateIl2CppString(std::string str) {
    return CreateIl2CppString(str.c_str());
}

monoString *CreateMonoString(const char *str) { //private unsafe string CreateString(sbyte* value)
#ifdef __arm__ //armeabi-v7a
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *,
                                                                                           const char *)) getAbsoluteAddress(
            libName, 0x0);
#elif defined(__i386__) //x86
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *,
                                                                                           const char *)) getAbsoluteAddress(
            libName, 0x0);
#elif defined(__aarch64__) //arm64-v8a
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *, const char *)) getAbsoluteAddress(libName, 0x0);
#endif
    return String_CreateString(NULL, str);
}

monoString *CreateMonoString(std::string str) {
    return CreateMonoString(str.c_str());
}
