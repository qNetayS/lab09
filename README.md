# Отчёт по лабораторной работе №9: GitHub Release

**Студент:** qNetayS  
**Дата выполнения:** 2026-05-23  
**Репозиторий:** https://github.com/qNetayS/lab09  

---

## Цель работы

Изучить процесс создания релизов на GitHub, настройку GPG-подписи коммитов и автоматизацию упаковки артефактов с помощью CPack.

---

## Задачи

1. Создать публичный репозиторий `lab09` на GitHub
2. Настроить GPG-ключ для подписи коммитов и тегов
3. Создать CMake-проект с библиотекой `print`
4. Настроить CPack для упаковки в `.tar.gz`
5. Создать подписанный тег `v0.1.0.0`
6. Создать релиз на GitHub и загрузить артефакт
7. Настроить GitHub Actions для автоматического создания релизов

---

## Ход выполнения

### 1. Создание репозитория

```shell
gh repo create lab09 --public --clone
cd lab09
```

### 2.Настройка GPG-ключа

```
# Генерация ключа
gpg --full-generate-key

# Просмотр ключей
gpg --list-secret-keys --keyid-format LONG

# Настройка Git
git config --global user.signingkey 72F45FEF8DF00E38
git config --global commit.gpgsign true
git config --global user.email "petrenk007@yandex.ru"

# Экспорт публичного ключа
gpg --armor --export 72F45FEF8DF00E38

# Добавление ключа на GitHub
# https://github.com/settings/keys → New GPG key
```

### 3.Создание Cmake -проекта
```
cmake_minimum_required(VERSION 3.10)
project(print)

set(CMAKE_CXX_STANDARD 11)

add_library(print STATIC print.cpp)
install(TARGETS print DESTINATION lib)
install(FILES print.h DESTINATION include)

# Настройка CPack
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_NAME "print")
set(CPACK_PACKAGE_VERSION "0.1.0")
include(CPack)
```
print.h:
```
#pragma once
#include <string>
#include <ostream>

std::string print(const std::string& message);
void print(std::ostream& os, const std::string& message);
```
print.cpp:
```
#include "print.h"

std::string print(const std::string& message) {
    return "[" + message + "]";
}

void print(std::ostream& os, const std::string& message) {
    os << "[" << message << "]";
}
```
### 4.Сборка пакета
```
cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
cmake --build _build --target package
```

### 5.Создание тэга и релиза
```
# Создание подписанного тега
git tag -s v0.1.0.0 -m "First release"

# Отправка тега
git push origin v0.1.0.0

# Создание релиза через GitHub CLI
gh release create v0.1.0.0 \
    --title "print library" \
    --notes "First release: static library for string formatting" \
    _build/print-0.1.0-Linux.tar.gz
```
### 6.Настройка Github Actions
Для этого напишем файл release.yml
```
name: Create Release

on:
  push:
    tags:
      - 'v*'

jobs:
  release:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4

    - name: Build package
      run: |
        cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
        cmake --build _build --target package

    - name: Create Release
      uses: softprops/action-gh-release@v1
      with:
        files: _build/*.tar.gz
        generate_release_notes: true
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 7.Отправка всего на гитхаб
```
git add .
git commit -m "Lab09: GitHub Release with CPack"
git push origin main
git push origin v0.1.0.0
```
### 8.Результат
Ссылка:https://github.com/qNetayS/lab09/releases/tag/v0.1.0.0
