# New-Encryption-System
A new algorithm created for encrypting personal files. Not the strongest algorithm in the world, but good enough for most practical uses. 

To use the program, simply run the program and type the path to the file you would like to encrypt. Tell the program to encrypt it, and (for now), copy the raw encrypted string and paste it into the file you encrypted. This is done this way right now so that no files are permanently lost. Copy the password and put it somewhere safe.

To decrypt the encrypted file, restart the program and write the path to the file you wish to decrypt. Tell the program to decrypt it, and then enter the password. It will output the decrypted string.

# Known issues
It works for most decently sized paragraphs now! Unfortunately, if given too much info, it now hangs due to a while-loop error which I need to rewrite and get out of here (I will most likely do this with a recursive function).

# Goals moving forward
* Fixing the while-loop bug
* Adding unicode and UTF support

Please note that this is a side-project at best, and I will likely not make it anything more than that. The algorithm is extremely weak with small segments of text, but fairly strong with large ones (You are still better off using RSA though for now, and for the love of GOD DO NOT encrypt anything important with this until the larger bugs are ironed out).
