#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <sstream>
#include <dlfcn.h>

#define ALLOC_PTRFREE(obj, vt, size) do { (obj) = (_monoString*)malloc ((size)); (obj)->klass = (vt); (obj)->monitor = NULL;} while (0)

struct _monoString;
typedef struct Il2CppDefaults_str{
    void *corlib;
    void *object_class;
    void *byte_class;
    void *void_class;
    void *boolean_class;
    void *sbyte_class;
    void *int16_class;
    void *uint16_class;
    void *int32_class;
    void *uint32_class;
    void *int_class;
    void *uint_class;
    void *int64_class;
    void *uint64_class;
    void *single_class;
    void *double_class;
    void *char_class;
    void *string_class;
    void *enum_class;
    void *array_class;
    void *delegate_class;
    void *multicastdelegate_class;
    void *asyncresult_class;
    void *manualresetevent_class;
    void *typehandle_class;
    void *fieldhandle_class;
    void *methodhandle_class;
    void *systemtype_class;
    void *monotype_class;
    void *exception_class;
    void *threadabortexception_class;
    void *thread_class;
    void *internal_thread_class;
    void *appdomain_class;
    void *appdomain_setup_class;
    void *field_info_class;
    void *method_info_class;
    void *property_info_class;
    void *event_info_class;
    void *mono_event_info_class;
    void *stringbuilder_class;
    void *stack_frame_class;
    void *stack_trace_class;
    void *marshal_class;
    void *typed_reference_class;
    void *marshalbyrefobject_class;
    void *generic_ilist_class;
    void *generic_icollection_class;
    void *generic_ienumerable_class;
    void *generic_ireadonlylist_class;
    void *generic_ireadonlycollection_class;
    void *runtimetype_class;
    void *generic_nullable_class;
    void *il2cpp_com_object_class;
    void *attribute_class;
    void *customattribute_data_class;
    void *version;
    void *culture_info;
    void *async_call_class;
    void *assembly_class;
    void *mono_assembly_class;
    void *assembly_name_class;
    void *mono_field_class;
    void *mono_method_class;
    void *mono_method_info_class;
    void *mono_property_info_class;
    void *parameter_info_class;
    void *mono_parameter_info_class;
    void *module_class;
    void *pointer_class;
    void *system_exception_class;
    void *argument_exception_class;
    void *wait_handle_class;
    void *safe_handle_class;
    void *sort_key_class;
    void *dbnull_class;
    void *error_wrapper_class;
    void *missing_class;
    void *value_type_class;
    void *threadpool_wait_callback_class;
    void *threadpool_perform_wait_callback_method;
    void *mono_method_message_class;
    void *ireference_class;
    void *ireferencearray_class;
    void *ikey_value_pair_class;
    void *key_value_pair_class;
    void *windows_foundation_uri_class;
    void *windows_foundation_iuri_runtime_class_class;
    void *system_uri_class;
    void *system_guid_class;
    void *sbyte_shared_enum;
    void *int16_shared_enum;
    void *int32_shared_enum;
    void *int64_shared_enum;
    void *byte_shared_enum;
    void *uint16_shared_enum;
    void *uint32_shared_enum;
    void *uint64_shared_enum;};
Il2CppDefaults_str il2cpp_str_defaults;
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
        _monoString *s;
        size_t size = (sizeof(_monoString) + ((strlen(str) + 1) * 2));
        ALLOC_PTRFREE(s, (_monoString *)(il2cpp_str_defaults.string_class), size);
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
