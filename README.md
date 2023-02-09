# DinguxCommander

DinguxCommander is a file manager for MiyooCFW.
It uses two vertical panels side by side, one being the source and the other the
destination, like many 'commander-style' file managers such as Norton Commander
or Midnight Commander.
DinguxCommander allows to:

* Copy, move and delete multiple files.
* View a file
* Execute a file
* Rename a file or directory
* Create a new directory
* Display disk space used by a list of selected files/dirs
* Display disk information (used, available, total)

## Building
1. Set up your environment with legacy dynamic uClibc toolchain: 

```
cd
wget https://github.com/steward-fu/miyoo/releases/download/v1.0/toolchain.7z
7za x toolchain.7z
sudo cp -a miyoo /opt/
```

2. Build output with Makefile for MiyooCFW:

```
make -f Makefile.miyoo
```

## Controls


* D-pad         Move
* L/R           Page up/page down
* A             For a directory: open
                For a file: view or execute
* B             Go to parent directory / cancel
* Y             System actions:
                  - Select all items
                  - Select no items
                  - Create new directory
                  - Display disk information
                  - Quit program
* X             Actions on selected items:
                  - Copy to destination directory
                  - Move to destination directory
                  - Rename (appears only if 1 item is selected)
                  - Delete
                  - Display disk used
* SELECT        Select highlighted item.
                Selected items are displayed in red.
* START         Open highlighted directory in destination panel.
                If a file is highlighted, open current directory in destination panel.


## Credits

Homepage:      http://beyondds.free.fr/
Development:   Mia
Font:          Beycan Çetin
