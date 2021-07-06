# il2cpp_mono_string
Working il2cpp(mono) string for hacking unity il2cpp games.

I'm not beginner in Android modding. I made this monoString because I can.
# Usage:
```c++
//Create
const char *cc = "const char";
monoString *from_const_char = monoString::New(cc);
std::string str = "string";
monoString *from_string = monoString::New(str);
monoString *just_create = new monoString();
just_create->create("Any text");
monoString *il2cpp_method = CreateMonoString("Through il2ccp_string_new"); // const char * and std::string
monoString *mono_method = CreateMonoString("Through CreateString", false); // Need offsets, const char * and std::string // false - mono method
//Output
LOGI("const char*: %s", from_const_char->get_const_char());
LOGI("std::string: %s", from_string->get_string().c_str());
LOGI("just_create: %s", just_create->get_const_char());
LOGI("il2cpp_method: %s", il2cpp_method->get_string().c_str());
LOGI("mono_method: %s", mono_method->get_const_char());
```

# What was used to create this monoString:

Convert il2cppString to std::string with utf8 support - https://github.com/Octowolve/aucl

CreateMonoString - https://platinmods.com/threads/how-to-modify-unitys-il2cpp-string-methods.123414/
