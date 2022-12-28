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

# TODO: RGB Matrix Lighting

Relevant links:
- https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_rgb_matrix.md
- https://www.reddit.com/r/olkb/comments/sbvefp/has_anyone_gotten_qmk_rgb_matrix_effects_working/


# Debugging Notes

## Debugging oled won't turn off


### Observations

1. When the usb is connected to the right hand side (thus right is master), the OLEDs do not turn off despite setting OLED_TIMEOUT.
2. The right hand side OLED has the bongo cat animation

#### Thoughts

1. Maybe the idle animation of the bongo cat is keeping the screen on?
 - Since the secondary side of the keyboard looks at oled status of master side, if bongo cat is keeping oled status on, then secondary will never see signal to turn off.
 - Whereas the left side is displaying only text with no idle, so when it is master, it will turn off.
 
1a. Test 1 - Add a CUSTOM_OLED_TIMEOUT that will force oled to be off 
 - This causes screen to flicker. Seems like something else is calling `oled_on()` in between CUSTOM_OLED_TIMEOUT checks

1b. Test 2 - Omit Bongo cat entirely, by showing oled status the whole time

2. Got around this by manually handing OLED_TIMEOUT to no longer call `oled_write()` when OLED_TIMEOUT is exceeded. There is probably still a bug somewhere that causes this issue with split keyboards using EE_Hands that needs to be tracked down. 

## Debug on wake single key held until reset

### Observations
 
 1. After the board is idle for a long while (enough that windows suspends), using the keyboard again will cause the board to get stuck on the first key pressed, sending that key repeatedly until the board is reset.

 Related Issue: https://github.com/qmk/qmk_firmware/issues/6369
 
 2. changed to 3000ms of wait -> still experiencing issue
 3. Fixed lufa.c wake from suspend condition. (probably won't have an effect but trying anyways)
 4. Added `NO_USB_STARTUP_CHECK = yes` in `rules.mk`
 