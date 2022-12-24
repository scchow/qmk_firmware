A custom keymapping for the Sofle RGB v3.0.0 (mini-E LED version).

My build also uses Elite-Pi microcontrollers that uses the Raspberry Pi rp2040 instead Atmega32u4 of the standard Pro-Micro.

To build QMK for the rp2040, use the following:

```
qmk compile -kb sofle/rev1 -km scchow -e CONVERT_TO=promicro_rp2040
```

