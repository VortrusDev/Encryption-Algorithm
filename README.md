# New-Encryption-System
A new algorithm created for encrypting personal files. Not the strongest algorithm in the world, but good enough for most practical uses. 

To use the program, simply run the program and type the path to the file you would like to encrypt. Tell the program to encrypt it, and (for now), copy the raw encrypted string and paste it into the file you encrypted. This is done this way right now so that no files are permanently lost. Copy the password and put it somewhere safe.

To decrypt the encrypted file, restart the program and write the path to the file you wish to decrypt. Tell the program to decrypt it, and then enter the password. It will output the decrypted string.

# Known issues
The decryption algorithm needs to be tweaked to work correctly. The program will not be able to write to any files right now, however this will change in the future once the encryption and decryption are more stable. The decryption algorithm will work for short sentences right now, but anything long will break due to a known bug. Multiple lines are not supported yet, and only ANSI text is supported right now. 
