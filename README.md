<h1 align="center">missware</h1>

<h4 align='center'>Работает только на видеокартах NVIDIA</h4>
<p align='center'>Хочу сообщить, что я не планирую продолжать обновление нашего проекта. В связи с изменением приоритетов, я не смогу уделять ему необходимое время и внимание.</p>

## Описание

Этот проект представляет собой консольное приложение с авторизацией через **Keyauth**. Приложение предоставляет различные функции и модификации игрового интерфейса.

### Реализованные функции
-  WallHack: позволяет видеть сквозь стены.

-  Chams: выделяет персонажей и объекты яркими цветами.
  

-  WallHack v2: Может работать лучше, чем Wallhack.
  

-  Delete Effects on Screen: убирает мешающие эффекты на экране для более комфортной игры.
  

## Установка

1. Склонируйте репозиторий:
   ```bash
   git clone https://github.com/finnalynop/STALCRAFT-chams.git
   ```
2. Перейдите в папку проекта:
   ```bash
   cd STALCRAFT-chams
   ```

## Использование

1. Настройте проект в режиме Release x64.
2. Настройте Keyauth в коде:
   ```cpp
   std::string name = skCrypt("").decrypt(); // App name
   std::string ownerid = skCrypt("").decrypt(); // Account ID
   std::string secret = skCrypt("").decrypt(); // Application secret
   std::string version = skCrypt("").decrypt(); // Application version
   ```
3. Обновите оффсеты:
   ```cpp
   std::uintptr_t wallhackAddress = baseAddress + OFFSET;
   std::uintptr_t chamsAddress = baseAddress + OFFSET;
   ```
4. Запустите приложение:
   ```bash
   ./build/loader.exe
   ```

<div align="center">
  <div>
	  <h2>Пример работы WallHack</h2>
	  <img src="https://i.ibb.co/H4dtCpL/wallhack.png" />
  </div>
  <div>
	  <h2>Пример работы Chams</h2>
	  <img src="https://i.ibb.co/nnmWz42/chams.png" />
  </div>
</div>

## Зависимости

- Keyauth SDK: для интеграции авторизации.
  

- skCrypt: библиотека для шифрования данных.
  

## Лицензия

RU: Этот проект распространяется под лицензией MIT. Подробности в файле [LICENSE](./LICENSE).

## Авторы

 ```
Dev - https://github.com/finnalynop
```

