# New-Encryption-System
A new algorithm created for encrypting personal files. Not the strongest algorithm in the world, but good enough for most practical uses. 

To use the program, simply run the program and type the path to the file you would like to encrypt. Tell the program to encrypt it, and (for now), copy the raw encrypted string and paste it into the file you encrypted. This is done this way right now so that no files are permanently lost. Copy the password and put it somewhere safe.

To decrypt the encrypted file, restart the program and write the path to the file you wish to decrypt. Tell the program to decrypt it, and then enter the password. It will output the decrypted string.

# Known issues
It works for most decently sized paragraphs now! Unfortunately, if given too much info, it now hangs due to a while-loop error which I need to rewrite and get out of here (I will most likely do this with a recursive function). Non-ANSI characters are not supported right now.

# Goals moving forward
* Fixing the while-loop bug
* Adding unicode and UTF support

Please note that this is a side-project at best, and I will likely not make it anything more than that. The algorithm is extremely weak with small segments of text, but fairly strong with large ones (You are still better off using RSA though for now, and for the love of GOD DO NOT encrypt anything important with this until the larger bugs are ironed out).

# About the code itself
The main source file is EncryptionProgramNew.cpp. It has no helper headers or anything, the rest of the files are due to it being a Visual Studio 2019 Solution. You can compile EncryptionProgramNew.cpp outside of Visual Studio by simply removing the line #include "pch.h" from the top of EncryptionProgramNew.cpp, specifying compilation with C++11 or newer, and compiling. It also works on Linux. 

# How to work the program
Right now, the program does not write to any files (to prevent someone, say, writing the encrypted data to a personal file and never being able to get it back due to a glitch or something). When you run it, it will ask for a file to work on. Simply write the full file path of the file you wish to encrypt (right now, keeping in mind the limitations of no UTF-8 or Unicode support, keep it plain ANSI text). Then it will ask if you would like to encrypt or decrypt it. Answer. If you encrypt it, it will leave the numbers for the data in the terminal for you to copy and paste as you wish, as well as the password to be used upon decryption. If you choose decrypt, it will ask for the password.

Right now, to do encryption then decryption, or vice versa, you need to restart the program. 
