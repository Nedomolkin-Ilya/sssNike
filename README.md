# sssNike

Функция зашифварония и расшифрования файлов!

## Описани

sssNike это функция котороая зашифровывает файлы с использование алгоритма BlowFish.\n

## Установка
### Требования
Компиялтор C\n
СMake версии 2.8 и выше\n
OpenSSL версии 1.0.1 и выше\n

### Сборка
git clone <URL>\n
mkdir build\n
cd build\n
cmake ../sssNike\n
make\n

## Использование
sssnike -e||-d -f <fileName> -p <pasWd>\n
  -e||-d  Encryption||Decription\n
  -f      File name\n
  -p      The string on the base of with the password will be created\n
