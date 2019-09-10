# Problem set 4: File I/O and Pointers 

We now arrive at pointers and memory address. This section has us opening files and writing to disk, while allocating memory for our program to work.
It also gives a small foray into forensics as we have to access the content of a corrupted SD card.

### **Whodunit**
This assignment opens an image where we must scan each RGB triplets of a BMP in memory to remove tints of red. It then reveals the culprit.

### **Resize**
Takes into argument a BMP image and recopies it as a greater version. All the while respecting the padding of BMP files, as per the documentation.

### **Recover**
The real work of this problem set. We must load the raw data from a corrupted SD card into memory. Then, iterate through each Bytes until we find the signature of JPGs files. We must then export these files out to 'recover' them.
