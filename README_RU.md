# il2cpp_mono_string
Рабочий il2cpp(mono) string для ломания unity il2cpp игр.

Я не начинающий в андроид моддинге. Я сделал эту сборку monoString, потому что я могу.
# Использование:
```c++
//Создание
monoString *il2cpp_method = CreateMonoString("С Помощью il2ccp_string_new", true); // true - il2cpp метод
monoString *mono_method = CreateMonoString("С Помощью CreateString", false); // Нужны оффсеты,  false - mono метод
monoString *edit_str = mono_method;
edit_str->set("Изменено!");
//Вывод
LOGI("il2cpp_method: %s", il2cpp_method->get_string().c_str());
LOGI("mono_method: %s", mono_method->get_const_char());
LOGI("edit_str: %s", edit_str->get_const_char());
```

# Что использовалось для создания этого monoString:

Конвертация Il2cppString в std::string с поддержкой utf8 - https://github.com/Octowolve/aucl

CreateMonoString - https://platinmods.com/threads/how-to-modify-unitys-il2cpp-string-methods.123414/
