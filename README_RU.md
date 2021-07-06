# il2cpp_mono_string
Рабочий il2cpp(mono) string для ломания unity il2cpp игр.

Я не начинающий в андроид моддинге. Я сделал эту сборку monoString, потому что я могу.
# Использование:
```c++
//Создание
const char *cc = "const char";
monoString *from_const_char = monoString::New(cc);
std::string str = "string";
monoString *from_string = monoString::New(str);
monoString *just_create = new monoString();
just_create->create("Любой текст");
monoString *il2cpp_method = CreateMonoString("С Помощью il2ccp_string_new"); // const char * и std::string
monoString *mono_method = CreateMonoString("С Помощью CreateString", false); // Нужны оффсеты, const char * и std::string // false - mono метод
//Вывод
LOGI("const char*: %s", from_const_char->get_const_char());
LOGI("std::string: %s", from_string->get_string().c_str());
LOGI("just_create: %s", just_create->get_const_char());
LOGI("il2cpp_method: %s", il2cpp_method->get_string().c_str());
LOGI("mono_method: %s", mono_method->get_const_char());
```

# Что использовалось для создания этого monoString:

Конвертация Il2cppString в std::string с поддержкой utf8 - https://github.com/Octowolve/aucl

CreateMonoString - https://platinmods.com/threads/how-to-modify-unitys-il2cpp-string-methods.123414/
