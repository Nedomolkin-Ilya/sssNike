# sssNike

Функция зашифварония и расшифрования файлов!

## Описани

sssNike это функция котороая зашифровывает файлы с использование алгоритма BlowFish.\n

## Установка
### Требования\
Компиялтор C\
СMake версии 2.8 и выше\
OpenSSL версии 1.0.1 и выше\

### Сборка
git clone <URL>
mkdir build
cd build
cmake ../sssNike
make

## Использование
sssnike -e||-d -f <fileName> -p <pasWd>
  -e||-d  Encryption||Decription
  -f      File name
  -p      The string on the base of with the password will be created
