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

## TODO

### Refactor encoder
Apparently, instead of manually tracking detents, we can just set encoder resolution in `config.h`:
```
#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 4
```
QMK defaults to 4, but sofle base repo sets it to 2. This reverts it. Based on [this](https://github.com/qmk/qmk_firmware/pull/19524#discussion_r1063983324).
There is also en encoder map feature that I may want to take a look at.

### Can no longer wake computer up with keyboard

Somewhere in my debugging the on wake key stuck issue, I broke waking from sleep using this board. Would be nice to fix it.

Maybe try things [here](https://github.com/qmk/qmk_firmware/issues/1149#issuecomment-792042931).

## Debug on wake single key held until reset

### Observations
 
 1. After the board is idle for a long while (enough that windows suspends), using the keyboard again will cause the board to get stuck on the first key pressed, sending that key repeatedly until the board is reset.

 Related Issue: https://github.com/qmk/qmk_firmware/issues/6369
 
 2. changed to 3000ms of wait -> still experiencing issue
 3. Fixed lufa.c wake from suspend condition. (probably won't have an effect but trying anyways)
 4. Added `NO_USB_STARTUP_CHECK = yes` in `rules.mk`
 5. Disabled RGBLight in `rules.mk` `RGBLIGHT_ENABLE = no`
   - No more freezes! So issue is when rgblight is enabled
 6. Maybe the rgblight turn off command is improper?
   - enabled RGBSleep flag for suspend and wake functions based on gist I saw.
   - refactored RGBLIGHT to use these functions
   - still freezing.
 7. Maybe it has something to do with the sharing of timers with oled?
   - Disabled oled.
   - Still freezing. D:
 8. what if we enable rgbsleep, but not the timer?
   - turns out rgbsleep doesn't seem to work
 9. let's try a different turn off rgb function
   - RGB_TOG keycode triggers rgb_toggle(), which in turn calls `rgblight_disable()` or `rgblight_enable()`
   - note how these are the eeprom versions of the functions instead of `rgblight_enable_noeeprom()` which we used before
   - let's try this function instead.
   - Something strange just happened. I pressed my keyboard and it did not wake my computer from sleep, nor did the oled on the secondary half of the keyboard wake up. The rgb did not turn on either. however it did not repeat the same key, instead, just froze.
   - I turned on the computer with the power button, and used my other keyboard for some typing. Then I left for a bit. When I came back, the board was responsive again. Huh...
 10. Trying to see if flashing the firmware with left and right specifically might solve the issue?
 - Still seeing issue
 11. Trying revert EEHands, switch back to MASTER_LEFT/MASTER_RIGHT

   

 