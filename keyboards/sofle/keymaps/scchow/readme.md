A custom keymapping for the Sofle RGB v3.0.0 (mini-E LED version).

My build also uses Elite-Pi microcontrollers that uses the Raspberry Pi rp2040 instead Atmega32u4 of the standard Pro-Micro.

To build QMK for the rp2040, use the following:

```
qmk compile -kb sofle/rev1 -km scchow -e CONVERT_TO=promicro_rp2040
```

Auto Detection of Handedness
---

In config.h, instead of setting `#define MASTER_LEFT` or `#define MASTER_RIGHT`, one can encode handedness in EEPROM.
In `config.h`, uncomment `#define EE_HANDS` and comment out `#define MASTER_LEFT`/`#define MASTER_RIGHT`. 
Then flash each side with the corresponding commands:
```
 make sofle:scchow:uf2-split-left
```
and 
```
 make sofle:scchow:uf2-split-left
```
Left/Right should be written into EEPROM and should persist unless EEPROM is wiped.