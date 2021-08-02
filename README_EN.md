# il2cpp_mono_string
Working il2cpp(mono) string for hacking unity il2cpp games.

I'm not beginner in Android modding. I made this monoString because I can.
# Usage:
```c++
//Create
monoString *il2cpp_method = CreateMonoString("Through il2ccp_string_new", true); // true - il2cpp method
monoString *mono_method = CreateMonoString("Through CreateString", false); // Need offsets, false - mono method
monoString *edit_str = mono_method;
edit_str->set("Changed!");
//Output
LOGI("const char*: %s", from_const_char->get_const_char());
LOGI("std::string: %s", from_string->get_string().c_str());
LOGI("edit_str: %s", edit_str->get_const_char());;
```

# What was used to create this monoString:

Convert il2cppString to std::string with utf8 support - https://github.com/Octowolve/aucl

CreateMonoString - https://platinmods.com/threads/how-to-modify-unitys-il2cpp-string-methods.123414/
