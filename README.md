# scratch-source-online-comparer
The program can help you quickly use **scratch-source-copier** and **scratch-source-comparer** to compare the differences between different scratch projects
## Usage
　　This program depends on scratch-source-copier and scratch-source-comparer, so please make sure that the other two projects are in the program directory and the corresponding dependencies have been configured before use.So you may need to enter the following command to configure:
```shell
sudo update
sudo apt install nodejs git
git clone https://github.com/Steve-xmh/scratch-source-copier
cd scratch-source-copier && npm i
git clone https://github.com/Steve-xmh/scratch-source-comparer
cd ../scratch-source-comparer && npm i
```
To use it, enter the following command:
```shell
./soc [link1] [link2]
```