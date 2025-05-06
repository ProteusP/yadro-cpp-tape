# Tape Sorter

Решение реализует сортировку данных с использованием эмуляции ленточного устройства хранения (типа tape). Поддерживается сортировка больших файлов с ограничением на использование оперативной памяти, а также конфигурируемые задержки операций чтения, записи и перемотки.

## Сборка

```bash
git clone https://github.com/ProteusP/yadro-cpp-tape
cd yadro-cpp-tape

mkdir build && cd build
cmake ..
make
```

## Запуск

Запуск приложения и тестов происходит из корневой папки:

#### TapeSorter

Переместим исполняемый файл в корневую директорию:

```bash
mv build/src/TapeSorter ../
```

Перед запуском можно настроить конфигурационный json файл _config.json_:

```json
{
  "delay_read": 1,
  "delay_write": 2,
  "delay_move": 3,
  "delay_rewind": 4
}
```

Запуск:

```bash
./TapeSorter <input_file>
```

Пример на файле _input.txt_:

```bash
./TapeSorter input.txt
```

Выходные данные запишутся в output.bin

#### Tests

Запуск тестов:

```bash
./build/tests/UnitTests
```


## Генерация файлов и валидация вывода

Дополнительно реализованы программы генерации входного файла и валидации выходного. Для их компиляции:
- Генерация

```bash
g++ -std=c++20 generate_input.cpp -o generate_input
```

- Валидация

```bash
g++ -std=c++20 validate_output.cpp -o validate_output
```

#### Запуск
- Генерация
```bash
./generate_input input.bin 5
```

- Валидация
```bash
./validate_output output.bin
```
