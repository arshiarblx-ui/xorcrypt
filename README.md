# xorcrypt
# XOR File Encryptor

A simple command-line tool written in C that encrypts and decrypts any file
(text, images, PDFs, ...) using a password and repeating-key XOR.

> ⚠️ **Educational project. This is NOT secure encryption.**
> Repeating-key XOR can be broken easily (for example with known-plaintext
> or frequency analysis). Do not use it to protect real sensitive data.

## Features

- Works on any file type (reads and writes in binary mode)
- Password-based: the same password encrypts and decrypts
- Checks for empty passwords, invalid menu input, and files that cannot be opened
- Refuses to use the same file for input and output (prevents data loss)

## How it works

Every byte of the file is XORed with a character of the password.
The password repeats over the whole file:

```
encrypted[i] = original[i] ^ password[i % passwordLength]
```

XOR is symmetric (`(a ^ k) ^ k == a`), so running the program again with the
same password restores the original file.

## Build

You need a C compiler such as GCC:

```bash
gcc main.c -o xorcrypt
```

## Usage

```bash
./xorcrypt        # Linux / macOS
xorcrypt.exe      # Windows
```

Example, encrypting a file:

```
1. Encrypt
2. Decrypt
Choose: 1
Encrypting
Enter input filename: secret.txt
Enter output filename: secret.enc
Enter password: mypassword
Done.
```
